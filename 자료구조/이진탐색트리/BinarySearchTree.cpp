#include "header.h"
#include <iostream>
using namespace std;

Node::Node(Node* left, int e, Node* right) {
	LeftChild = left;
	data = e;
	RightChild = right;
}

BST::BST() { root = 0; } // �����ڴ� root�� NULL ����

Node* BST::IterSearch(const int& x) {
	for (Node* t = root; t; ) {
		if (x == t->data) { // x�� ������ �� ��ġ�ϸ�, t ��� ��ȯ
			return t;
		}

		if (x < t->data) // x < ������ ���� �� ���� �ڽ� ��������
			t = t->LeftChild;
		else // x > ������ ���� �� ������ �ڽ� ��������
			t = t->RightChild;
	}

	return 0; // x�� �ش��ϴ� ������ �� ������ NULL ��ȯ
}

bool BST::Insert(const int& x) {
	Node* p, * q;
	p = root; q = 0; // q�� p�� �ڵ����� ����

	while (p) {
		q = p;

		if (x == p->data) // ���� ������ ���� x�� �����ϸ� �������� �ʴ´�
			return false;

		if (x < p->data) // x < ������ ���� ��
			p = p->LeftChild;
		else // x > ������ ���� ��
			p = p->RightChild;
	}
	p = new Node(0, x, 0); // p�� ��Ȱ��, p�� ���� ������ ��� ����Ŵ

	if (root == 0) // �� Ʈ���̸�
		root = p; // p�� ù ��° ���� ���Եȴ�

	else if (x < q->data) // x�� q�� ����Ű�� ������ ������ ������ ���� �ڽ�����
		q->LeftChild = p;
	else // x�� q�� ����Ű�� ������ ������ ũ�� ������ �ڽ�����
		q->RightChild = p;
}

Node* BST::Delete(const int& x) {
	if (root == 0) // �� Ʈ���� ���� �Ұ�
		return 0; // ����  NULL ��ȯ

	Node* delNode = IterSearch(x);
	if (delNode == 0) // x�� ��ġ�ϴ� ��� ������ ���� �Ұ�
		return 0; // ���� NULL ��ȯ

	else {
		// delNode�� �θ� ��� q ã��
		Node* p, * q;
		p = root; q = 0;

		while (true) {
			if (p == delNode)
				break;

			q = p;

			if (x < p->data)
				p = p->LeftChild;
			else
				p = p->RightChild;
		}

		/* delNode, p: ������ ���, q: delNode�� �θ� ��� */

		// 1. delNode�� �ܸ������ ��
		if (delNode->LeftChild == 0 && delNode->RightChild == 0) {
			if (q->LeftChild == delNode) //�θ��� ���� �ڽ��� ������ �����,
				q->LeftChild = 0; // �θ��� ���� �ڽĿ� NULL ����

			else // �θ��� ������ �ڽ��� ������ �����,
				q->RightChild = 0; // �θ��� ������ �ڽĿ� NULL ����
		}

		// 2. delNode�� 2���� �ڽ� ��� ���� ��
		else if (delNode->LeftChild && delNode->RightChild) {
			// ���� ����Ʈ������ ���� ū ���� ��ü

			Node* t = delNode; // t�� ������ ��带 ����Ų��
			p = p->LeftChild; // ���� delNode == p
			// ���� p�� ������ ����� ���� ����Ʈ���� ���� ������

			// ���� ����Ʈ������ ���� ū ���� ������ �ڽ��� ���� ���
			while (p->RightChild) {
				q = p;
				p = p->RightChild;
			}

			/* p: delNode�� ���� ����Ʈ������ ���� ū ��� ī��Ŵ, q: p�� �θ� ���*/
			t->data = p->data; // ������ ����� ���� ���� ����Ʈ������ ���� ū ��� ������ ��ü

			if (p->LeftChild) // ���� ���� ����Ʈ������ ���� ū ��尡 ���� �ڽ��� �ִٸ�,
				q->RightChild = p->LeftChild; // p�� �θ� ����� ���� �ڽ�����, p�� ���� �ڽ��� �ִ´�
			else // p�� ���� �ڽ��� ���ٸ�
				q->RightChild = 0; // p�� �θ� �ڽ��� ���� �ڽĿ� NULL ����
		}

		// 3-1) delNode�� ���� �ڽĸ� ���� ��
		else if (delNode->LeftChild) {
			if (q->LeftChild == delNode) // �θ� ����� ���� �ڽ��� ������ ����� ��
				q->LeftChild = delNode->LeftChild; // ������ ����� �ڽ��� ������ ��� �ڸ��� ��ü
			else // �θ� ����� ������ �ڽ��� ������ ����� ��
				q->RightChild = delNode->LeftChild;
		}

		// 3-2) delNode�� ������ �ڽĸ� ���� ��
		else {
			if (q->LeftChild == delNode) // 3-1 ����� ����
				q->LeftChild = delNode->RightChild;
			else
				q->RightChild = delNode->RightChild;
		}

		return delNode;
	}
}

void BST::inorder() {
	// ��ȯ ȣ��� �Լ� Driver
	inorder(root);
	cout << endl;
}

void BST::inorder(Node* CurrentNode) {
	// ���� ��ȯ�ϸ� Ʈ�� ��¿� �Լ� Work Horse

	if (CurrentNode == 0) // CurrentNode�� NULL�̸�
		return; // �ٷ� ����

	else if (CurrentNode) { // ���� ��尡 NULL�� �ƴ϶��
		inorder(CurrentNode->LeftChild); // ���� �ڽ� ������ ��ȯ�ϰ�
		cout << CurrentNode->data << " "; // �״����� ���ϵǸ�, ���� ����� ������ ���
		inorder(CurrentNode->RightChild); // ������ �ڽ� ������ ��ȯ
	}
}
