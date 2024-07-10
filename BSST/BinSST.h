#ifndef BINSST_H
#define BINSST_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Node.h"

typedef unsigned int uint;
using namespace std;

class BinSST {
private:
	Node* mRoot;
public:
	BinSST();
	BinSST(int rootData);
	BinSST(int* dataList, uint listSize);
	~BinSST();

	// Node population
	void Add(int data);
	void Remove(int data);

	// Searching
	bool Find(int data);
	int Count(int data);

	// Properties
	int GetHeight();

	// Traversal
	vector<int>* GetPreOrder();
	vector<int>* GetInOrder();
	vector<int>* GetPostOrder();
	void Print();
private:
	// Recursive population
	Node* AddData(Node* node, int data);
	Node* RemoveData(Node* node, int data);

	// AVL Balancing
	int GetBalance(Node* node);
	Node* Rebalance(Node* node, int data);
	Node* LeftRotate(Node* x);
	Node* RightRotate(Node* y);

	// Recursive calculators
	void CheckSubtreeHeight(Node* node, int currHeight, int& maxHeight);

	// Recursive searching
	Node* Find(Node* node, int data);
	void Count(Node* node, int data, vector<Node*>& nodes);

	// Recursive traversals
	void TraversePreOrder(vector<Node*>& list, Node* node);
	void TraverseInOrder(vector<Node*>& list, Node* node);
	void TraversePostOrder(vector<Node*>& list, Node* node);
	void GetPrintingTree(Node* node, int currHeight, const int treeHeight, vector<vector<string>>* printingTree);
};

#endif