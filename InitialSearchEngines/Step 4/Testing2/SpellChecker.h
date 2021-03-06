#pragma once
#include <string>
#include <vector>

#include "HashMapHE.h"

using namespace std;

class SpellChecker
{
public:
	SpellChecker(string input, HashMapHE * map);
	~SpellChecker();

	HashMapVE * Levenshtein(bool damerau);
	HashMapHE * CreateThreeGramInverted();
	HashMapVE * Faroos();

	void TrigramSimilarity(vector<string> * inputTrigram, HashMapHE * invertedTrigram, HashMapVE * resultSet);
	void NGramSplit(int ngram, string word, vector<string> * stringVector);

	static void SubstringDeletion(int k, string word, vector<string> * stringVector);
private:
	HashMapHE * map;
	
	string input;
	int MAX_DISTANCE;

	int LevenshteinDistance(string s, int len_s, string t, int len_t);
	int LevenshteinDamerauDistance(string s, int len_s, string t, int len_t);

};

