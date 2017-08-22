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

	void Levenshtein();

private:
	//vector<string> dictionary;
	HashMapHE * map;
	HashMapVE * resultSet;

	string input;
	int MAX_DISTANCE;

	int LevenshteinDistance(string s, int len_s, string t, int len_t);

};

