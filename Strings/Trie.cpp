#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

struct Node {

	Node* nodes[26];
	bool term;

	Node() = default;
	~Node() = default;
};

struct Trie {

	int alphabet;
	Node* root;
	
	Trie(int alpha): alphabet(alpha) {
		root  = new Node();
	}

	~Trie() {
		clean(root);
	}

	void add(string& str);
	bool find(string& str);
	void erase(string& str);
	void clean(Node* root);
};

void Trie::add(string& str) {
	Node* temp = root;
	for (int i = 0; i < str.size(); ++i) {

		int symbol = str[i] - 'a';
		if (temp->nodes[symbol] == nullptr) {
			temp->nodes[symbol] = new Node();
		}

		temp = temp->nodes[symbol];
	}
	temp->term = true;
}

bool Trie::find(string& str) {
	Node* temp = root;
	for (int i = 0; i < str.size(); ++i) {
		int symbol = str[i] - 'a';
		if (temp->nodes[symbol] == nullptr) {
			return false;
		}
		temp = temp->nodes[symbol];
	}
	return temp->term;
}

void Trie::erase(string& str) {
	Node* temp = root;
	for (int i = 0; i < str.size(); ++i) {
		int symbol = str[i] - 'a';
		if (temp->nodes[symbol] == nullptr) {
			return;
		}
		temp = temp->nodes[symbol];
	}
	temp->term = false;
	return;
}

void Trie::clean(Node* root) {
	if (root->nodes == nullptr){
		return;
	}
	for (int i = 0; i < alphabet; ++i) {
		clean(root->nodes[i]);
	}
	delete root;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	Trie trie(26);
	vector<bool> result;

	while (t--) {
		char c;
		string str;
		cin >> c >> str;
		if (c == 'a') {
			trie.add(str);
		} else if (c == 'f') {
			result.push_back(trie.find(str));
		} else {
			trie.erase(str);
		}
	}

	for (auto now : result) {
		cout << now << " ";
	}
	return 0;
}
