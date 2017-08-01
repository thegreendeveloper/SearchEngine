#include "ValueEntry.h"


ValueEntry::ValueEntry(string nm, ValueEntry * nxt)
{
	documentName = nm;
	next = nxt;
}

ValueEntry * ValueEntry::getNext() {
	return next;
}

string ValueEntry::getDocumentName() {
	return documentName;
}

void ValueEntry::setNext(ValueEntry * next) {
	this->next = next;
}
ValueEntry::~ValueEntry()
{
	delete next;
}
