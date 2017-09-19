#include "Utilities.h"
#include <algorithm>

void Utilities::sort(vector<string> &resultSet, unordered_map<string, double> * entries)
{
	/*Initializing*/
	int arrSize = entries->size();
	int* arrOcc = new int[arrSize];
	string* arrKey = new string[arrSize];

	for (int i = 0; i < arrSize; i++) {
		arrOcc[i] = 0;
		arrKey[i] = "";
	}

	///*inserting values; document name and occurence, into temp arrays*/
	int counter = 0;
	for (unordered_map<string, double>::iterator it = entries->begin(); it != entries->end(); it++) {
		arrKey[counter] = it->first;
		arrOcc[counter] = (int)it->second;
		counter++;
	}


	int maxVal = getMaximumValue(arrOcc, entries->size());
	///*Implementation of countsort, which can be used in radix sort*/
	for (int exp = 1; maxVal / exp > 0; exp *= 10)
		countSort(arrOcc, arrKey, arrSize, exp);

	for (int i = 0; i < entries->size(); i++)
		resultSet.push_back(arrKey[i] + " : " + to_string(arrOcc[i]));

	delete[] arrOcc;
	delete[] arrKey;
}


void Utilities::countSort(int arrOcc[], string arrKey[], int n, int exp)
{
	string* outputKey = new string[n];
	int* output = new int[n];

	for (int i = 0; i < n; i++) {
		output[i] = 0;
	}

	int i, count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < n; i++)
		count[(arrOcc[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--)
	{
		int value = count[(arrOcc[i] / exp) % 10] - 1;
		output[value] = arrOcc[i];
		outputKey[value] = arrKey[i];
		count[(arrOcc[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++) {
		arrOcc[i] = output[i];
		arrKey[i] = outputKey[i];
	}

	delete[] outputKey;
	delete[] output;

}

int Utilities::getMaximumValue(int arr[], int NoOfEntries) {
	int maxValue = arr[0];
	for (int i = 1; i < NoOfEntries; i++) {
		if (maxValue < arr[i])
			maxValue = arr[i];
	}
	return maxValue;
}


/*Non - recursive method : O(n ^ 2) time.O(n) space.*/
int Utilities::LevenshteinDistance(string s, int n, string t, int m) {
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
int Utilities::LevenshteinDamerauDistance(string s, int n, string t, int m) {
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

			current[i] = min(current[i - 1] + 1, min(previous[i - 1] + cost, previous[i] + 1));

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

void Utilities::print(vector<string> * resultSet, int noOfLines, bool reverse, string outputText) {
	int counter = 0;
	cout << outputText << endl;

	if (reverse) {
		for (vector<string>::reverse_iterator it = resultSet->rbegin(); it != resultSet->rend(); it++) {
			cout << *it << endl;
			counter++;
			if (counter > noOfLines)
				break;
		}
	}
	else {
		cout << "Sugestions based on FastSSwC :" << endl;
		for (vector<string>::iterator it = resultSet->begin(); it != resultSet->end(); it++) {
			cout << *it << endl;
			counter++;
			if (counter > noOfLines)
				break;
		}	
	}
	cout << endl;

}