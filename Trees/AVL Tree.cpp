#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

struct Node{
    Node* parent;
    Node* left;
    Node* right;
    int cnt;
    int val;
	int h;
    Node() : parent(nullptr), left(nullptr), right(nullptr), cnt(1), h(0) {}
    Node(int val) : Node() {this->val = val; }
};

class AVL {
private:

	Node* root;

	void FixHeight(Node* p){
		if (p == nullptr)
			return;
		p->h = max(Height(p->left), Height(p->right)) + 1;
	}

	int Difference(Node* p){
		return Height(p->right) - Height(p->left);
	}

	int Height(Node*p){
		return (p == nullptr) ? 0 : p->h;
	}

	Node* RotateLeft(Node* p){
		Node* main = p->right;
		Node* left = p;
		Node* rightForLeft = (main->left == nullptr) ? nullptr : main->left;
		main->left = left;
		main->parent = left->parent;
		left->parent = main;
		left->right = rightForLeft;
		if (rightForLeft != nullptr)
			rightForLeft->parent = left;
		FixHeight(left);
		FixHeight(main);
		return main;
	}

	Node* RotateRight(Node* p){
		Node* main = p->left;
		Node* right = p;
		Node* leftForRight = (main->right == nullptr) ? nullptr : main->right;
		main->right = right;
		main->parent = right->parent;
		right->parent = main;
		right->left = leftForRight;
		if (leftForRight != nullptr)
			leftForRight->parent = right;
		FixHeight(right);
		FixHeight(main);
		return main;
	}

	Node* Balance(Node* p){
		if (p == nullptr)
			return p;
		FixHeight(p);
		if (Difference(p) == 2){
			if (Difference(p->right) < 0)
				p->right = RotateRight(p->right);
			return RotateLeft(p);
		}
		if (Difference(p) == -2){
			if (Difference(p->left) > 0)
				p->left = RotateLeft(p->left);
			return RotateRight(p);
		}
		return p;
	}

	Node* FindMin(Node* p){
		return (p->left == nullptr) ? p : FindMin(p->left);
	}

	Node* FindMax(Node* p){
		return (p->right == nullptr) ? p : FindMax(p->right);
	}

	void ChangeParent(Node* oldNode, Node* newNode){
		Node* parent = oldNode->parent;
		newNode->parent = parent;
		oldNode->parent = nullptr;
		if (parent == nullptr){
			return;
		}
		if (parent->left == oldNode)
			parent->left = newNode;
		else 
			parent->right = newNode;
	}

	Node* NextValue(Node* p){
		if (p->right != nullptr){
			return FindMin(p->right);
		}
		Node* q = p->parent;
		while (q != nullptr && p == q->right){
			p = q;
			q = q->parent;
		}
		return q;
	}

	Node* PreviousValue(Node* p){
		if (p->left != nullptr){
			return FindMax(p->left);
		}
		Node* q = p->parent;
		while (q != nullptr && p == q->left){
			p = q;
			q = q->parent;
		}
		return q;
	}

	Node* Find(Node* p, int value){
		if (p == nullptr)
			return p;
		if (p->val == value)
			return p;
		if (p->val > value)
			return Find(p->left, value);
		else
			return Find(p->right, value);
	}

public:

	AVL() : root(nullptr) {}
	~AVL() { Traversal(root); }

	void Traversal(Node* p){
		if (p == nullptr)
			return;
		Traversal(p->left);
		Traversal(p->right);
		delete p;
	}
	
	void Write(Node* p){
		if (p == nullptr)
			return;
		cout << p->val << " ";
		Write(p->left);
		Write(p->right);
	}

	void Write(){
		Write(root);
	}

	Node* insert(Node* p, int value){
		if (p == nullptr){
			p = new Node(value);
			return p;
		}
		if (p->val == value){
			++p->cnt;
		}
		else if (p->val > value){
			p->left = insert(p->left, value);
			p->left->parent = p;
		}
		else {
			p->right = insert(p->right, value);
			p->right->parent = p;
		}
		return Balance(p);
	}

	void insert(int value){
		root = insert(root, value);
	}

	Node* remove(Node* p, int value){
		if (p == nullptr) 
			return nullptr;
		if (value < p->val){
			p->left = remove(p->left, value);
			if (p->left != nullptr)
				p->left->parent = p;
		}
		else if (value > p->val){
			p->right = remove(p->right, value);
			if (p->right != nullptr)
				p->right->parent = p;
		}
		else {
			if (p->cnt > 1){
				--p->cnt;
				return Balance(p);
			}
			if (p->left != nullptr && p->right != nullptr) {
				Node* min = FindMin(p->right);
				p->val = min->val;
				p->cnt = min->cnt;
				p->right = remove(p->right, p->val);
			}
			else {
				if (p->left != nullptr) {
					Node* parent = p->parent;
					p = p->left;
					p->parent = parent;
				}
				else if (p->right != nullptr){
					Node* parent = p->parent;
					p = p->right;
					p->parent = parent;
				}
				else {
					delete p;
					p = nullptr;
				}
			}
		}
		return Balance(p);
	}

	void remove(int value){
		root = remove(root, value);
	}

	int NearBy(int value){
		Node* current = Find(root, value);
		assert(current != nullptr);
		if (current->cnt > 1)
			return current->val;
		Node* next = NextValue(current);
		Node* previous = PreviousValue(current);
		if (next == nullptr && previous == nullptr)
			return INT_MAX;
		if (next == nullptr || previous == nullptr)
			return next == nullptr ? previous->val : next->val;
		return (abs(next->val - value) < abs(previous->val - value)) ? next->val : previous->val;
	}
};