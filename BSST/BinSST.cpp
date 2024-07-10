#include "BinSST.h"

BinSST::BinSST() {
	mRoot = nullptr;
}

BinSST::BinSST(int rootData) {
	mRoot = new Node(rootData);
}

BinSST::BinSST(int* dataList, uint listSize) {
	for (uint i = 0; i < listSize; i++) {
		Add(dataList[i]);
	}
}

BinSST::~BinSST() {
	vector<Node*> tree;
	if (mRoot != nullptr)
		TraversePostOrder(tree, mRoot);

	for (Node* node : tree) {
		delete node;
		node = nullptr;
	}
}

// ----------------------------------------------------------------
// Node Population
// ----------------------------------------------------------------
void BinSST::Add(int data) {
	if (mRoot == nullptr) {
		mRoot = new Node(data);
	} else {
		mRoot = AddData(mRoot, data);
	}
}

void BinSST::Remove(int data) {
	if (mRoot == nullptr)
		return;
	
	mRoot = RemoveData(mRoot, data);
}

Node* BinSST::AddData(Node* node, int data) {
	if (data < node->data) {
		if (node->left != nullptr) {
			node->left = AddData(node->left, data);
		} else {
			node->left = new Node(data);
		}
	} else if (data >= node->data) {
		if (node->right != nullptr) {
			node->right = AddData(node->right, data);
		} else {
			node->right = new Node(data);
		}
	}

	return Rebalance(node, data);
}

Node* BinSST::RemoveData(Node* node, int data) {
	if (data < node->data) {
		// Remove on left
		if (node->left != nullptr) {
			node->left = RemoveData(node->left, data);
		} else {
			return node;
		}
		// Remove on right
	} else if (data > node->data) {
		if (node->right != nullptr) {
			node->right = RemoveData(node->right, data);
		} else {
			return node;
		}
		// Remove this node
	} else {
		// Easy remove?
		if (node->left == nullptr || node->right == nullptr) {
			Node* child = nullptr;
			if (node->left != nullptr)
				child = node->left;
			else if (node->right != nullptr)
				child = node->right;

			delete node;
			node = child;
		} else {
			// Lowest value on right
			Node* swap = node->right;
			while (swap->left != nullptr)
				swap = swap->left;

			// Swap data
			node->data = swap->data;

			// Delete the now duplicate node
			node->right = RemoveData(node->right, swap->data);
		}
	}

	// If no children
	if (node == nullptr)
		return nullptr;

	return Rebalance(node, data);
}

Node* BinSST::Rebalance(Node* node, int data) {
	// Calculate new heights
	int leftHeight = 0;
	if (node->left != nullptr)
		leftHeight = node->left->height;
	int rightHeight = 0;
	if (node->right != nullptr)
		rightHeight = node->right->height;
	node->height = 1 + max(leftHeight, rightHeight);

	// Rebalance if necessary
	int balance = GetBalance(node);
	if (balance > 1) {
		if (data > node->left->data)
			node->left = LeftRotate(node->left);
		return RightRotate(node);
	} else if (balance < -1) {
		if (data < node->right->data)
			node->right = RightRotate(node->right);
		return LeftRotate(node);
	}

	return node;
}

Node* BinSST::LeftRotate(Node* root) {
	Node* parent = root->right;
	Node* leaf = parent->left;

	parent->left = root;
	root->right = leaf;

	int leftHeight = 0, rightHeight = 0;
	if (root->left != nullptr)
		leftHeight = root->left->height;
	if (root->right != nullptr)
		rightHeight = root->right->height;
	root->height = 1 + max(leftHeight, rightHeight);

	leftHeight = 0;
	rightHeight = 0;
	if (parent->left != nullptr)
		leftHeight = parent->left->height;
	if (parent->right != nullptr)
		rightHeight = parent->right->height;
	parent->height = 1 + max(leftHeight, rightHeight);

	return parent;
}

