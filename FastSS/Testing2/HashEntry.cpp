#include "HashEntry.h"

HashEntry::HashEntry(string key, string valueEntry, HashEntry * next) {
	this->key = key;
	entries = new HashMapVE(0);
	entries->put(valueEntry);
	this->next = next;
}

HashEntry::~HashEntry()
{
	delete entries;
	delete next;
}

string HashEntry::getKey() {
	return key;
}

HashEntry * HashEntry::getNext() {
	return next;
}

HashMapVE * HashEntry::getValueEntries() {
	return entries;
}

void HashEntry::setNext(HashEntry * next) {
	this->next = next;
}

