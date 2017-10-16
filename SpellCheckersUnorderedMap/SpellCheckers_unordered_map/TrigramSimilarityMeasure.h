#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class TrigramSimilarityMeasure {
public:
	TrigramSimilarityMeasure(unordered_map<string, unordered_set<string>> * map);
	~TrigramSimilarityMeasure();

	void Search(string input);
	unordered_map<string, unordered_set<string>> * CreateThreeGramInverted();
private:
	void NGramSplit(int ngram, string word, vector<string> * stringVector);
	void TrigramSimilarityMeasure::insertWord(string word, string document, unordered_map<string, unordered_set<string>> * map);
	void TrigramSimilarity(vector<string> * inputTrigram, unordered_map<string, unordered_set<string>> * invertedTrigram, unordered_map<string, double> * resultSet);

	unordered_map<string, unordered_set<string>> * map;//HashMapHE * map;
	unordered_map<string, unordered_set<string>> * dictionaryThreeGrams;
};

