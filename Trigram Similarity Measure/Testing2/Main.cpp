#include "HashEntry.h"
#include "HashMapHE.h"
#include "Utilities.h"
#include "TrigramSimilarityMeasure.h"
#include "JSONImporter.h"
#include "TextImporter.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1], word, dt;

	HashMapHE map(0);	
	JSONImporter import(filename, &map);
	TrigramSimilarityMeasure tsm(&map);

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
			
		tsm.Search(searchstring);
	}
	

	int i;
	cin >> i;
}