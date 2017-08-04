#pragma once
#include "HashMapAbs.h"
#include "ValueEntry.h"
#include <iostream>

using namespace std; 

class HashMapVE : public HashMapAbs
{
private:
	ValueEntry **table;
	int tableSize = 0;
	int MAX_ENTRIES = 0;

	void initialize(int tbSz);
	void handleCollision(ValueEntry * tablePointer, string key);
	void reHashMap();
	

public:
	HashMapVE(int tbSz);

	ValueEntry **getTable();
	ValueEntry * get(string key);

	int getTableSize();
	void put(string key);
	void print();

	~HashMapVE();
};

