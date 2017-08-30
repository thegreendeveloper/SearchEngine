#include "Utilities.h"
#include <algorithm> 


string Utilities::RemoveSpecials(string str)
{
	int i = 0, len = str.length();
	while (i < len)
	{
		char c = str[i];
		if (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '-'))
		{
			if ((c >= 'A') && (c <= 'Z')) str[i] += 32; //Assuming dictionary contains small letters only.
			++i;
		}
		else
		{
			str.erase(i, 1);
			--len;
		}
	}
	return str;
}

bool Utilities::ImportFile(string fileName, HashMapHE * map) {
	clock_t start = clock();
	FILE * file = NULL;
	char buf[1024];

	int totalLines = getLineCount(fileName), counter = 0;
	int divisor = totalLines / 10;

	string line, word, dt;

	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			counter++;
			if (counter % divisor == 0) {
				cout << counter << " out of " << totalLines << " lines" << endl;
			}

			istringstream iss(line);
			while (iss >> word) {
				if (dt == "") {
					dt = line;
					continue;
				}
				if (word == "---END.OF.DOCUMENT---") {
					dt = "";
					continue;
				}

				transform(word.begin(), word.end(), word.begin(), ::tolower);
				word = RemoveSpecials(word);
				if (word != "")
					map->put(word, dt);
			}
		}
		myfile.close();
	}
	else {
		cout << "File could not be read" << endl;
		return false;
	}

	clock_t duration = clock() - start;
	cout << endl;
	cout << "Duration : " << duration / CLOCKS_PER_SEC << "\n";
	cout << "Max chained collision length: " << map->MAX_NO_OF_COLLISIONS << endl;
	cout << "Number of entries : " << map->NO_OF_ENTRIES << endl;
	cout << "Final table size: " << map->getTableSize() << endl;
	return true;
}

int Utilities::getLineCount(string fileName) {
	int counter = 0;
	string line;
	FILE * file = NULL;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		cout << "Counting number of lines.." << endl;
		while (getline(myfile, line))
		{
			counter++;
		}
		myfile.close();
	}
	return counter;
}

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
		if (entries->getTable()[i] != NULL) {

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
	}

	int maxVal = getMaximumValue(arrOcc);

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

int Utilities::getMaximumValue(int arr[]) {
	int maxValue = arr[0];
	for (int i = 1; i < sizeof(arr); i++) {
		if (maxValue < arr[i])
			maxValue = arr[i];
	}
	return maxValue;
}