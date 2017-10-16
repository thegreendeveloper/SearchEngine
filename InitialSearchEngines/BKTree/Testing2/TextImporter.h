#pragma once
#include <iostream>
#include <unordered_map>
#include "HashMapHE.h"

using namespace std;

class TextImporter {
public:
	TextImporter(string fileName, HashMapHE * map);
	~TextImporter();
private:
	void ImportTextFile(string fileName, HashMapHE * map);
	int getLineCount(string fileName);
};

