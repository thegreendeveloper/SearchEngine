#include "Index.h"
#include "RaddixSort.h"

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
	RaddixSort radix;
	if (searchStrings.size() == 1) {
		HashEntry * result = map->get(searchstring);
		if (result != NULL) {
			cout << searchstring << " exists in the documents: " << endl;
			HashMapVE * entries = result->getValueEntries();
			/*raddix sort result*/
			radix.sort(entries);			
			return;
		}

		cout << searchstring << " does not exist!" << endl;
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

void Index::intersectSearchstring(vector<string> searchStrings) {
	//vector<string> documents;
	HashMapVE * documents = new HashMapVE(0);

	/*Extract the first word in the list, use this list to compare documents of all other words in the searchstring*/
	HashMapVE * entries = map->get(searchStrings[0])->getValueEntries();
	for (int i = 0; i < entries->getTableSize(); i++) {
		if (entries->getTable()[i] != NULL) {
			bool intersect = false;
			for (vector<string>::iterator it = searchStrings.begin() + 1; it != searchStrings.end(); it++) {
				HashEntry * entry = map->get(*it);
				if (entry != NULL && entry->getValueEntries()->get(entries->getTable()[i]->getKey()))
					intersect = true;
				else
					intersect = false;
			}
			//TODO Find a way to sort according to the most popular document. Dont know if relevant.*/
			if (intersect)
				documents->put(entries->getTable()[i]->getKey());
		}
	}
	/*output the intersected documents*/
	if (!documents->isEmpty()) {
		cout << "The words intersect in the documents: " << endl;
		documents->print();
	}
	else
		cout << "None of the words intersect" << endl;
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
