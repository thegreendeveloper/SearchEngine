#ifndef HashEntry_HEADER
#define HashEntry_HEADER

#include <iostream>
#include "HashMapVE.h"

using namespace std;

class HashEntry
{
public:
	HashEntry(string key, string valueEntry, HashEntry * next);
	~HashEntry();

	string getKey();
	HashEntry * getNext();
	HashMapVE * getValueEntries();

	void setNext(HashEntry * next);

private:
	string key;
	HashEntry * next; /*Linked list of hashEntries aka. chained hashing*/
	HashMapVE * entries;
};
#endif

