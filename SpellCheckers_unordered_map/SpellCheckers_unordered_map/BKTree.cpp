#include "BKTree.h"
#include <algorithm>
#include <cassert>

BKTree::BKTree() {}
BKTree::BKTree(string root) {
	_root = new Node(root);
}

BKTree::~BKTree() {
	delete _root;
}

void BKTree::Add(string word) {
	if (_root == NULL) {
		_root = new Node(word);
		return;
	}

	int distance = LevenshteinDistance(_root->word,word);

	if (_root->children->find(distance) == _root->children->end()) {
		/*if the distance does not exist we insert a new node equivalent to edit distance*/	
		Node * child = new Node(word);
		_root->children->insert(make_pair(distance, child));
		return;
	}
	/*If an object with same distance exists, then we recurse down the tree finding a 
	node to insert the childnode. */
	unordered_map<int, Node *>::iterator i = _root->children->find(distance);
	assert(i != _root->children->end());
	AddChildNode(i->second, word);
}


void BKTree::AddChildNode(Node * current, string word) {
	int distance = LevenshteinDistance(current->word, word);

	if (current->children->find(distance) == current->children->end()) {
		/*if the distance does not exist we insert a new node equivalent to edit distance*/
		Node * child = new Node(word);
		current->children->insert(make_pair(distance, child));
		return;
	}
	/*If an object with same distance exists, then we recurse down the tree finding a
	free place to insert the childnode. */
	unordered_map<int, Node *>::iterator i = current->children->find(distance);
	assert(i != current->children->end()); //TODO: Maybe something else than assert should be used. 
	AddChildNode(i->second, word);

}

void BKTree::Print() {
	_root->Print();
	cout << endl;
	for (unordered_map<int, Node *>::iterator it = _root->children->begin(); it != _root->children->end(); it++)
		it->second->Print();
}

vector<pair<string,int>> * BKTree::Search(string searchString, int tolerance) {
	vector<pair<string, int>> * resultSet = new vector<pair<string, int>>();
	
	RecursiveSearch(searchString, tolerance, _root, resultSet);

 	return resultSet;
}


void BKTree::RecursiveSearch(string searchString, int tolerance, Node * current, vector<pair<string, int>> * resultSet) {
	int distance = LevenshteinDistance(current->word, searchString), upper = distance + tolerance, lower = distance - tolerance;

	if (distance <= tolerance)
		resultSet->push_back(make_pair(current->word, distance));

	for (int score = lower; score <= upper; score++) {
		if (score < 0)
			continue;

		unordered_map<int, Node *>::iterator it = current->children->find(score);
		if(it != current->children->end()){
			RecursiveSearch(searchString, tolerance, it->second, resultSet);
		}
	}
}

/*Non-recursive basic levenshtein method :  O(n^2) time. O(n) space.*/
int BKTree::LevenshteinDistance(string s, string t) {
	int n = s.length(), m = t.length();
	if (n == 0)
		return m;
	if (m == 0)
		return n;

	/*initializing*/
	int* distance = new int[n + 1];
	for (int i = 0; i < n + 1; i++)
		distance[i] = i;

	int* current = new int[n + 1];
	int cost = 0;

	for (int j = 1; j < m + 1; j++) { // iterate through each row
		for (int i = 1; i < n + 1; i++) { // iterate through each column
			if (i == 1)
				current[0] = j;

			if (s[i - 1] == t[j - 1])
				cost = 0;
			else
				cost = 1;

			current[i] = min(current[i - 1] + 1, min(distance[i] + 1, distance[i - 1] + cost));
		}
		
		for (int i = 0; i < n + 1; i++)
			distance[i] = current[i];
	}

	cost = distance[n];

	delete[] distance;
	delete[] current;

	return cost;
}