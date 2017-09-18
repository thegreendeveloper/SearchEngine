#include "Utilities.h"

void Utilities::sort(vector<string> &resultSet, HashMapVE * entries)
{
	/*Initializing*/
	int arrSize = entries->NO_OF_ENTRIES;
	int* arrOcc = new int[arrSize];
	string* arrKey = new string[arrSize];

	for (int i = 0; i < arrSize; i++) {
		arrOcc[i] = 0;
		arrKey[i] = "";
	}

	///*inserting values; document name and occurence, into temp arrays*/
	int counter = 0;
	for (int i = 0; i < entries->getTableSize(); i++) {

		ValueEntry * current = entries->getTable()[i];
		while (current != NULL) {
			arrKey[counter] = current->getKey();
			arrOcc[counter] = current->getOcc();
			counter++;

			if (current->getNext() == NULL)
				break;
			current = current->getNext();
		}
	}

	int maxVal = getMaximumValue(arrOcc, entries->NO_OF_ENTRIES);
	///*Implementation of countsort, which can be used in radix sort*/
	for (int exp = 1; maxVal / exp > 0; exp *= 10)
		countSort(arrOcc, arrKey, arrSize, exp);

	for (int i = 0; i < entries->NO_OF_ENTRIES; i++)
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