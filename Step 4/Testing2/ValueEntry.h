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
	int getOcc();

	void setNext(ValueEntry * next);
	void setOcc(int newOcc);
private:
	string key;
	ValueEntry * next;
	int occ;
};
#endif