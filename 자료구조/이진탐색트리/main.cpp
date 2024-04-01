#include "header.h"
#include <iostream>
using namespace std;

int main() {
	BST bst;


	// Ű 10�� ����
	bst.Insert(50);
	bst.Insert(10);
	bst.Insert(20);
	bst.Insert(90);
	bst.Insert(40);
	bst.Insert(60);
	bst.Insert(70);
	bst.Insert(100);
	bst.Insert(30);
	bst.Insert(80);

	// �����켱��ȸ
	bst.inorder();

	// Ű 2�� Ž�� (���� �Ǵ� ���� ���)
	if (bst.IterSearch(5))
		cout << "����" << endl;
	else
		cout << "����" << endl;

	if (bst.IterSearch(80))
		cout << "����" << endl;
	else
		cout << "����" << endl;

	// Ű 2�� ����
	bst.Delete(80);
	bst.Delete(70);

	// �����켱��ȸ
	bst.inorder();

	// Ű 5�� ����
	bst.Insert(5);
	bst.Insert(58);
	bst.Insert(2);
	bst.Insert(77);
	bst.Insert(35);

	// Ű 2�� Ž�� (���� �Ǵ� ���� ���)
	if (bst.IterSearch(58))
		cout << "����" << endl;
	else
		cout << "����" << endl;

	if (bst.IterSearch(80))
		cout << "����" << endl;
	else
		cout << "����" << endl;

	// Ű 2���� ����
	bst.Delete(50);
	bst.Delete(30);

	// �����켱��ȸ
	bst.inorder();
}
