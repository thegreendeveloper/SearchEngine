#include "TrigramSimilarityMeasure.h"
#include "Utilities.h"

TrigramSimilarityMeasure::TrigramSimilarityMeasure(unordered_map<string, unordered_set<string>> * map)
{
	this->map = map;
	cout << "Creating Three Gramm inverted file of entire dictionary (preprossesing)..." << endl;
	dictionaryThreeGrams = CreateThreeGramInverted();
}

TrigramSimilarityMeasure::~TrigramSimilarityMeasure(){}

void TrigramSimilarityMeasure::Search(string input) {
	/*PostProcessing : breaking input intro threegrams, iterating over each three grams 
	doing similarity scores for each of the dictionary words*/
	vector<string> * inputTrigram = new vector<string>();
	NGramSplit(3, input, inputTrigram);

	unordered_map<string, double> * resultSet = new unordered_map<string, double>();

	// Applying trigram similarity meassure
	TrigramSimilarity(inputTrigram, dictionaryThreeGrams, resultSet);
	
	vector<string> result;
	Utilities::sort(result, resultSet);
	Utilities::print(&result,10,true,"Sugestions based on Trigram Similarity : ");

	delete resultSet;
	delete inputTrigram;
}

void TrigramSimilarityMeasure::TrigramSimilarity(vector<string> * inputTrigram, 
	unordered_map<string, unordered_set<string>> * invertedTrigram, unordered_map<string, double> * resultSet)
{
	for (vector<string>::iterator it = inputTrigram->begin(); it != inputTrigram->end(); it++) {
		auto trigramIter = invertedTrigram->find(*it);

		/*three grams exist in our dictionary. for each word the three gram exist in,
		we want to add it to our hashmapve and increment the counter*/
		if (trigramIter != invertedTrigram->end()) {
			
			for (string element : trigramIter->second) {
				auto wordIter = resultSet->find(element);
				if (wordIter != resultSet->end()) {
					wordIter->second++;
				}else
					resultSet->insert(make_pair(element,1));
			}
		}
	}

	/*Calculated dice coefficient. Every word consist of n+2 trigrams. Multiplying by 100.*/
	for (unordered_map<string, double>::iterator it = resultSet->begin(); it != resultSet->end();it++) {
		it->second = (2 * it->second) / (inputTrigram->size() + it->first.length() + 2) * 100;		
	}
}


unordered_map<string, unordered_set<string>>  * TrigramSimilarityMeasure::CreateThreeGramInverted() {
		unordered_map<string, unordered_set<string>> * ngramsDataSet = new unordered_map<string, unordered_set<string>>();

	for (unordered_map<string, unordered_set<string>>::iterator it = map->begin(); it != map->end();it++) {
		vector<string> * threeGramsWord = new vector<string>();
		//Split string into n-grams 
		NGramSplit(3, it->first, threeGramsWord);

		//for each three grams in the vector insert three gram into ngramsDataSet and insert the word as well.
		for (vector<string>::iterator threegram = threeGramsWord->begin(); threegram != threeGramsWord->end(); threegram++) {
			insertWord(*threegram, it->first, ngramsDataSet);
		}
		delete threeGramsWord;
	}
	return ngramsDataSet;
}




/*Overlapping ngram split. Spaces are filled out with $
//Performance :
//word length 4, iteration : 200000, 18 sec.
//word length 16, iteration : 200000, 38 sec. */
void TrigramSimilarityMeasure::NGramSplit(int ngram, string word, vector<string> * stringVector) {

	for (int index = 0; index < word.length(); index++) {
		if (index == word.length())
			return;

		if (index - ngram + 1 < 0) {
			string concatinated;
			int upper = (ngram - index - 1);
			for (int i = 0; i < upper; i++)
				concatinated += "$";
			concatinated += word.substr(0, index + 1);
			stringVector->push_back(concatinated);
		}

		if (index + ngram > word.length()) {
			string concatinated = word.substr(index, ngram);
			int upper = index + ngram - word.length();
			for (int i = 0; i < upper; i++) {
				concatinated += "$";
			}
			stringVector->push_back(concatinated);
		}

		if (index + ngram <= word.length())
			stringVector->push_back(word.substr(index, ngram));
	}
}


void TrigramSimilarityMeasure::insertWord(string word, string document, unordered_map<string, unordered_set<string>> * map) {
	auto iter = map->find(word);
	if (iter == map->end()) {
		unordered_set<string> documents;
		documents.insert(document);
		map->insert(make_pair(word, documents));
	}
	else {
		auto iter = map->at(word).find(document);
		if (iter == map->at(word).end()) {
			map->at(word).insert(document);
		}

	}

}
