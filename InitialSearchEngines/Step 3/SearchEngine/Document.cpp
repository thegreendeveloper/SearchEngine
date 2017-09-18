#include "Document.h"


Document::Document(string nm, Document * nxt)
{
	name = nm;
	next = nxt;
}


Document::~Document()
{
}
