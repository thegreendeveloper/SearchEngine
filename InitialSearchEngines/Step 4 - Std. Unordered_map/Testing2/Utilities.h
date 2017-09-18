#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>


using namespace std;

class Utilities
{
public:
	static void ImportFile(string fileName, unordered_map<string, unordered_map<string, string>> * map);
	static int getLineCount(string fileName);
};

