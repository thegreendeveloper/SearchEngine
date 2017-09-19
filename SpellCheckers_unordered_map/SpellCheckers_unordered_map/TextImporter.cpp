#include "TextImporter.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <codecvt>

TextImporter::TextImporter(string fileName, unordered_map<string, unordered_map<string, string>> * map)
{
	ImportTextFile(fileName, map);
}


TextImporter::~TextImporter()
{
}


void TextImporter::ImportTextFile(string fileName, unordered_map<string, unordered_map<string, string>> * map) {
	clock_t start = clock();
	FILE * file = NULL;

	int totalLines = getLineCount(fileName), counter = 0;
	int divisor = totalLines / 10, lineSkipper = 0;
	
	wstring currentLine;
	string word, previousLine;

	wifstream myfile(fileName);
	myfile.imbue(locale(
		myfile.getloc(),
		new codecvt_utf8_utf16<wchar_t, 0x10FFFF, std::consume_header>));
	
	if (myfile.is_open())
	{
		vector<string> localString;
		while (getline(myfile, currentLine))
		{
			counter++;
			if (counter % divisor == 0) {
				cout << counter << " out of " << totalLines << " lines" << endl;
			}

			if (lineSkipper > 0) {
				lineSkipper--;
				continue;
			}

			string currentL(currentLine.begin(), currentLine.end());

			if (currentL == "")
				continue;

			if (currentL.substr(0, 4) == "<div") {
				//The last converted line was the title. We save the words in connection to the title. 
				for (vector<string>::iterator it = localString.begin(); it != localString.end(); it++)
					insertWord(*it, previousLine, map);

				localString.clear();
				//Skip tree lines 
				lineSkipper = 3;
				continue;
			}

			transform(currentL.begin(), currentL.end(), currentL.begin(), ::tolower);

			////We start importing the words
			//localString.push_back(currentL);

			///*Breakdown converted line and insert each word in into the map */
			istringstream iss(currentL);
			while (iss >> word) {
				localString.push_back(word);
			}
			previousLine = currentL;

		}
		myfile.close();
	}
	else {
		cout << "File could not be read" << endl;
	}

	
	clock_t duration = clock() - start;
	cout << endl;
	cout << "Duration : " << duration / CLOCKS_PER_SEC << "\n";

}

int TextImporter::getLineCount(string fileName) {
	int counter = 0;
	string line;
	FILE * file = NULL;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		cout << "Counting number of lines.." << endl;
		while (getline(myfile, line))
		{
			counter++;
		}
		myfile.close();
	}
	return counter;
}

void TextImporter::insertWord(string word, string document, unordered_map<string, unordered_map<string, string>> * map) {
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