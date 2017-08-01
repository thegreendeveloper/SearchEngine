#include "HashEntry.h"

HashEntry::HashEntry(string key, ValueEntry * valueEntry, HashEntry * next) {
	this->key = key;
	this->valueEntry = valueEntry;
	this->next = next;
}

HashEntry::~HashEntry()
{
	delete valueEntry;
	delete next;
}

string HashEntry::getKey() {
	return key;
}

HashEntry * HashEntry::getNext() {
	return next;
}

ValueEntry * HashEntry::getValueEntry() {
	return valueEntry;
}
void HashEntry::setNext(HashEntry * next) {
	this->next = next;
}

