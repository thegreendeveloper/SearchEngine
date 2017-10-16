#include "JSONImporter.h"
#include <sstream>
#include <cstdio>
#include <fstream>
#include <locale>
#include <codecvt>
#include <queue>
#include "rapidjson\filereadstream.h"
#include "rapidjson\document.h"
#include "rapidjson\istreamwrapper.h"

using namespace rapidjson;

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

void JSONImporter::insertWord(string word, string document, unordered_map<string, unordered_set<string>> * map) {
	auto iter = map->find(word);
	if (iter == map->end()) {
		unordered_set<string> documents;
		documents.insert(document);
		map->insert(make_pair(word, documents));
	}
	else {
		auto iter = map->at(word).find(document);
		if (iter == map->at(word).end()) {
			map->at(word).insert(document);
		}

	}

}

string JSONImporter::encodeString(string line) {
	wstring encoded = utf8_to_utf16(line);
	string converted = string(encoded.begin(), encoded.end());

	transform(converted.begin(), converted.end(), converted.begin(), ::tolower);

	return converted;
}

void JSONImporter::readJSONFileRapid(string filePath, unordered_set<string> * map) {

	FILE* fp = fopen(filePath.c_str(), "rb"); // non-Windows use "r"
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document document;
	document.ParseStream<0, UTF8<>, FileReadStream>(is);
	fclose(fp);

	cout << "JSON file buffered... " << endl;
	string previousLine, word;
	
	const Value& audios = document["response"]["docs"];
	assert(audios.IsArray());

	for (Value::ConstValueIterator itr = audios.Begin(); itr != audios.End(); ++itr) {
		const Value& metadata = (*itr)["spell"];
		assert(metadata.IsArray());

		for (int i = 0; i < metadata.Size(); i++) {
			string currentLine = metadata[i].GetString();

			if (currentLine.substr(0, 4) == "<div") {
				map->insert(previousLine);
				break;
			}
			if (currentLine == "")
				continue;

			/*Breakdown converted line and insert each word in into the map */
			istringstream iss(currentLine);
			while (iss >> word) {
				if (word != "" && word.length() != 1 && !is_digits(word))
					map->insert(encodeString(word));
			}
			previousLine = currentLine;
		}
	}
}
string JSONImporter::cleanString(string input) {
	return input;
}

bool JSONImporter::is_digits(string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}