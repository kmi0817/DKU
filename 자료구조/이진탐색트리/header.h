#pragma once
#ifndef header_h
#define header_h

class BST; // 전방선언
class Node {
	friend BST; // friend 지정

private:
	int data;
	Node* LeftChild, * RightChild;

public:
	Node(Node* left = 0, int e = 0, Node* right = 0);
};

class BST {
private:
	Node* root;
	void inorder(Node* CurrentNode);

public:
	BST();
	Node* IterSearch(const int& x);
	bool Insert(const int& x);
	Node* Delete(const int& x);

	// 중위순회
	void inorder();
};
#endif

