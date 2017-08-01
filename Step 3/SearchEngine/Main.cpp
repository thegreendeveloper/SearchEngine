#include <ctime>
#include <iostream>
#include "Index2.h"
#include "WikiItem.h"
using namespace std;


int main(int argc, char* argv[]) {
	cout << argv[1] << "\n";
	
	clock_t start = clock();
	Index2 i = Index2(argv[1]);
	clock_t duration = clock() - start;
	cout << "Duration : " << duration / CLOCKS_PER_SEC << "\n";

	while (true) {
		cout << "Input search string or type exit to stop\n";
		string searchstring;
		cin >> searchstring;

		if (searchstring == "exit")
			break;

		if (i.Search(searchstring))
			cout << searchstring << " exists!\n";
		else
			cout << searchstring << " does not exist!\n";

	}

	return 0;
}


