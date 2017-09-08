#include "HashEntry.h"
#include "HashMapHE.h"
#include "Utilities.h"
#include "Index.h"
#include "BKTree.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1], word, dt;

	HashMapHE map(0);	
	if (Utilities::ImportFile(filename, &map)) {
		Index index(&map);
	}
	

	/*Filling out the tree with the wiki info*/
	clock_t start = clock();
	int first = 0;
	for (int i = 0; i < map.getTableSize(); i++) {
		if (map.getTable()[i] != NULL) {
			first = i;
			break;
		}
	}

	BKTree tree(map.getTable()[first]->getKey());
	for (int i = first+1; i < map.getTableSize(); i++) {

		HashEntry * current = map.getTable()[i];
		while (current != NULL) {
			tree.Add(current->getKey());
			if (current->getNext() == NULL)
				break;
			current = current->getNext();
		}
	}

	//BKTree tree("book");
	//tree.Add("books");
	//tree.Add("cake");
	//tree.Add("boo");
	//tree.Add("cape");
	//tree.Add("cart");
	//tree.Add("boon");
	//tree.Add("cook");

	//tree.Print();
	

	clock_t duration = clock() - start;
	cout << endl;
	cout << "Build tree duration : " << duration / CLOCKS_PER_SEC << "\n";


	while (true) {
			cout << "Input search string. Type 'exit' to stop. Type 'p' to print dictionary.\n";
			string searchstring;
			getline(cin, searchstring);

			if (searchstring == "exit")
				break;
			if (searchstring == "p") {
				map.print();
				continue;
			}

			start = clock();
			vector<pair<string, int>> * result = tree.Search(searchstring, 1);
			duration = clock() - start;
			cout << endl;
			cout << "Search time in tree : " << duration / CLOCKS_PER_SEC << "\n";

			for (vector<pair<string, int>>::iterator it = result->begin(); it != result->end(); it++) {
				cout << it->first << " dist : " << it->second << endl;
			}

		}
	
	int i;
	cin >> i;
}