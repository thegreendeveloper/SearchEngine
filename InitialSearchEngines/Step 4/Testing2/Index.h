#pragma once
#include <vector>
#include "HashMapHE.h"

using namespace std;

class Index
{
public:
	Index(HashMapHE * map);
	~Index();
	void Search(string searchstring);

private:
	vector<string> destructSearchString(string searchString);
	void intersectSearchstring(vector<string> searchStrings);
	void initializeSpellChecker(string searchString);
	HashMapHE * map;

};

