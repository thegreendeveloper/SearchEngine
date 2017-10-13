#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "JSONImporter.h"
#include "TrigramSimilarityMeasure.h"
#include "BKTree.h"
#include "FastSSwC.h"

using namespace std;

int main(int argc, char* argv[]) {

	//string input = argv[1];
	//cout << input << endl;

	unordered_set<string> map;
	//string input = "C:/Users/tjoe/Dropbox/DTUMaster/5/Thesis/datafiles/FULLSPELL0";
	//JSONImporter json;

	//for (int i = 1; i < 4; i++) {
	//	json.readJSONFileRapid(input+to_string(i)+".json", &myMap);
	//	clock_t end = clock();
	//	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//	cout << "Time : " << elapsed_secs << endl;

	//}
	string input = "C:/Users/tjoe/Dropbox/DTUMaster/5/Thesis/datafiles/FinalNotaDict.txt";
	ifstream myfile(input);
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			map.insert(line);
		}
	}
	cout << "map size : " << map.size() << endl;


	/*Building the spellcheckers*/

	/*TRIGRAMSIM*/
	//TrigramSimilarityMeasure trigram(&map);
	
	/*FastSSwC*/
	//FastSSwC ss(&map, 2);

	/*BKTree*/
	/*BKTree myTree;
	for (string element : map)
		myTree.Add(element);		*/


	/*search loop*/
	//while (true) {
	//	cout << "input search string. type 'exit' to stop. type 'p' to print dictionary.\n";
	//	string searchstring;
	//	getline(cin, searchstring);

	//	if (searchstring == "exit")
	//		break;

	//	trigram.Search(searchstring);
	//	//ss.Search(searchstring);
	//	//myTree.Search(searchstring,3);
	//}

	int i;
	cin >> i;
}