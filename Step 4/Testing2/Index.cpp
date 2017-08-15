#include "Index.h"



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
	/*TODO :: printing out the rresults in the search engine*/
	vector<string> searchStrings = destructSearchString(searchstring);

	if (searchStrings.size() == 1) {
		HashEntry * result = map->get(searchstring);
		if (result != NULL) {
			cout << searchstring << " exists in the documents: " << endl;
			HashMapVE * entries = result->getValueEntries();
			entries->print();
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
	vector<string> documents;

	/*Extract the first word in the list, use this list to compare documents of all other words in the searchstring*/
	HashMapVE * entries = map->get(searchStrings[0])->getValueEntries();
	for (int i = 0; i < entries->getTableSize(); i++) {
		if (entries->getTable()[i] != NULL) {
			bool intersect = false;
			for (vector<string>::iterator it = searchStrings.begin() + 1; it != searchStrings.end(); it++) {
				if (map->get(*it)->getValueEntries()->get(entries->getTable()[i]->getKey()))
					intersect = true;
				else
					intersect = false;
			}
			if (intersect)
				documents.push_back(entries->getTable()[i]->getKey());
		}
	}
	/*output the intersected documents*/
	if (documents.size() != 0) {
		cout << "The words intersect in the documents: " << endl;
		for (vector<string>::iterator it = documents.begin(); it != documents.end(); it++) {
			cout << *it << endl;
		}
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
