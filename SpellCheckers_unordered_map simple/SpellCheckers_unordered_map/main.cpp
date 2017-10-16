#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
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
	string input = "C:/Users/tjoe/Dropbox/DTUMaster/5/Thesis/datafiles/FinalNotaThird.txt";
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
	BKTree myTree;
	int counter = 0;
	for (string element : map) {
		counter++;
		myTree.Add(element);		

		if (counter % 10000 == 0)
			cout << "counter : " << counter << endl;
	}


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

	//Reading search file and querying spellchecker
	ifstream file("C:/Users/tjoe/Dropbox/DTUMaster/5/Thesis/datafiles/testData/TestDataPopular.txt");
	ofstream outfile("C:/Users/tjoe/Dropbox/DTUMaster/5/Thesis/datafiles/testData/BKTreeResult.txt");
	string word;
	clock_t begin, end;
	double elapsed_secs;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			string query = line.substr(0, line.find(","));
			outfile << query << std::endl;

			istringstream iss(query);
			int counter = 0;
			while (iss >> word) {
				begin = clock();
				vector<string> result = myTree.Search(word, 2);
				end = clock();
				elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
				outfile << "\t"<< word << "\t" << elapsed_secs << std::endl;
				counter++;
			}

			if (counter > 1) {
				begin = clock();
				vector<string> result = myTree.Search(query, 2);
				end = clock();
				elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
				outfile << "\t" << query << "\t" << elapsed_secs << std::endl;			
			}
		}
	}
	outfile.close();
	cout << "Finished" << endl;
	int i;
	cin >> i;
}