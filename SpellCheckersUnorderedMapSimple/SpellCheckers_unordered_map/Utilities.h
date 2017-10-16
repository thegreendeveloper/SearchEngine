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
	static void print(vector<string> * resultSet, int noOfLines, bool reverse, string outputText);
	static int LevenshteinDamerauDistance(string s, int n, string t, int m);
	static int LevenshteinDistance(string s, int n, string t, int m);
private:
	static int getMaximumValue(unsigned long long arr[], int NoOfEntries);
	static void countSort(unsigned long long arrOcc[], string arrKey[], int n, int exp);

};

