#include <iostream>
#include <unordered_map>
#include "JSONImporter.h"
#include "TrigramSimilarityMeasure.h"
#include "BKTree.h"
#include "FastSSwC.h"

using namespace std;

int main(int argc, char* argv[]) {

	string input = argv[1];
	cout << input << endl;

	unordered_map<string, unordered_set<string>> map;
	JSONImporter import(input, &map);
	cout << "JSON imp size : " << map.size() << endl;

	/*Building the spellcheckers*/

	/*TRIGRAMSIM*/
	TrigramSimilarityMeasure trigram(&map);
	
	///*FastSSwC*/
	//FastSSwC ss(&map, 2);

	///*BKTree*/
	//BKTree myTree;
	//for (pair<string, unordered_set<string>> element : map)
	//	myTree.Add(element.first);		

	///*search loop*/
	//while (true) {
	//	cout << "input search string. type 'exit' to stop. type 'p' to print dictionary.\n";
	//	string searchstring;
	//	getline(cin, searchstring);

	//	if (searchstring == "exit")
	//		break;

	//	trigram.Search(searchstring);
	//	ss.Search(searchstring);
	//	myTree.Search(searchstring,3);
	//}

	int i;
	cin >> i;
}