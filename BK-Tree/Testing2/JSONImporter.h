#pragma once
#include <iostream>
#include <unordered_map>
#include "HashMapHE.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class JSONImporter {
public:
	JSONImporter(string filePath, HashMapHE * map);
	~JSONImporter();
private:
	void readJSONFile(string filePath, HashMapHE * map);
	string encodeString(string line);
	//void insertWord(string word, string document, unordered_map<string, unordered_map<string, string>> * map);
	wstring utf8_to_utf16(const string& utf8);
};

