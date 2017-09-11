#include "HashEntry.h"
#include "HashMapHE.h"
#include "Utilities.h"
#include "FastSS.h"

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1], word, dt;

	HashMapHE map(0);	
	if (Utilities::ImportFile(filename, &map)) {

		clock_t start = clock();
		FastSS ss(&map);
		clock_t duration = clock() - start;
		cout << endl;
		cout << "Duration building the suffix inverted file : " << duration / CLOCKS_PER_SEC << "\n";
		
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
	}

	

	int i;
	cin >> i;
}