Node* BinSST::RightRotate(Node* parent) {
	Node* root = parent->left;
	Node* leaf = root->right;

	root->right = parent;
	parent->left = leaf;

	int leftHeight = 0, rightHeight = 0;
	if (root->left != nullptr)
		leftHeight = root->left->height;
	if (root->right != nullptr)
		rightHeight = root->right->height;
	root->height = 1 + max(leftHeight, rightHeight);

	leftHeight = 0;
	rightHeight = 0;
	if (parent->left != nullptr)
		leftHeight = parent->left->height;
	if (parent->right != nullptr)
		rightHeight = parent->right->height;
	parent->height = 1 + max(leftHeight, rightHeight);

	return root;
}

// ----------------------------------------------------------------
// Searching
// ----------------------------------------------------------------
bool BinSST::Find(int data) {
	if (mRoot != nullptr)
		return Find(mRoot, data) != nullptr;
	else
		return false;
}

int BinSST::Count(int data) {
	vector<Node*> nodes;
	if (mRoot != nullptr)
		Count(mRoot, data, nodes);
	return nodes.size();
}

Node* BinSST::Find(Node* node, int data) {
	if (data == node->data)
		return node;

	if (data < node->data) {
		if (node->left != nullptr)
			return Find(node->left, data);
		else
			return nullptr;
	}
	if (data > node->data) {
		if (node->right != nullptr)
			return Find(node->right, data);
		else
			return nullptr;
	}

	return nullptr;
}

void BinSST::Count(Node* node, int data, vector<Node*>& nodes) {
	if (data == node->data) {
		nodes.push_back(node);
		if (node->right != nullptr)
			Count(node->right, data, nodes);
	} else if (data < node->data) {
		if (node->left != nullptr)
			Count(node->left, data, nodes);
	} else if (data > node->data) {
		if (node->right != nullptr)
			Count(node->right, data, nodes);
	}
}

// ----------------------------------------------------------------
// Properties
// ----------------------------------------------------------------
int BinSST::GetHeight() {
	// TODO: if changesMade;
	int maxHeight = 0;
	if (mRoot != nullptr)
		CheckSubtreeHeight(mRoot, 1, maxHeight);

	return maxHeight;
}

void BinSST::CheckSubtreeHeight(Node* node, int currHeight, int& maxHeight) {
	if (maxHeight < currHeight)
		maxHeight = currHeight;

	if (node->left != nullptr)
		CheckSubtreeHeight(node->left, currHeight + 1, maxHeight);
	if (node->right != nullptr)
		CheckSubtreeHeight(node->right, currHeight + 1, maxHeight);
}

int BinSST::GetBalance(Node* node) {
	if (node == nullptr)
		return 0;

	int leftHeight;
	if (node->left != nullptr)
		leftHeight = node->left->height;
	else
		leftHeight = 0;

	int rightHeight;
	if (node->right != nullptr)
		rightHeight = node->right->height;
	else
		rightHeight = 0;

	return leftHeight - rightHeight;
}

// ----------------------------------------------------------------
// Traversal
// ----------------------------------------------------------------
vector<int>* BinSST::GetPreOrder() {
	vector<Node*> list;
	if (mRoot != nullptr)
		TraversePreOrder(list, mRoot);

	vector<int>* data = new vector<int>();
	for (Node* node : list)
		data->push_back(node->data);
	return data;
}
void BinSST::TraversePreOrder(vector<Node*>& list, Node* node) {
	list.push_back(node);
	if (node->left != nullptr) TraversePreOrder(list, node->left);
	if (node->right != nullptr) TraversePreOrder(list, node->right);
}

vector<int>* BinSST::GetInOrder() {
	vector<Node*> list;
	if (mRoot != nullptr)
		TraverseInOrder(list, mRoot);

	vector<int>* data = new vector<int>();
	for (Node* node : list)
		data->push_back(node->data);
	return data;
}
void BinSST::TraverseInOrder(vector<Node*>& list, Node* node) {
	if (node->left != nullptr) TraverseInOrder(list, node->left);
	list.push_back(node);
	if (node->right != nullptr) TraverseInOrder(list, node->right);
}

