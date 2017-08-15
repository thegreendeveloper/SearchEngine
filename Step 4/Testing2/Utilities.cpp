#include "Utilities.h"

bool Utilities::ImportFile(string fileName, HashMapHE * map) {
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
				map->put(word, dt);
			}
		}
		myfile.close();
	}
	else {
		cout << "File could not be read" << endl;
		return false;
	}

	clock_t duration = clock() - start;
	cout << endl;
	cout << "Duration : " << duration / CLOCKS_PER_SEC << "\n";
	cout << "Max chained collision length: " << map->MAX_NO_OF_COLLISIONS << endl;
	cout << "Number of entries : " << map->NO_OF_ENTRIES << endl;
	cout << "Final table size: " << map->getTableSize() << endl;
	return true;
}
int Utilities::getLineCount(string fileName) {
	int counter = 0;
	string line;
	FILE * file = NULL;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		cout << "Counting number of lines.." << endl;
		while (getline(myfile, line))
		{
			counter++;
		}
		myfile.close();
	}
	return counter;
}