#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class JSONImporter {
public:
	void readJSONFileRapid(string filePath, unordered_set<string> * map);
private:
	string encodeString(string line);
	void insertWord(string word, string document, unordered_map<string, unordered_set<string>> * map);
	wstring utf8_to_utf16(const string& utf8);
	string cleanString(string input);
	bool is_digits(string &str);
};

