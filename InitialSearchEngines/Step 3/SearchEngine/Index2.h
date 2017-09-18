#include <string>
#include "WikiItem2.h"

using namespace std;

class Index2
{
public:
	Index2(string filename);
	void updateWikiItems(WikiItem2 * start, string word, string dt);
	bool Search(string searchname);
		
	WikiItem2 * start;
	
};

