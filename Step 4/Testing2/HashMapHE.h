#include "HashEntry.h"
#include "ValueEntry.h"
#include <string>
#include <iostream>
#include "HashMapAbs.h"

using namespace std;

class HashMapHE : public HashMapAbs
{
private:
	HashEntry **table;
	int tableSize = 0;
	int MAX_ENTRIES = 0;	

	void initialize(int tbSz);
	void handleCollision(HashEntry * tablePointer, string key, string dt);
	void insertValueEntry(ValueEntry * initial, string dt);	
	void reHashMap();
	//void InsertReHashValueEntries(string key, ValueEntry * initial, HashMapHE * newT);
	void InsertReHashValueEntries(HashMapHE * newT, HashMapVE * oldEntries, string key);

public:
	HashMapHE(int tbSz);
	
	HashEntry **getTable();
	HashEntry * get(string key);
	
	int getTableSize();
	void put(string key, string dt);
	void print();
	
	~HashMapHE();
		
};

