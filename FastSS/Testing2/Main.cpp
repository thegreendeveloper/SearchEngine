#include "HashEntry.h"
#include "HashMapHE.h"
#include "Utilities.h"
#include "FastSS.h"
#include "JSONImporter.h"
#include "TextImporter.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1], word, dt;

	HashMapHE map(0);	
	
	JSONImporter import(filename, &map);

		clock_t start = clock();
		FastSS ss(&map, 2);
		clock_t duration = clock() - start;
		cout << endl;
		cout << "Duration building the suffix inverted file : " << duration / CLOCKS_PER_SEC << "\n";
		
		cout << "calculating average length" << endl;
		double avg = 0;
		for (int i = 0; i < map.getTableSize(); i++) {
			if (map.getTable()[i] != NULL)
				avg += map.getTable()[i]->getKey().length();
		}
		cout << "average str size : " << avg / map.NO_OF_ENTRIES << endl;

		while (true) {
			cout << "input search string. type 'exit' to stop. type 'p' to print dictionary.\n";
			string searchstring;
			getline(cin, searchstring);

			if (searchstring == "exit")
				break;
			if (searchstring == "p") {
				map.print();
				continue;
			}

			ss.Search(searchstring);
		}

	int i;
	cin >> i;
}