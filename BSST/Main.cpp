#include <iostream>

#include "BinSST.h"

static BinSST* binTree;
static bool quit;

void Init() {
	cout << "Binary Tree implementation." << endl << endl;
	binTree = new BinSST();
}

void Test() {
	// Building
	cout << "Constructing tree..." << endl;
	binTree->Add(0);
	binTree->Add(1);
	binTree->Add(2);
	binTree->Add(5);
	binTree->Add(1);
	binTree->Add(3);
	binTree->Add(9);
	binTree->Add(9);
	cout << "Tree Complete.  Height = " << binTree->GetHeight() << endl;

	// Traversal
	std::vector<int>* tree;
	cout << "Pre: ";
	tree = binTree->GetPreOrder();
	for (int data : *tree) {
		cout << data << ",";
	}
	cout << endl;
	tree->clear();

	cout << "In: ";
	tree = binTree->GetInOrder();
	for (int data : *tree) {
		cout << data << ",";
	}
	cout << endl;
	tree->clear();

	cout << "Post: ";
	tree = binTree->GetPostOrder();
	for (int data : *tree) {
		cout << data << ",";
	}
	cout << endl;
	tree->clear();

	// Printing
	cout << endl << "Printing..." << endl;
	binTree->Print();

	// Finding
	string found;
	cout << "Searching for 6..." << endl;
	found = binTree->Find(6) ? "true" : "false";
	cout << "Found = " << found << endl;
	cout << endl;

	cout << "Searching for 2..." << endl;
	found = binTree->Find(2) ? "true" : "false";
	cout << "Found = " << found << endl;
	cout << endl;

	// Counting
	int total;
	cout << "Counting 1s..." << endl;
	total = binTree->Count(1);
	cout << "Total = " << total << endl;
	cout << endl;

	cout << "Counting 4s..." << endl;
	total = binTree->Count(4);
	cout << "Total = " << total << endl;
	cout << endl;

	cin.get();
}

void AddDataMenu() {
	cout << "Enter the data to add: ";

	string input;
	cin >> input;
	int data = atoi(input.c_str());

	cout << "Adding " << data << "..." << endl;
	binTree->Add(data);
	binTree->Print();

	cout << endl;
}

void RemoveDataMenu() {
	cout << "Enter the data to remove: ";

	string input;
	cin >> input;
	int data = atoi(input.c_str());

	cout << "Removing " << data << "..." << endl;
	binTree->Remove(data);
	binTree->Print();

	cout << endl;
}

void FindMenu() {
	cout << "Enter the data to find: ";

	string input;
	cin >> input;
	int data = atoi(input.c_str());
	
	bool found = binTree->Find(data);
	string grammar = found ? " " : " not ";
	cout << "Item \"" << data << "\" was" << grammar << "found." << endl;

	cin.get();
	cout << endl;
}

void CountMenu() {
	cout << "Enter the data to find: ";

	string input;
	cin >> input;
	int data = atoi(input.c_str());

	int count = binTree->Count(data);
	string grammar = count > 1 ? "times" : "time";
	cout << "Item \"" << data << "\" was found " << count << " times." << endl;

	cin.get();
	cout << endl;
}

void PrintList(vector<int>* list) {
	for (int i : *list) {
		cout << i;
	}
	cout << endl;
}

void PrintMenu() {
	cout << "Print menu:" << endl;
	cout << "1. Tree" << endl;
	cout << "2. Height" << endl;
	cout << "3. Pre-order" << endl;
	cout << "4. In-order" << endl;
	cout << "5. Post-order" << endl;

	string input;
	cin >> input;
	int option = atoi(input.c_str());

	bool removeAll = false;
	switch (option) {
	case 1:
		binTree->Print();
		cout << endl;
		break;
	case 2:
		cout << "Height = " << binTree->GetHeight() << endl;
		cout << endl;
		break;
	case 3:
		cout << "Pre-order = ";
		PrintList(binTree->GetPreOrder());
		cout << endl;
		break;
	case 4:
		cout << "In-order = ";
		PrintList(binTree->GetInOrder());
		cout << endl;
		break;
	case 5:
		cout << "Post-order = ";
		PrintList(binTree->GetPostOrder());
		cout << endl;
		break;
	default:
		PrintMenu();
		break;
	}

	cin.get();
	cout << endl;
}

void MainMenu() {
	cout << "Main menu:" << endl;
	cout << "1. Add node" << endl;
	cout << "2. Remove node" << endl;
	cout << "3. Find node" << endl;
	cout << "4. Count nodes" << endl;
	cout << "5. Print info" << endl;
	cout << "Enter any other key to exit" << endl;

	string input;
	cin >> input;
	int option = atoi(input.c_str());
	cout << endl;

	switch (option) {
	case 1:
		AddDataMenu();
		break;
	case 2:
		RemoveDataMenu();
		break;
	case 3:
		FindMenu();
		break;
	case 4:
		CountMenu();
		break;
	case 5:
		PrintMenu();
		break;
	default:
		quit = true;
		break;
	}
}

void Cleanup() {
	delete binTree;
	binTree = nullptr;
}

int main() {
	Init();
	while (!quit)
		MainMenu();

	Cleanup();
	return 0;
}