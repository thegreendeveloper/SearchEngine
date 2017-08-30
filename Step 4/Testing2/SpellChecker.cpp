#include "SpellChecker.h"
#include <algorithm>

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
	int* distance = new int[n + 1];
	for (int i = 0; i < n + 1; i++)
		distance[i] = i;

	int* current = new int[n + 1];
	int cost = 0;

	for (int j = 1; j < m + 1; j++) { // iterate through each row
		for (int i = 1; i < n + 1; i++) { // iterate through each column
			if (i == 1)
				current[0] = j;

			if (s[i - 1] == t[j - 1])
				cost = 0;
			else
				cost = 1;

			current[i] = min(current[i - 1] + 1, min(distance[i] + 1, distance[i - 1] + cost));
			//cout << current[i-1] << " ";
		}
		//cout << current[n] << endl;

		for (int i = 0; i < n + 1; i++)
			distance[i] = current[i];
	}

	cost = distance[n];

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
	int* thirdPrevious = new int[n + 1];
	int* previous = new int[n + 1];
	int* current = new int[n + 1];

	for (int i = 0; i < n + 1; i++)
		previous[i] = i;

	int cost = 0;

	for (int j = 1; j < m + 1; j++) { // iterate through each row
		for (int i = 1; i < n + 1; i++) { // iterate through each column
			if (i == 1)
				current[0] = j;

			if (s[i - 1] == t[j - 1])
				cost = 0;
			else
				cost = 1;

			current[i] = min(current[i-1]+1, min(previous[i-1]+cost, previous[i]+1));

			if ((i > 1 && j > 1) && (s[i - 1] == t[j - 2]) && (s[i - 2] == t[j - 1])) /*Damerau specific : transposition part*/
				current[i] = min(current[i], thirdPrevious[i - 2] + cost);
		}
		for (int i = 0; i < n + 1; i++) {
			thirdPrevious[i] = previous[i];
			previous[i] = current[i];
		}
	}

	cost = current[n];

	delete[] current;
	delete[] previous; 
	delete[] thirdPrevious;

	return cost;
}

HashMapHE * SpellChecker::CreateThreeGramInverted() {
	HashMapHE * ngramsDataSet = new HashMapHE(0);
	for (int i = 0; i < map->getTableSize(); i++) {

		HashEntry * currentHashEntry = map->getTable()[i];		
		while (currentHashEntry != NULL) {
			
			//Split string into n-grams 
			vector<string> * threeGramsWord = new vector<string>();
			ThreeGramSplit(currentHashEntry->getKey(), threeGramsWord);

			//for each three grams in the vector insert three gram into ngramsDataSet and insert the word as well.
			for (vector<string>::iterator it = threeGramsWord->begin(); it != threeGramsWord->end(); it++) {
				ngramsDataSet->put(*it, currentHashEntry->getKey());
			}

			delete threeGramsWord;

			if (currentHashEntry->getNext() == NULL)
				break;
			currentHashEntry = currentHashEntry->getNext();
		}
	}
	return ngramsDataSet;
}


void SpellChecker::TrigramSimilarity(vector<string> * inputTrigram, HashMapHE * invertedTrigram, HashMapVE * resultSet) {
	for (vector<string>::iterator it = inputTrigram->begin(); it != inputTrigram->end(); it++) {
		HashEntry * current = invertedTrigram->get(*it);
		if (current != NULL) {
			/*three grams exist in our dictionary. for each word the three gram exist in,
			we want to add it to our hashmapve and increment the counter*/
			HashMapVE * currentwords = current->getValueEntries();
			for (int i = 0; i < currentwords->getTableSize(); i++) {
				ValueEntry * currentVE = currentwords->getTable()[i];
				while (currentVE != NULL) {
					resultSet->put(currentVE->getKey());

					if (currentVE->getNext() == NULL)
						break;
					currentVE = currentVE->getNext();
				}
			}
		}
	}

}
void SpellChecker::ThreeGramSplit(string word, vector<string> * stringVector) {
	if (word.length() <= 3)
		stringVector->push_back(word);
	else {
		for (int i = 0; i < word.length(); i++) {
			if (i == 0) {
				stringVector->push_back("$$"+word.substr(i, 1));
				stringVector->push_back("$"+word.substr(i, 2));
				stringVector->push_back(word.substr(i, 3));
			}else if(i == word.length()-2)
				stringVector->push_back(word.substr(i, 2)+"$");
			else if(i == word.length()-1)
				stringVector->push_back(word.substr(i, 1) + "$$");
			else
				stringVector->push_back(word.substr(i, 3));
		}
	}
}
SpellChecker::~SpellChecker()
{

}
