#include "HashMapHE.h"
#include <vector>

class TrigramSimilarityMeasure {
public:
	TrigramSimilarityMeasure(HashMapHE * map);
	~TrigramSimilarityMeasure();

	void Search(string input);
	HashMapHE * CreateThreeGramInverted();
private:
	void NGramSplit(int ngram, string word, vector<string> * stringVector);
	void TrigramSimilarity(vector<string> * inputTrigram, HashMapHE * invertedTrigram, HashMapVE * resultSet);

	HashMapHE * map;
	HashMapHE * dictionaryThreeGrams;
};

