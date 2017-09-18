#include <string>
#include "Document.h"

using namespace std;

class WikiItem2
{
public:
	WikiItem2();
	WikiItem2(string s, Document * dcm, WikiItem2 * n);
	~WikiItem2();

	string str;
	Document * document;
	WikiItem2 * next;
};

