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
	double getOcc();

	void setNext(ValueEntry * next);
	void setOcc(double newOcc);
private:
	string key;
	ValueEntry * next;
	double occ;
};
#endif