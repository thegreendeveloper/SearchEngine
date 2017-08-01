#ifndef ValueEntry_HEADER
#define ValueEntry_HEADER

#include <string>

using namespace std;

class ValueEntry
{
public:
	ValueEntry(string nm, ValueEntry * nxt);
	~ValueEntry();

	ValueEntry * getNext();
	string getDocumentName();

	void setNext(ValueEntry * next);
private:
	string documentName;
	ValueEntry * next;
};
#endif