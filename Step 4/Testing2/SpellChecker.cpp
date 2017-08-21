#include "SpellChecker.h"
#include <algorithm>
#include "RaddixSort.h"

SpellChecker::SpellChecker(string input, HashMapHE * map)
{
	this->input = input;
	for (int i = 0; i < map->getTableSize(); i++) {
		if (map->getTable()[i] != NULL) {
			dictionary.push_back(map->getTable()[i]->getKey());
		}
	}
	/*TODO: We just pick an initial distance. The perfect distance needs to be considered.*/
	MAX_DISTANCE = 3;
	resultSet = new HashMapVE(0);
}


void SpellChecker::Levenshtein() {

	for (vector<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++) {
		string word = *it;
		int distance = LevenshteinDistance(input, input.length(), word, word.length());
		resultSet->put(word);
		resultSet->get(word)->setOcc(distance);
	}

	cout << "Did you mean: " << endl;
	RaddixSort radix;
	radix.sort(resultSet);

}

/*Non-recursive method :  O(n^2) time. O(n) space.*/
int SpellChecker::LevenshteinDistance(string s, int n, string t, int m) {
	if (n == 0)
		return m;
	if (m == 0)
		return n;

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
				current[i] = min(current[i - 1], min(distance[i], distance[i - 1])) + cost;
			else
				current[i] = distance[i] + cost;
		}

		for (int i = 0; i < n; i++)
			distance[i] = current[i];

		/*for (int i = 0; i < n; i++) {
			cout << distance[i] << " ";
		}
		cout << endl;*/
	}

	cost = distance[n - 1];

	delete distance;
	delete current;

	return cost;
}

SpellChecker::~SpellChecker()
{

}
