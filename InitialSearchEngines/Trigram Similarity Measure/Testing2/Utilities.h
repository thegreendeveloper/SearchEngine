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
	static void sort(vector<string> &resultSet,HashMapVE * entries);
private:
	static int getMaximumValue(int arr[], int NoOfEntries);
	static void countSort(int arrOcc[], string arrKey[], int n, int exp);

};

