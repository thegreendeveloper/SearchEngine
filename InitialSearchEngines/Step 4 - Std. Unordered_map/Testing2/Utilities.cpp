#include "Utilities.h"

void Utilities::ImportFile(string fileName, unordered_map<string, unordered_map<string, string>> * map) {
	clock_t start = clock();

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
				auto got = map->find(word);
				if (got == map->end()) {
					/*not found*/
					unordered_map<string, string > newMap; 
					newMap.insert(make_pair(dt,dt));
					map->insert(make_pair(word, newMap));
				}
				else {
					/*word exist, we need to update the document map*/
					auto iter = map->at(word).find(dt);
					if (iter == map->at(word).end()) {
						map->at(word).insert(make_pair(dt, dt));
					}
				}
			}
		}
		myfile.close();
	}
	else {
		cout << "File could not be read" << endl;
	}

	myfile.close();
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