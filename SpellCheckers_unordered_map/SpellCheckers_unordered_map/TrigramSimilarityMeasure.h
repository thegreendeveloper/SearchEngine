#include <vector>
#include <unordered_map>

using namespace std;

class TrigramSimilarityMeasure {
public:
	TrigramSimilarityMeasure(unordered_map<string, unordered_map<string, string>> * map);
	~TrigramSimilarityMeasure();

	void Search(string input);
	unordered_map<string, unordered_map<string, string>> * CreateThreeGramInverted();
private:
	void NGramSplit(int ngram, string word, vector<string> * stringVector);
	void TrigramSimilarityMeasure::insertWord(string word, string document, unordered_map<string, unordered_map<string, string>> * map);
	void TrigramSimilarity(vector<string> * inputTrigram, unordered_map<string, unordered_map<string, string>> * invertedTrigram, unordered_map<string, double> * resultSet);

	unordered_map<string, unordered_map<string, string>> * map;//HashMapHE * map;
	unordered_map<string, unordered_map<string, string>> * dictionaryThreeGrams;
};

