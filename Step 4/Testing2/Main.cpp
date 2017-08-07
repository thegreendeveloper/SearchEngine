#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

#include "HashEntry.h"
#include "HashMapHE.h"
#include "HashMapVE.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << argv[1] << "\n";
	clock_t start = clock();
	string filename = argv[1], word, dt;

	HashMapHE map(0);
	FILE * file = NULL;
	char buf[1024];
	
	string line;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
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
				map.put(word, dt);
			}
		}
		myfile.close();
	}
	else {
		cout << "File could not be read" << endl;
	}

	
	clock_t duration = clock() - start;
	cout << "Duration : " << duration / CLOCKS_PER_SEC << "\n";
	cout << "Max chained collision length: " << map.MAX_NO_OF_COLLISIONS << endl;
	cout << "Number of entries : " << map.NO_OF_ENTRIES << endl;
	cout << "Final table size: " << map.getTableSize() << endl;

	while (true) {
		cout << "Input search string or type exit to stop\n";
		string searchstring;
		cin >> searchstring;

		if (searchstring == "exit")
			break;

		/*printing out the rresults in the search engine*/
		HashEntry * result = map.get(searchstring);
		if (result != NULL) {
			cout << searchstring << " exists in the documents: " << endl;
			HashMapVE * entries = result->getValueEntries();
			entries->print();
		}
		else
			cout << searchstring << " does not exist!\n";

	}

}