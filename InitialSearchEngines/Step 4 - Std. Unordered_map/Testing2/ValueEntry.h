#ifndef ValueEntry_HEADER
#define ValueEntry_HEADER

#include <string>

using namespace std;

class ValueEntry
{
public:
	ValueEntry(string key, ValueEntry * nxt);
	~ValueEntry();

	ValueEntry * getNext();
	string getKey();

	void setNext(ValueEntry * next);
private:
	string key;
	ValueEntry * next;
};
#endif