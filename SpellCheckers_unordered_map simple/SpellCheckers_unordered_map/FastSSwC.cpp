#include "FastSSwC.h"
#include <iostream>
#include "Utilities.h"

FastSSwC::FastSSwC(unordered_set<string> * map, int k)
{
	this->map = map;
	initialize(k);
}


FastSSwC::~FastSSwC()
{
}

void FastSSwC::initialize(int k) {
	cout << "creating the inverted file of deletions.." << endl;
	invertedSubStrings = new unordered_map<string, unordered_set<string>>();

	for (unordered_set<string>::iterator it = map->begin(); it != map->end(); it++) {
		unordered_set<string> substrings;
		SubstringDeletionRecurse(k, *it, &substrings);

		for (string delSubStrngsIt : substrings) {
			auto iter = invertedSubStrings->find(delSubStrngsIt);
			if (iter == invertedSubStrings->end()) {
				unordered_set<string> words;
				words.insert(*it);
				invertedSubStrings->insert(make_pair(delSubStrngsIt, words));
			}
			else {
				auto iter2 = iter->second.find(*it);
				if (iter2 == invertedSubStrings->at(delSubStrngsIt).end())
					invertedSubStrings->at(delSubStrngsIt).insert(*it);
			}
		}
	}
	cout << "invertedSubStrings entries : " << invertedSubStrings->size() << endl;
}

void FastSSwC::Search(string input) { 
	vector<string> deletionStrings;
	SubstringDeletion(input, &deletionStrings);

	unordered_map<string, double> resultSet;
	for (vector<string>::iterator it = deletionStrings.begin(); it != deletionStrings.end(); it++) {
		auto iter = invertedSubStrings->find(*it);
		if (iter != invertedSubStrings->end()) {

			for (string element : iter->second) {
				resultSet.insert(make_pair(element, 0));
			}
		}
	}

	/*Calc edit distance and sort by these.*/ 
	for (unordered_map<string, double>::iterator it = resultSet.begin(); it != resultSet.end(); it++) {	
			it->second = Utilities::LevenshteinDistance(it->first, it->first.length(), input, input.length());
	}

	vector<string> sortedList;
	Utilities::sort(sortedList, &resultSet);
	Utilities::print(&sortedList, 10, false, "Sugestions based on FastSSwC : ");
}


/*faster but only worst for K = 2*/
void FastSSwC::SubstringDeletion(string word, vector<string> * stringVector) {
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

void FastSSwC::SubstringDeletionRecurse(int k, string word, unordered_set<string> * stringVector) {
	if (k == 0)
		return;

	for (int i = 0; i < word.length(); i++) {
		string temp = word;
		temp.replace(i, 1, "");
		stringVector->insert(temp);

		SubstringDeletionRecurse(k - 1, temp, stringVector);
	}
}
