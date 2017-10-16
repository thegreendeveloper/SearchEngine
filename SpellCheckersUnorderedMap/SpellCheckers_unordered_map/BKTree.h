#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class BKTree {

public:
	BKTree();
	BKTree(string root);
	~BKTree();

	void Add(string word);
	void Print();
	void Search(string searchString, int tolerance);
private:

	struct Node {
		string word;
		unordered_map<int, Node *> * children;

		Node() {}
		Node(string word) {
			this->word = word;
			children = new unordered_map<int,Node *>();
		}
		~Node() {
			delete children;
		}

		void Print() {
			cout << "Node : " << word << endl;
			cout << "\tChildren : " << endl;
			for (unordered_map<int,Node *>::iterator it = children->begin(); it != children->end();it++) {
				cout << "\tDistance : " << it->first << " word : " << it->second->word << endl;
			}	
		}
		
	};

	Node * _root;
	int LevenshteinDistance(string s, string t);
	void AddChildNode(Node * current, string word);
	void RecursiveSearch(string searchString, int tolerance, Node * current, vector<pair<string, int>> * resultSet);
};

