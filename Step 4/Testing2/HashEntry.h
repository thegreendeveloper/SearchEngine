#ifndef HashEntry_HEADER
#define HashEntry_HEADER

#include <iostream>
//#include "ValueEntry.h"
#include "HashMapVE.h"

using namespace std;

class HashEntry
{
public:
	HashEntry(string key, string valueEntry, HashEntry * next);
	~HashEntry();

	string getKey();
	HashEntry * getNext();
	//ValueEntry * getValueEntry();
	HashMapVE * getValueEntries();

	void setNext(HashEntry * next);

private:
	string key;
	HashEntry * next; /*Linked list of hashEntries aka. chained hashing*/
	//ValueEntry * valueEntry; /*Linked list of documents*/
	HashMapVE * entries;
};
#endif