vector<int>* BinSST::GetPostOrder() {
	vector<Node*> list;
	if (mRoot != nullptr)
		TraversePostOrder(list, mRoot);

	vector<int>* data = new vector<int>();
	for (Node* node : list)
		data->push_back(node->data);
	return data;
}
void BinSST::TraversePostOrder(vector<Node*>& list, Node* node) {
	if (node->left != nullptr) TraversePostOrder(list, node->left);
	if (node->right != nullptr) TraversePostOrder(list, node->right);
	list.push_back(node);
}

// ----------------------------------------------------------------
// Printing
// ----------------------------------------------------------------
void BinSST::GetPrintingTree(Node* node, int currHeight, const int treeHeight, vector<vector<string>>* printingTree) {
	printingTree->at(currHeight).push_back(to_string(node->data));

	if (node->left != nullptr) {
		GetPrintingTree(node->left, currHeight + 1, treeHeight, printingTree);
	} else {
		int nulls = 1;
		for (int i = currHeight + 1; i < treeHeight; i++) {
			for (int c = 0; c < nulls; c++) {
				printingTree->at(i).push_back("N");
			}
			nulls *= 2;
		}
	}
	if (node->right != nullptr) {
		GetPrintingTree(node->right, currHeight + 1, treeHeight, printingTree);
	} else {
		int nulls = 1;
		for (int i = currHeight + 1; i < treeHeight; i++) {
			for (int c = 0; c < nulls; c++) {
				printingTree->at(i).push_back("N");
			}
			nulls *= 2;
		}
	}
}

void BinSST::Print() {
	// Check there is a tree
	int treeHeight = GetHeight();
	if (treeHeight < 1) return;

	// Setup storage 
	vector<vector<string>>* printingTree = new vector<vector<string>>();
	for (int i = 0; i < treeHeight; i++) {
		printingTree->push_back(vector<string>());
	}

	// Get tree recursively by rows
	GetPrintingTree(mRoot, 0, treeHeight, printingTree);

	// Setup tree formatting
	string* treeFormat = new string[treeHeight];
	int formatter = 2;
	int repeatCount = (int)pow(2, treeHeight - 2);
	for (int i = treeHeight - 2; i >= 0; --i) {
		string pattern, gap;

		// Create pattern
		pattern += "+";
		for (int j = 0; j < formatter - 1; j++) pattern += "-";
		pattern += "+";
		for (int j = 0; j < formatter - 1; j++) pattern += "-";
		pattern += "+";

		// Create gap
		for (int j = 0; j < (formatter * 2) - 1; j++) gap += " ";

		// Create and position line
		string line;
		for (int j = 0; j < formatter - 1; j++) line += " ";

		// Repeat pattern and gaps
		for (int j = 0; j < repeatCount; j++) {
			line += pattern;
			line += gap;
		}

		// Set line and setup formatters for next time
		treeFormat[i] = line;
		formatter *= 2;
		repeatCount /= 2;
	}

	// Setup data formatting
	string* dataFormat = new string[treeHeight];
	formatter = 2;
	for (int i = treeHeight - 1; i >= 0; --i) {
		// Create and position line
		string line;
		for (int j = 0; j < formatter - 1; j++) line += " ";

		// Add numbers
		for (string s : printingTree->at(i)) {
			line += s;
			// Add dynamic gap
			for (uint j = 0; j < (formatter * 2) - s.length(); j++) line += " ";
		}

		// Set line and setup formatter for next time
		dataFormat[i] = line;
		formatter *= 2;
	}

	// Print tree
	for (int i = 0; i < treeHeight; i++) {
		cout << dataFormat[i] << endl;
		cout << treeFormat[i] << endl;
	}
}
