#include "Index.h"



Index::Index(HashMapHE * map)
{
	/*Initialize global map*/
	this->map = map;

	/*build suffix tree*/
	/*Ranking would  require some restructuring of the documents or maybe this should be done when creating the map*/
}


Index::~Index()
{
}

void Index::Search(string searchstring) {
	/*TODO :: printing out the rresults in the search engine*/
	//vector<string> searchStrings = destructSearchString(searchstring);

	//for (vector<string>::iterator it = searchStrings.begin(); it != searchStrings.end(); it++) {
		//cout << *it << endl;
		HashEntry * result = map->get(searchstring);
		if (result != NULL) {
			cout << searchstring << " exists in the documents: " << endl;
			HashMapVE * entries = result->getValueEntries();
			entries->print();
		}
		else
			cout << searchstring << " does not exist!\n";

		cout << endl;
	//}
}

vector<string> Index::destructSearchString(string searchString) {
	vector<string> result;
	size_t pos = searchString.find("AND");
	if (pos == -1) {
		result.push_back(searchString);
		return result;
	}
	string current = searchString;
	while (pos != -1) {

		if (current.substr(0,1) == " ")
			cout << "test" << endl;
		//	current = current.substr(1, pos);
		//if(current[pos] == ' ')
		//	current = current.substr(0, pos-1);

		result.push_back(current.substr(0, pos));
		current = current.substr(pos+3,current.length());
		pos = current.find("AND");
	}
	result.push_back(current);

	return result;
}
