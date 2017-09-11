#include "HashEntry.h"
#include "HashMapHE.h"
#include "Utilities.h"
#include "Index.h"
#include "SpellChecker.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1], word, dt;

	HashMapHE map(0);	
	if (Utilities::ImportFile(filename, &map)) {
		Index index(&map);

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
			index.Search(searchstring);
		}
	/*}
	else {
		int i;
		cin >> i;*/
	}

	/*clock_t start = clock();
	HashMapHE invertedSubStrings(0);
	vector<string> results;
	for (int i = 0; i < map.getTableSize(); i++) {
		HashEntry * current = map.getTable()[i];
		if (current != NULL) {
			results.clear();
			SpellChecker::SubstringDeletion(3, current->getKey(), &results);
			for (vector<string>::iterator it = results.begin(); it != results.end(); it++)
				invertedSubStrings.put(*it, current->getKey());
		}
	}
	clock_t duration = clock() - start;
	cout << endl;
	cout << "Duration building the suffix inverted file : " << duration / CLOCKS_PER_SEC << "\n";
	cout << "entries : " << invertedSubStrings.NO_OF_ENTRIES<< endl;


	start = clock();
	word = "inehritad";
	results.clear();
	SpellChecker::SubstringDeletion(3, word, &results);
	duration = clock() - start;
	cout << endl;
	cout << "Duration searching the inverted file : " << duration / CLOCKS_PER_SEC << "\n";
	
	for (vector<string>::iterator it = results.begin(); it != results.end(); it++) {
		HashEntry * current = invertedSubStrings.get(*it);
		if (current != NULL) {
			cout << *it << " existed" << endl;
			current->getValueEntries()->print();
		}
	}*/

	int i;
	cin >> i;
}