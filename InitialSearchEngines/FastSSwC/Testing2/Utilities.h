#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Utilities
{
public:
	static void sort(vector<string> &resultSet, unordered_map<string, double> * entries);
	static int LevenshteinDamerauDistance(string s, int n, string t, int m);
	static int LevenshteinDistance(string s, int n, string t, int m);
private:
	static int getMaximumValue(int arr[], int NoOfEntries);
	static void countSort(int arrOcc[], string arrKey[], int n, int exp);

};

