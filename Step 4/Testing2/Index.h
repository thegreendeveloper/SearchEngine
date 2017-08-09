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
	HashMapHE * map;
};

