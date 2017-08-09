#include "Utilities.h"

void Utilities::ImportFile(string fileName, unordered_map<string, unordered_map<string, string>> * map) {
	clock_t start = clock();
	FILE * file = NULL;
	char buf[1024];

	int totalLines = getLineCount(fileName), counter = 0;
	int divisor = totalLines / 10;

	string line, word, dt;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			counter++;
			if (counter % divisor == 0) {
				cout << counter << " out of " << totalLines << " lines" << endl;
			}

			istringstream iss(line);
			while (iss >> word) {
				if (dt == "") {
					dt = line;
					continue;
				}
				if (word == "---END.OF.DOCUMENT---") {
					dt = "";
					continue;
				}
				unordered_map<string, unordered_map<string, string>>::const_iterator got = map->find(word);
				if (got == map->end()) {
					/*not found*/
					unordered_map<string, string > newMap; 
					newMap.insert(make_pair(dt,dt));
					map->insert(make_pair(word, newMap));
				}
				else {
					/*word exist, we need to update the document map*/
					/*this takes sooo long time and I wonder why*/
					unordered_map<string, string> documents = got->second;
					documents.insert(make_pair(dt,dt));
					(*map)[word] = documents;
				}
			}
		}
		myfile.close();
	}
	else {
		cout << "File could not be read" << endl;
	}

	clock_t duration = clock() - start;
	cout << "Duration : " << duration / CLOCKS_PER_SEC << "\n";
	//cout << "Hashmap size: " << map->size << endl;

}
int Utilities::getLineCount(string fileName) {
	cout << "Counting number of lines.." << endl;
	int counter = 0;
	string line;
	FILE * file = NULL;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			counter++;
		}
		myfile.close();
	}
	return counter;
}