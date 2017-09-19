#include <iostream>
#include <unordered_map>
#include "JSONImporter.h"
#include "TrigramSimilarityMeasure.h"
#include "BKTree.h"

using namespace std;

int main(int argc, char* argv[]) {

	string input = argv[1];
	cout << input << endl;

	unordered_map<string, unordered_set<string>> map;
	JSONImporter import(input, &map);
	cout << "JSON imp size : " << map.size() << endl;

	/*TRIGRAMSIM*/
	/*TrigramSimilarityMeasure trigram(&map);
	trigram.Search("birgite");*/
	
	/*BKTree*/
	/*BKTree myTree;
	for (pair<string, unordered_set<string>> element : map) {
		myTree.Add(element.first);		
	}

	vector<pair<string, int>> * result = myTree.Search("birgite", 3);
	for (vector<pair<string, int>>::iterator it = result->begin(); it != result->end(); it++) {
		cout << it->first << " Dist : " << it->second << endl;
	}*/

	/*FastSSwC*/

	int i;
	cin >> i;
}