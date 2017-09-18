#include "FastSS.h"



FastSS::FastSS(HashMapHE * map, int k)
{
	this->map = map;
	this->k = k;
	initialize();
}


FastSS::~FastSS()
{
}

void FastSS::initialize() {
	cout << "creating the inverted file of deletions.." << endl;
	invertedSubStrings = new HashMapHE(0);
	vector<string> substrings;

	for (int i = 0; i < map->getTableSize(); i++) {
		HashEntry * current = map->getTable()[i];
		if (current != NULL) {
			substrings.clear();
			SubstringDeletion(k, current->getKey(), &substrings);
			for (vector<string>::iterator it = substrings.begin(); it != substrings.end(); it++)
				invertedSubStrings->put(*it, current->getKey());
		}
	}
	cout << "invertedSubStrings entries : " << invertedSubStrings->NO_OF_ENTRIES << endl;
}

void FastSS::Search(string input) { //TODO : Not correct
	vector<string> results;
	SubstringDeletion(k, input, &results);

	for (vector<string>::iterator it = results.begin(); it != results.end(); it++) {
		HashEntry * current = invertedSubStrings->get(*it);
		if (current != NULL) {
			cout << *it << " existed" << endl;
			current->getValueEntries()->print();
		}
	}
}


void FastSS::SubstringDeletion(int k, string word, vector<string> * stringVector) {
	for (int distance = 0; distance < word.length(); distance++) {
		for (int i = 0; i < word.length(); i++) {
			string temp = word;
			if (distance != 0 && i + distance < word.length())
				temp = temp.replace(i + distance, 1, "");
			temp.replace(i, 1, "");

			if (i + distance >= word.length())
				break;

			stringVector->push_back(temp);
		}
	}
}