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

void insertTestData(vector<string> * testData, string filename);
void printFile(string outputFName, vector<string> resultSet);

int main(int argc, char* argv[]) {

	string path = argv[1];
	
	unordered_set<string> map;
	
	ifstream myfile(path + "FinalNotaThird.txt");
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
	FastSSwC ss(&map, 2);

	/*BKTree*/ //WORKS
	//BKTree myTree;
	//int counter = 0;

	//for (auto it = map.begin(); it != map.end(); ++it)
	//{
	//	string element = *it;
	////for (string element : map) {
	//	counter++;
	//	myTree.Add(element);		

	//	if (counter % 10000 == 0)
	//		cout << "counter : " << counter << endl;
	//}


	//Reading search file and querying spellchecker
	vector<string> testData;
	vector<string> resultSet;
	string word;
	clock_t begin, end;
	double elapsed_secs;

	insertTestData(&testData, path + "testData/TestDataPopular.txt");
	cout << "Read test data" << endl;

	for (string value : testData) {
		resultSet.push_back(value);
		istringstream iss(value);
		int counter = 0;

		while (iss >> word) {
			counter++;
			if (map.find(word) != map.end()) {
				resultSet.push_back("\t" + word + "\t" + word + "\t" + to_string(0));
				continue;
			}

			begin = clock();
			//vector<string> result = myTree.Search(word, 2);
			//vector<string> result = trigram.Search(word); //NEeds testing
			vector<string> result = ss.Search(word);

			end = clock();
			elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			if (result.size() > 0) {
				string concat = "{";
				for (string val : result) {
					concat += val + ", ";
				}
				resultSet.push_back("\t" + word + "\t" + concat + "}\t" + to_string(elapsed_secs));
			}
			else {
				resultSet.push_back("\t" + word + "\t{}\t" + to_string(elapsed_secs));
			}
		}

		if (counter > 1) {			
			begin = clock();
			//vector<string> result = myTree.Search(value, 2);
			//vector<string> result = trigram.Search(word); //NEeds testing
			vector<string> result = ss.Search(value);

			end = clock();
			elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			if (result.size() > 0) {
				string concat = "{";
				for (string val : result) {
					concat += val + ", ";
				}
				resultSet.push_back("\t" + value +"\t"+ concat+"}\t" + to_string(elapsed_secs));
			}
			else
				resultSet.push_back("\t" + value + "\t{}\t" + to_string(elapsed_secs));
		}
	}
	
	//printFile(path+"testData/BKTreeResultCPP.txt", resultSet);
	//printFile(path+"testData/TrigramResultCPP.txt", resultSet);
	printFile(path + "testData/FastSSResultCPP.txt", resultSet);

	cout << "Finished" << endl;
	int i;
	cin >> i;
}

void printFile(string outputFName, vector<string> resultSet) {
	ofstream outfile(outputFName);

	for (string line : resultSet) {
		outfile << line << endl;
	}
	outfile.close();
}

void insertTestData(vector<string> * testData, string filename) {
	ifstream file(filename);
	
	string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			string query = line.substr(0, line.find(","));
			testData->push_back(query);
		}
	}
	file.close();
}