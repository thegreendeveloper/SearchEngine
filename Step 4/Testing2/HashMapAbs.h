#pragma once
#include <string>

using namespace std;

class HashMapAbs
{

public:	
	virtual int getTableSize() = 0;
	virtual void print() = 0;

	const int DEFAULT_TABLE_SIZE = 2;
	const double DENSITY_THRESHOLD = 0.75;
	int MAX_NO_OF_COLLISIONS, NO_OF_ENTRIES;

private:
	virtual void initialize(int tbSz) = 0;
	virtual void reHashMap() = 0;

	
};

