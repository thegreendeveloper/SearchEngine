#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class FastSSwC {
public:
	FastSSwC(unordered_set<string> * map, int k);
	~FastSSwC();

	vector<string> Search(string input);
	void SubstringDeletion(string word, vector<string> * stringVector);
	void SubstringDeletionRecurse(int k, string word, unordered_set<string> * stringVector);
private:
	void initialize(int k);

	unordered_set<string> * map;
	unordered_map<string, unordered_set<string>> * invertedSubStrings;

};

