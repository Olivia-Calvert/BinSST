#ifndef NODE_H
#define NODE_H

//template<class DataType>
struct Node {
	int data;
	Node* left;
	Node* right;
	int height;

	Node(int d) {
		data = d;
		left = nullptr;
		right = nullptr;
		height = 1;
	}
};

#endif