#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "HashEntry.h"
#include "HashMapHE.h"


using namespace std;

class Utilities
{
public:
	static bool ImportFile(string fileName, HashMapHE * map);
	static int getLineCount(string fileName);
	static vector<string> * sort(HashMapVE * entries);
private:
	static string RemoveSpecials(string str);
	static int getMaximumValue(int arr[]);
	static void countSort(int arrOcc[], string arrKey[], int n, int exp);

};

