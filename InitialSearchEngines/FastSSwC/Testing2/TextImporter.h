#pragma once
#include <iostream>
#include <unordered_map>

using namespace std;

class TextImporter {
public:
	TextImporter(string fileName, unordered_map<string, unordered_map<string, string>> * map);
	~TextImporter();
private:
	void ImportTextFile(string fileName, unordered_map<string, unordered_map<string, string>> * map);
	int getLineCount(string fileName);
	void insertWord(string word, string document, unordered_map<string, unordered_map<string, string>> * map);
};

