#include "Index2.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <set>
#include <algorithm>

Index2::Index2(string filename)
{
	string word, dt = "";
	//WikiItem * current, *tmp;
	//WikiItem2 * current;
	FILE * file = NULL;

	try
	{
		char buf[1024];


		if (fopen_s(&file, filename.c_str(), "r") == 0) {

			while (fscanf_s(file, "%s", buf, sizeof(buf)) != EOF)
			{
				word = buf;
				if (dt == "")
					dt = word;
				if (word == "---END.OF.DOCUMENT---") {
					dt = "";
					continue;
				}

				if (start == NULL) {
					Document * dcm = new Document(dt, 0);
					start = new WikiItem2(word, dcm, 0);
				}
				else {
					updateWikiItems(start, word, dt);
				}

			}
			fclose(file);
		}

	}
	catch (const std::exception&)
	{
		cout << "Error reading file " + filename;
	}

	/*WikiItem2 * current = start;
	while (current->next != NULL)
	{
		cout << current->str << "\n";
		current = current->next;
	}*/

}


void Index2::updateWikiItems(WikiItem2 * start, string word, string dt) {
	WikiItem2 * current, *tmp;
	Document * current_doc, *tmp_doc;
	bool word_exist = false, document_exist = false;
	int counter = 0;

	/*looking in the linked list, finding the word if it exists.*/
	current = start;
	while (current->next != NULL) {
		counter++;
		if (current->str == word) {
			word_exist = true;
			break;
		}
		current = current->next;
	}

	if (!word_exist) {
		/*if the word does not exist it is created*/
		tmp_doc = new Document(dt, 0);
		tmp = new WikiItem2(word, tmp_doc, 0);
		current->next = tmp;
		current = tmp;

	}
	else {
		/*if the word exist then we check if the document is mentioned in the document list*/
		current_doc = current->document;		

		do {
			if (current_doc->name._Equal(dt)) {
				document_exist = true;
				break;
			}
			if(current_doc->next != NULL)
				current_doc = current_doc->next;
		
		} while (current_doc->next != NULL);
		
		/*if the document does not exist then we add it*/
		if (!document_exist) {	
			tmp_doc = new Document(dt, 0);
			current_doc->next = tmp_doc;			
		}
	}

}

bool Index2::Search(string searchname)
{
	WikiItem2 * current = start;
	Document * current_doc;
	set<string> documentList;

	while (current->next != NULL) {
		if (current->str == searchname) {
			current_doc = current->document;
			
			do {
				documentList.insert(current_doc->name);
				current_doc = current_doc->next;
			} while (current_doc != NULL);
			
		}
		current = current->next;
	}

	if (documentList.empty())
		return false;
	else {
		for (string title : documentList) {
			cout << title << "\n";
		}
		return true;
	}
	return true;
}

