#include "Utilities.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	string filename = argv[1];
	
	unordered_map<string, unordered_map<string,string>> map;

	Utilities::ImportFile(filename,&map);

	while (true) {
		cout << "Input search string or type exit to stop\n";
		string searchstring;
		cin >> searchstring;

		if (searchstring == "exit")
			break;

		unordered_map<string, unordered_map<string, string>>::const_iterator got = map.find(searchstring);
		if (got == map.end())
			cout << searchstring << " does not exist!\n";
		else {
			unordered_map<string, string> result = got->second;
			for (unordered_map<string, string>::iterator it = result.begin(); it != result.end(); ++it) {
				cout << it->first << endl;
			}
			
		}
		
		cout << endl;
	}

}