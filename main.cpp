#include "header.h"
#include <iostream>
using namespace std;

int main() {
	BST bst;


	// 키 10개 삽입
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

	// 중위우선순회
	bst.inorder();

	// 키 2개 탐색 (성공 또는 실패 출력)
	if (bst.IterSearch(5))
		cout << "성공" << endl;
	else
		cout << "실패" << endl;

	if (bst.IterSearch(80))
		cout << "성공" << endl;
	else
		cout << "실패" << endl;

	// 키 2개 삭제
	bst.Delete(80);
	bst.Delete(70);

	// 중위우선순회
	bst.inorder();

	// 키 5개 삽입
	bst.Insert(5);
	bst.Insert(58);
	bst.Insert(2);
	bst.Insert(77);
	bst.Insert(35);

	// 키 2개 탐색 (성공 또는 실패 출력)
	if (bst.IterSearch(58))
		cout << "성공" << endl;
	else
		cout << "실패" << endl;

	if (bst.IterSearch(80))
		cout << "성공" << endl;
	else
		cout << "실패" << endl;

	// 키 2개를 삭제
	bst.Delete(50);
	bst.Delete(30);

	// 중위우선순회
	bst.inorder();
}
