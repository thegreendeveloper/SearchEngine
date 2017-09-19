#pragma once
#include <iostream>
#include <unordered_map>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class JSONImporter {
public:
	JSONImporter(string filePath, unordered_map<string, unordered_map<string, string>> * map);
	~JSONImporter();
private:
	void readJSONFile(string filePath, unordered_map<string, unordered_map<string, string>> * map);
	string encodeString(string line);
	void insertWord(string word, string document, unordered_map<string, unordered_map<string, string>> * map);
	wstring utf8_to_utf16(const string& utf8);
};

