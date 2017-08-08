#include "HashEntry.h"
#include "HashMapHE.h"
#include "Utilities.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1], word, dt;
	HashMapHE map(0);
	
	Utilities::ImportFile(filename,&map);

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
		
		cout << endl;
	}

}