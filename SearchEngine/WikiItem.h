#include <string>
using namespace std;

class WikiItem
{
public:
	WikiItem();
	WikiItem(string s, string dt, WikiItem * n);
	~WikiItem();

	string str;
	string document_title;
	WikiItem * next;

};

