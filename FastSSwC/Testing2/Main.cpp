#include "FastSSwC.h"
#include "JSONImporter.h"
#include "TextImporter.h"
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {

	string filename = argv[1], word, dt;

	//taking 29 mb
	//unordered_map<string, unordered_map<string, string>> map;
	unordered_map<string, unordered_set<string>> map;

	JSONImporter import(filename, &map);
	FastSSwC ss(&map, 2);

	while (true) {
		cout << "input search string. type 'exit' to stop. type 'p' to print dictionary.\n";
		string searchstring;
		getline(cin, searchstring);

		if (searchstring == "exit")
			break;

		ss.Search(searchstring);
	}

	int i;
	cin >> i;
}