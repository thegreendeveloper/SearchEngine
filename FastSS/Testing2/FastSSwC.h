#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class FastSSwC {
public:
	FastSSwC(unordered_map<string, unordered_map<string, string>> * map, int k);
	~FastSSwC();

	void Search(string input);
	void SubstringDeletion(string word, vector<string> * stringVector);
	void SubstringDeletionRecurse(int k, string word, unordered_set<string> * stringVector);
private:
	void initialize(int k);

	//HashMapHE * map;
	//HashMapHE * invertedSubStrings;
	unordered_map<string, unordered_map<string, string>> * map;
	unordered_map<string, unordered_map<string, double>> * invertedSubStrings;

};

