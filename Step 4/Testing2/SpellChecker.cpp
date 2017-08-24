#include "SpellChecker.h"
#include <algorithm>
#include "RaddixSort.h"

SpellChecker::SpellChecker(string input, HashMapHE * map)
{
	this->input = input;
	this->map = map;

	/*TODO: We just pick an initial distance. The perfect distance needs to be considered.*/
	MAX_DISTANCE = 3;

}


HashMapVE *  SpellChecker::Levenshtein(bool damerau) {
	HashMapVE * resultSet = new HashMapVE(0);
	int distance = 0;

	for (int i = 0; i < map->getTableSize(); i++) {
		if (map->getTable()[i] != NULL) {
			string word = map->getTable()[i]->getKey();
			if (damerau)
				distance = LevenshteinDamerauDistance(input, input.length(), word, word.length());
			else
				distance = LevenshteinDistance(input, input.length(), word, word.length());

			if (distance < MAX_DISTANCE) {
				resultSet->put(word);
				resultSet->get(word)->setOcc(distance);
			}
		}
	}
	return resultSet;
}

/*Non-recursive method :  O(n^2) time. O(n) space.*/
int SpellChecker::LevenshteinDistance(string s, int n, string t, int m) {
	if (n == 0)
		return m;
	if (m == 0)
		return n;

	/*initializing*/
	int* distance = new int[n];
	for (int i = 0; i < n; i++)
		distance[i] = i;

	int* current = new int[n];
	int cost = 0;

	for (int j = 0; j < m; j++) { // iterate through each row
		for (int i = 0; i < n; i++) { // iterate through each column

			if (s[i] == t[j])
				cost = 0;
			else
				cost = 1;

			if (i > 0 && j > 0)
				current[i] = min(current[i - 1] + 1, min(distance[i] + 1, distance[i - 1] + cost));
			else
				current[i] = distance[i] + cost;
		}

		for (int i = 0; i < n; i++)
			distance[i] = current[i];
	}

	cost = distance[n - 1];

	delete[] distance;
	delete[] current;

	return cost;
}

/*Non-recursive method :  O(n^2) time. O(n^2) space.*/
//TODO : Optimize on space!!
int SpellChecker::LevenshteinDamerauDistance(string s, int n, string t, int m) {
	if (n == 0)
		return m;
	if (m == 0)
		return n;

	/*initializing*/
	int** distance = new int*[n];

	for (int i = 0; i < n + 1; i++) {
		distance[i] = new int[m + 1];
		distance[i][0] = i;
	}
	for (int j = 0; j < m + 1; j++) {
		distance[0][j] = j;
	}

	int cost = 0;

	for (int j = 1; j < m + 1; j++) { // iterate through each row
		for (int i = 1; i < n + 1; i++) { // iterate through each column

			if (s[i - 1] == t[j - 1])
				cost = 0;
			else
				cost = 1;

			distance[i][j] = min(distance[i - 1][j] + 1, min(distance[i - 1][j - 1] + cost, distance[i][j - 1] + 1));

			if ((i > 1 && j > 1) && (s[i - 1] == t[j - 2]) && (s[i - 2] == t[j - 1])) /*Damerau specific : transposition part*/
				distance[i][j] = min(distance[i][j], distance[i - 2][j - 2] + cost);
		}
	}

	cost = distance[n][m];

	for (int i = 0; i < n + 1; i++)
		delete[] distance[i];

	return cost;
}

SpellChecker::~SpellChecker()
{

}
