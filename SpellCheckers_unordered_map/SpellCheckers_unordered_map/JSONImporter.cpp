#include "JSONImporter.h"

#include <fstream>
#include <locale>
#include <codecvt>


JSONImporter::JSONImporter(string filePath, unordered_map<string, unordered_map<string, string>> * map)
{
	readJSONFile(filePath,map);
}


JSONImporter::~JSONImporter()
{
}


wstring JSONImporter::utf8_to_utf16(const string& utf8)
{
	vector<unsigned long> unicode;
	size_t i = 0;
	while (i < utf8.size())
	{
		unsigned long uni;
		size_t todo;
		bool error = false;
		unsigned char ch = utf8[i++];
		if (ch <= 0x7F)
		{
			uni = ch;
			todo = 0;
		}
		else if (ch <= 0xBF)
		{
			throw logic_error("not a UTF-8 string");
		}
		else if (ch <= 0xDF)
		{
			uni = ch & 0x1F;
			todo = 1;
		}
		else if (ch <= 0xEF)
		{
			uni = ch & 0x0F;
			todo = 2;
		}
		else if (ch <= 0xF7)
		{
			uni = ch & 0x07;
			todo = 3;
		}
		else
		{
			throw logic_error("not a UTF-8 string");
		}
		for (size_t j = 0; j < todo; ++j)
		{
			if (i == utf8.size())
				throw logic_error("not a UTF-8 string");
			unsigned char ch = utf8[i++];
			if (ch < 0x80 || ch > 0xBF)
				throw logic_error("not a UTF-8 string");
			uni <<= 6;
			uni += ch & 0x3F;
		}
		if (uni >= 0xD800 && uni <= 0xDFFF)
			throw logic_error("not a UTF-8 string");
		if (uni > 0x10FFFF)
			throw logic_error("not a UTF-8 string");
		unicode.push_back(uni);
	}
	wstring utf16;
	for (size_t i = 0; i < unicode.size(); ++i)
	{
		unsigned long uni = unicode[i];
		if (uni <= 0xFFFF)
		{
			utf16 += (wchar_t)uni;
		}
		else
		{
			uni -= 0x10000;
			utf16 += (wchar_t)((uni >> 10) + 0xD800);
			utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
		}
	}
	return utf16;
}

void JSONImporter::insertWord(string word, string document, unordered_map<string, unordered_map<string, string>> * map) {
	auto iter = map->find(word);
	if (iter == map->end()) {
		unordered_map<string, string> documents;
		documents.insert(make_pair(document, document));
		map->insert(make_pair(word, documents));
	}
	else {
		auto iter = map->at(word).find(document);
		if (iter == map->at(word).end()) {
			map->at(word).insert(make_pair(document, document));
		}

	}

}

string JSONImporter::encodeString(string line) {
	wstring encoded = utf8_to_utf16(line);
	string converted = string(encoded.begin(), encoded.end());

	transform(converted.begin(), converted.end(), converted.begin(), ::tolower);

	return converted;
}


void JSONImporter::readJSONFile(string filePath, unordered_map<string, unordered_map<string, string>> * map) {
	ifstream i(filePath);

	json file, documents;
	i >> file;

	string converted, word;

	documents = file["response"]["docs"];

	for (json::iterator it = documents.begin(); it != documents.end(); it++) {
		json currentDocument = *it;
		vector<string> localString;

		for (json::iterator it = currentDocument["spell"].begin(); it != currentDocument["spell"].end(); it++) {
			string currentLine = *it;

			if (currentLine.substr(0, 4) == "<div") {
				//The last converted line was the title. We save the words in connection to the title. 
				for (vector<string>::iterator it = localString.begin(); it != localString.end(); it++)
					insertWord(*it, converted, map);

				localString.clear();
				break;
			}
			if (currentLine == "")
				continue;

			//encode the line such that special characters are correctly encoded. 
			converted = encodeString(currentLine);

			//We start importing the words
			//localString.push_back(converted);

			/*Breakdown converted line and insert each word in into the map */
			istringstream iss(converted);
			while (iss >> word) {
				localString.push_back(word);
			}
		}
	}

	file.clear();
	documents.clear();
}