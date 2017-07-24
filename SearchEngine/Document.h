#include <string>

using namespace std;

class Document
{
public:
	Document(string nm, Document * nxt);
	~Document();

	string name;
	Document * next;
};

