#include "HashEntry.h"
#include "ValueEntry.h"
#include <string>
#include <iostream>

using namespace std;

const int DEFAULT_TABLE_SIZE = 128;
const double DENSITY_THRESHOLD = 0.75;

class HashMap
{
private:
	HashEntry **table;
	int tableSize = 0;
	int MAX_ENTRIES = 0;	

	void initialize(int tbSz);
	void handleCollision(HashEntry * tablePointer, string key, string dt);
	void insertValueEntry(ValueEntry * initial, string dt);	
	void reHashMap();
	void InsertReHashValueEntries(string key, ValueEntry * initial, HashMap * newT);
	

public:
	HashMap(int tbSz);
	
	HashEntry **getTable();
	HashEntry * get(string key);
	
	int getTableSize();
	void put(string key, string dt);
	void print();
	
	~HashMap();
	
	int MAX_NO_OF_COLLISIONS, NO_OF_ENTRIES;
};

