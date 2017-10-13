#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class JSONImporter {
public:
	JSONImporter(string filePath, unordered_set<string> * map);
	~JSONImporter();
private:
	void readJSONFileRapid(string filePath, unordered_set<string> * map);
	string encodeString(string line);
	wstring utf8_to_utf16(const string& utf8);
};

