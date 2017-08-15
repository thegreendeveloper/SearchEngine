#include "ValueEntry.h"


ValueEntry::ValueEntry(string nm, ValueEntry * nxt)
{
	key = nm;
	next = nxt;
	occ = 1;
}

ValueEntry * ValueEntry::getNext() {
	return next;
}

string ValueEntry::getKey() {
	return key;
}

int ValueEntry::getOcc() {
	return occ;
}

void ValueEntry::setNext(ValueEntry * next) {
	this->next = next;
}

void ValueEntry::setOcc(int newOcc) {
	occ = newOcc;
}
ValueEntry::~ValueEntry()
{
	delete next;
}
