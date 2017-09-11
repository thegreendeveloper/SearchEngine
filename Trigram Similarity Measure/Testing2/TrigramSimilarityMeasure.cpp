#include "TrigramSimilarityMeasure.h"
#include "Utilities.h"

TrigramSimilarityMeasure::TrigramSimilarityMeasure(HashMapHE * map)
{
	this->map = map;
	cout << "Creating Three Gramm inverted file of entire dictionary (preprossesing)..." << endl;
	dictionaryThreeGrams = CreateThreeGramInverted();
}


TrigramSimilarityMeasure::~TrigramSimilarityMeasure()
{
	delete dictionaryThreeGrams;
}

void TrigramSimilarityMeasure::Search(string input) {
	
	///*PostProcessing : breaking input intro threegrams, iterating over each three grams 
	//doing similarity scores for each of the dictionary words*/
	vector<string> * inputTrigram = new vector<string>();
	NGramSplit(3, input, inputTrigram);
	HashMapVE * resultSet = new HashMapVE(0);

	// Applying trigram similarity meassure
	TrigramSimilarity(inputTrigram, dictionaryThreeGrams, resultSet);
	
	cout << "Did you mean?" << endl;
	vector<string> result;
	Utilities::sort(result, resultSet);
	int counter = 0;
	for (vector<string>::reverse_iterator it = result.rbegin(); it != result.rend(); it++) {
		cout << *it << endl;
		if (counter > 10)
			break;
		counter++;
	}

	delete resultSet;
	delete inputTrigram;
	delete dictionaryThreeGrams;
}

void TrigramSimilarityMeasure::TrigramSimilarity(vector<string> * inputTrigram, HashMapHE * invertedTrigram, HashMapVE * resultSet) {
	for (vector<string>::iterator it = inputTrigram->begin(); it != inputTrigram->end(); it++) {
		HashEntry * current = invertedTrigram->get(*it);
		if (current != NULL) {
			/*three grams exist in our dictionary. for each word the three gram exist in,
			we want to add it to our hashmapve and increment the counter*/
			HashMapVE * currentwords = current->getValueEntries();
			for (int i = 0; i < currentwords->getTableSize(); i++) {
				ValueEntry * currentVE = currentwords->getTable()[i];
				while (currentVE != NULL) {
					resultSet->put(currentVE->getKey());

					if (currentVE->getNext() == NULL)
						break;
					currentVE = currentVE->getNext();
				}
			}
		}
	}

	/*Calculated dice coefficient. Every word consist of n+2 trigrams. Multiplying by 100.*/
	for (int i = 0; i < resultSet->getTableSize(); i++) {
		ValueEntry * current = resultSet->getTable()[i];
		while (current != NULL) {
			/*if (current->getKey() == "words") {
				cout << "occ " << current->getOcc()  << " "<<inputTrigram->size() << " " << current->getKey().length() + 2 << endl;
				cout << (2 * current->getOcc()) / (inputTrigram->size() + current->getKey().length() + 2) * 100 << endl;
			}*/
			current->setOcc((2 * current->getOcc()) / (inputTrigram->size() + current->getKey().length() + 2)*100);
			if (current->getNext() == NULL)
				break;
			current = current->getNext();
		}
	}
}

HashMapHE * TrigramSimilarityMeasure::CreateThreeGramInverted() {
	HashMapHE * ngramsDataSet = new HashMapHE(0);
	for (int i = 0; i < map->getTableSize(); i++) {

		HashEntry * currentHashEntry = map->getTable()[i];
		while (currentHashEntry != NULL) {

			//Split string into n-grams 
			vector<string> * threeGramsWord = new vector<string>();
			NGramSplit(3, currentHashEntry->getKey(), threeGramsWord);


			//for each three grams in the vector insert three gram into ngramsDataSet and insert the word as well.
			for (vector<string>::iterator it = threeGramsWord->begin(); it != threeGramsWord->end(); it++) {
				ngramsDataSet->put(*it, currentHashEntry->getKey());
			}

			delete threeGramsWord;

			if (currentHashEntry->getNext() == NULL)
				break;
			currentHashEntry = currentHashEntry->getNext();
		}
	}
	return ngramsDataSet;
}

/*Overlapping ngram split. Spaces are filled out with $
Performance :
word length 4, iteration : 200000, 18 sec.
word length 16, iteration : 200000, 38 sec. */
void TrigramSimilarityMeasure::NGramSplit(int ngram, string word, vector<string> * stringVector) {

	for (int index = 0; index < word.length(); index++) {
		if (index == word.length())
			return;

		if (index - ngram + 1 < 0) {
			string concatinated;
			int upper = (ngram - index - 1);
			for (int i = 0; i < upper; i++)
				concatinated += "$";
			concatinated += word.substr(0, index + 1);
			stringVector->push_back(concatinated);
		}

		if (index + ngram > word.length()) {
			string concatinated = word.substr(index, ngram);
			int upper = index + ngram - word.length();
			for (int i = 0; i < upper; i++) {
				concatinated += "$";
			}
			stringVector->push_back(concatinated);
		}

		if (index + ngram <= word.length())
			stringVector->push_back(word.substr(index, ngram));
	}
}

