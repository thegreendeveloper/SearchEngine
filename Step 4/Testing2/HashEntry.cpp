#include "HashEntry.h"

HashEntry::HashEntry(string key, string valueEntry, HashEntry * next) {
	this->key = key;
	//this->valueEntry = valueEntry;
	entries = new HashMapVE(0);
	entries->put(valueEntry);
	this->next = next;
}

HashEntry::~HashEntry()
{
	//delete valueEntry;
	delete entries;
	delete next;
}

string HashEntry::getKey() {
	return key;
}

HashEntry * HashEntry::getNext() {
	return next;
}

//ValueEntry * HashEntry::getValueEntry() {
//	return valueEntry;
//}
HashMapVE * HashEntry::getValueEntries() {
	return entries;
}

void HashEntry::setNext(HashEntry * next) {
	this->next = next;
}

