#include <ctime>
#include <iostream>

#include "HashEntry.h"
#include "HashMap.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << argv[1] << "\n";
	clock_t start = clock();
	string filename = argv[1], word, dt;

	HashMap map(0);

	FILE * file = NULL;
	char buf[1024];
	
	if (fopen_s(&file, filename.c_str(), "r") == 0) {
		while (fscanf_s(file, "%s", buf, sizeof(buf)) != EOF)
		{
			word = buf;
			if (dt == "")
				dt = word;
			if (word == "---END.OF.DOCUMENT---") {
				dt = "";
				continue;
			}
			map.put(word, dt);
		}
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

		HashEntry * result = map.get(searchstring);
		if (result != NULL) {
			cout << searchstring << " exists in the documents: " << endl;
			ValueEntry * current = result->getValueEntry();
			while (current != NULL)
			{
				cout << current->getDocumentName() << endl;
				if (current->getNext() == NULL)
					break;
				current = current->getNext();
			}
		}
		else
			cout << searchstring << " does not exist!\n";

	}

}