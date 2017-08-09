#include "HashEntry.h"
#include "HashMapHE.h"
#include "Utilities.h"
#include "Index.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1], word, dt;

	HashMapHE map(0);	
	Utilities::ImportFile(filename,&map);
	Index index(&map);

	while (true) {
		cout << "Input search string or type exit to stop\n";
		string searchstring;
		getline(cin, searchstring);

		if (searchstring == "exit")
			break;
		index.Search(searchstring);
	}

}