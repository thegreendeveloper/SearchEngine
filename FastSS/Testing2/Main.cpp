#include "FastSSwC.h"
#include "JSONImporter.h"
#include "TextImporter.h"
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {

	string filename = argv[1], word, dt;

	unordered_map<string, unordered_map<string, string>> map;

	JSONImporter import(filename, &map);

	clock_t start = clock();
	FastSSwC ss(&map, 2);

	clock_t duration = clock() - start;
	cout << endl;
	cout << "Duration building deletion map " << duration / CLOCKS_PER_SEC << "\n";

	cout << "calculating average length" << endl;
	double avg = 0;
	for(unordered_map<string, unordered_map<string, string>>::iterator it = map.begin(); it != map.end(); it++)
		avg += it->first.length();

	cout << "average str size : " << avg / map.size() << endl;

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