#include "Index.h"
#include "SpellChecker.h"
#include "Utilities.h"

Index::Index(HashMapHE * map)
{
	/*Initialize global map*/
	this->map = map;

	/*Ranking would  require some restructuring of the documents or maybe this should be done after creating the map*/
}


Index::~Index()
{
}

void Index::Search(string searchstring) {
	//TODO try to optimize printing otu the documents*/
	vector<string> searchStrings = destructSearchString(searchstring);

	if (searchStrings.size() == 1) {
		HashEntry * result = map->get(searchstring);
		if (result != NULL) {
			cout << searchstring << " exists in the documents: " << endl;
			HashMapVE * entries = result->getValueEntries();
			/*raddix sort result*/
			vector<string> * result = Utilities::sort(entries);
			for (vector<string>::iterator it = result->begin(); it != result->end();it++) {
				cout << *it << endl;
			}
			return;
		}

		/*Result did not exist. We call our spellchecker applications to find the words most similar to the input*/
		initializeSpellChecker(searchstring);
		return;
	}

	/* Extract the first word in the searchstring. If this does not exist in the map, then
	we return nothing (because searchstring is AND'ed).*/
	if (map->get(searchStrings[0]) == NULL) {
		cout << "None of the words intersect" << endl;
		return;
	}

	intersectSearchstring(searchStrings);
}

void Index::initializeSpellChecker(string searchString) {
	SpellChecker check(searchString, map);

	//// EDIT DISTANCE ////////////
	/*HashMapVE * resultSet = check.Levenshtein(false);	
	cout << "Did you mean: " << endl;
	vector<string> * result = Utilities::sort(resultSet);
	vector<string> * result2 = Utilities::sort(resultSet2);
	
	for (vector<string>::iterator it = result->begin(); it != result->end(); it++) {
		cout << *it << endl;	
	}
	delete resultSet;
	delete result;
	cout << endl;

	////// DAMERAU LEVENSTEIN DISTANCE ///////////////
	HashMapVE * resultSet2 = check.Levenshtein(true);
	for (vector<string>::iterator it2 = result2->begin(); it2 != result2->end(); it2++) {
		cout << *it2 << endl;

	}	
	delete resultSet2;
	delete result2;*/

	////////////// THREEEE GRAMS /////////////////////
	/*Preprossesing : breaking entire dictionary into threegrams*/
	HashMapHE * dictionaryThreeGrams = check.ThreeGram();
	
	/*PostProcessing : breaking input intro threegrams, iterating over each three grams 
	doing similarity scores for each of the dictionary words*/
	vector<string> * wordGrams = new vector<string>();
	check.ThreeGramSplit(searchString,wordGrams);
	HashMapVE * wordOcc = new HashMapVE(0);

	for (vector<string>::iterator it = wordGrams->begin(); it != wordGrams->end(); it++) {
		HashEntry * current = dictionaryThreeGrams->get(*it);
		if (current != NULL) {
			/*Three grams exist in our dictionary. For each word the three gram exist in, 
			we want to add it to our hashmapVE and increment the counter*/
			HashMapVE * currentWords = current->getValueEntries();
			for (int i = 0; i < currentWords->getTableSize(); i++) {
				ValueEntry * current = currentWords->getTable()[i];
				while (current != NULL) {
					wordOcc->put(current->getKey());

					if (current->getNext() == NULL)
						break;
					current = current->getNext();
				}
			}
		}
	}
	vector<string> * result3 = Utilities::sort(wordOcc);
	for (vector<string>::iterator it = result3->begin(); it != result3->end(); it++) {
		cout << *it << endl;

	}
	delete result3;
	delete wordOcc;
	delete wordGrams;
	delete dictionaryThreeGrams;
}

void Index::intersectSearchstring(vector<string> searchStrings) {
	//vector<string> documents;
	HashMapVE * documents = new HashMapVE(0);

	/*Extract the first word in the list, use this list to compare documents of all other words in the searchstring*/
	HashMapVE * entries = map->get(searchStrings[0])->getValueEntries();
	for (int i = 0; i < entries->getTableSize(); i++) {
		ValueEntry * current = entries->getTable()[i];
		if (current != NULL) {
			bool intersect = true;
			int occ = 0;
			for (vector<string>::iterator it = searchStrings.begin() + 1; it != searchStrings.end(); it++) {
				HashEntry * entry = map->get(*it);
				if (entry == NULL || !entry->getValueEntries()->get(current->getKey())) {
					intersect = false;
				}

				if (!intersect)
					break;
				occ += entry->getValueEntries()->get(current->getKey())->getOcc();
			}
			/*If all words in the document intersect then we add the document to the list. Addition the occurences.*/
			if (intersect) {
				documents->put(entries->getTable()[i]->getKey());
				documents->get(entries->getTable()[i]->getKey())->setOcc(entries->getTable()[i]->getOcc() + occ);
			}
		}
	}
	/*output the intersected documents*/
	if (!documents->isEmpty()) {
		cout << "The words intersect in the documents: " << endl;
		vector<string> * result = Utilities::sort(documents);
		for (vector<string>::iterator it = result->begin(); it != result->end(); it++) {
			cout << *it << endl;
		}
	}
	else
		cout << "None of the words intersect" << endl;

	delete documents;
}

vector<string> Index::destructSearchString(string searchString) {
	vector<string> result;
	size_t pos = searchString.find("AND");
	if (pos == -1) {
		result.push_back(searchString);
		return result;
	}

	string current = searchString;
	while (pos != -1) {
		result.push_back(current.substr(0, pos - 1));
		current = current.substr(pos + 4, current.length());
		pos = current.find("AND");
	}
	result.push_back(current);

	return result;
}
