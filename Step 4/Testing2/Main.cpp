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

	//	while (true) {
	//		cout << "Input search string. Type 'exit' to stop. Type 'p' to print dictionary.\n";
	//		string searchstring;
	//		getline(cin, searchstring);

	//		if (searchstring == "exit")
	//			break;
	//		if (searchstring == "p") {
	//			map.print();
	//			continue;
	//		}
	//		index.Search(searchstring);
	//	}
	/*}
	else {
		int i;
		cin >> i;*/
	}

	clock_t start = clock();
	HashMapHE invertedSubStrings(0);
	vector<string> results;
	for (int i = 0; i < map.getTableSize(); i++) {
		HashEntry * current = map.getTable()[i];
		if (current != NULL) {
			results.clear();
			SpellChecker::SubstringDeletion(2, current->getKey(), &results);
			for (vector<string>::iterator it = results.begin(); it != results.end(); it++)
				invertedSubStrings.put(*it, current->getKey());
		}
	}
	clock_t duration = clock() - start;
	cout << endl;
	cout << "Duration : " << duration / CLOCKS_PER_SEC << "\n";
	cout << "entries : " << invertedSubStrings.NO_OF_ENTRIES<< endl;


	word = "informes";
	results.clear();
	SpellChecker::SubstringDeletion(2, word, &results);
	for (vector<string>::iterator it = results.begin(); it != results.end(); it++) {
		HashEntry * current = invertedSubStrings.get(*it);
		if (current != NULL) {
			cout << *it << " existed" << endl;
			current->getValueEntries()->print();
		}
	}

	int i;
	cin >> i;
}