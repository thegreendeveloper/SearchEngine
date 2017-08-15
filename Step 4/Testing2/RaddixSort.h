#pragma once
#include "HashMapVE.h"
#include <string>

using namespace std;

class RaddixSort
{
public:
	void sort(HashMapVE * entries);
	
private:
	int getMaximumValue(int arr[]);
	void countSort(int arrOcc[], string arrKey[], int n, int exp);

	
};

