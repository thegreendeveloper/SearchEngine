#include "HashMapHE.h"
#include <vector>


class FastSS {
public:
	FastSS(HashMapHE * map, int k);
	~FastSS();

	void Search(string input);
private:
	void SubstringDeletion(int k, string word, vector<string> * stringVector);
	void initialize();

	HashMapHE * map;
	HashMapHE * invertedSubStrings;
	int k;
};

