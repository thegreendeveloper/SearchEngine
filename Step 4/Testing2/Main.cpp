#include "HashEntry.h"
#include "HashMapHE.h"
#include "Utilities.h"
#include "Index.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1], word, dt;

	HashMapHE map(0);	
	if (Utilities::ImportFile(filename, &map)) {
		Index index(&map);

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
			index.Search(searchstring);
		}
	}
	else {
		int i;
		cin >> i;
	}
}