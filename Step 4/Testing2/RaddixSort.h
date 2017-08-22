#pragma once
#include "HashMapVE.h"
#include <string>

using namespace std;

class RaddixSort
{
public:
	RaddixSort(HashMapVE * entries);
	void sort();
	void print(bool reverse, int maxOutput);

private:
	int getMaximumValue(int arr[]);
	void countSort(int arrOcc[], string arrKey[], int n, int exp);

	HashMapVE * entries;
	int* arrOcc;
	string* arrKey;
};

