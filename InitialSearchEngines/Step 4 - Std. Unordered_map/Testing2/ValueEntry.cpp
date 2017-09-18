#include "ValueEntry.h"


ValueEntry::ValueEntry(string nm, ValueEntry * nxt)
{
	key = nm;
	next = nxt;
}

ValueEntry * ValueEntry::getNext() {
	return next;
}

string ValueEntry::getKey() {
	return key;
}

void ValueEntry::setNext(ValueEntry * next) {
	this->next = next;
}
ValueEntry::~ValueEntry()
{
	delete next;
}
