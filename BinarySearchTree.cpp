#include "header.h"
#include <iostream>
using namespace std;

Node::Node(Node* left, int e, Node* right) {
	LeftChild = left;
	data = e;
	RightChild = right;
}

BST::BST() { root = 0; } // 생성자는 root에 NULL 삽입

Node* BST::IterSearch(const int& x) {
	for (Node* t = root; t; ) {
		if (x == t->data) { // x와 데이터 값 일치하면, t 노드 반환
			return t;
		}

		if (x < t->data) // x < 데이터 값일 시 왼쪽 자식 방향으로
			t = t->LeftChild;
		else // x > 데이터 값일 시 오른쪽 자식 방향으로
			t = t->RightChild;
	}

	return 0; // x에 해당하는 데이터 값 없으면 NULL 반환
}

bool BST::Insert(const int& x) {
	Node* p, * q;
	p = root; q = 0; // q는 p를 뒤따르는 변수

	while (p) {
		q = p;

		if (x == p->data) // 기존 데이터 값에 x가 존재하면 삽입하지 않는다
			return false;

		if (x < p->data) // x < 데이터 값일 시
			p = p->LeftChild;
		else // x > 데이터 값일 시
			p = p->RightChild;
	}
	p = new Node(0, x, 0); // p의 재활용, p는 새로 생성된 노드 가리킴

	if (root == 0) // 빈 트리이면
		root = p; // p가 첫 번째 노드로 삽입된다

	else if (x < q->data) // x가 q가 가리키는 데이터 값보다 작으면 왼쪽 자식으로
		q->LeftChild = p;
	else // x가 q가 가리키는 데이터 값보다 크면 오른쪽 자식으로
		q->RightChild = p;
}

Node* BST::Delete(const int& x) {
	if (root == 0) // 빈 트리면 삭제 불가
		return 0; // 따라서  NULL 반환

	Node* delNode = IterSearch(x);
	if (delNode == 0) // x와 일치하는 노드 없으면 삭제 불가
		return 0; // 따라서 NULL 반환

	else {
		// delNode의 부모 노드 q 찾기
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

		/* delNode, p: 삭제할 노드, q: delNode의 부모 노드 */

		// 1. delNode가 단말노드일 때
		if (delNode->LeftChild == 0 && delNode->RightChild == 0) {
			if (q->LeftChild == delNode) //부모의 왼쪽 자식이 삭제될 노드라면,
				q->LeftChild = 0; // 부모의 왼쪽 자식에 NULL 대입

			else // 부모의 오른쪽 자식이 삭제될 노드라면,
				q->RightChild = 0; // 부모의 오른쪽 자식에 NULL 대입
		}

		// 2. delNode가 2개의 자식 노드 가질 때
		else if (delNode->LeftChild && delNode->RightChild) {
			// 왼쪽 서브트리에서 가장 큰 노드로 대체

			Node* t = delNode; // t는 삭제될 노드를 가리킨다
			p = p->LeftChild; // 원래 delNode == p
			// 이제 p는 삭제될 노드의 왼쪽 서브트리를 위한 시작점

			// 왼쪽 서브트리에서 가장 큰 노드는 오른쪽 자식이 없는 노드
			while (p->RightChild) {
				q = p;
				p = p->RightChild;
			}

			/* p: delNode의 왼쪽 서브트리에서 가장 큰 노드 카리킴, q: p의 부모 노드*/
			t->data = p->data; // 삭제할 노드의 값을 왼쪽 서브트리에서 가장 큰 노드 값으로 대체

			if (p->LeftChild) // 만약 왼쪽 서브트리에서 가장 큰 노드가 왼쪽 자식이 있다면,
				q->RightChild = p->LeftChild; // p의 부모 노드의 왼쪽 자식으로, p의 왼쪽 자식을 넣는다
			else // p의 왼쪽 자식이 없다면
				q->RightChild = 0; // p의 부모 자식의 왼쪽 자식에 NULL 대입
		}

		// 3-1) delNode가 왼쪽 자식만 가질 때
		else if (delNode->LeftChild) {
			if (q->LeftChild == delNode) // 부모 노드의 왼쪽 자식이 삭제될 노드일 때
				q->LeftChild = delNode->LeftChild; // 삭제될 노드의 자식을 삭제된 노드 자리로 대체
			else // 부모 노드의 오른쪽 자식이 삭제될 노드일 때
				q->RightChild = delNode->LeftChild;
		}

		// 3-2) delNode가 오른쪽 자식만 가질 때
		else {
			if (q->LeftChild == delNode) // 3-1 설명과 동일
				q->LeftChild = delNode->RightChild;
			else
				q->RightChild = delNode->RightChild;
		}

		return delNode;
	}
}

void BST::inorder() {
	// 순환 호출용 함수 Driver
	inorder(root);
	cout << endl;
}

void BST::inorder(Node* CurrentNode) {
	// 실제 순환하며 트리 출력용 함수 Work Horse

	if (CurrentNode == 0) // CurrentNode가 NULL이면
		return; // 바로 리턴

	else if (CurrentNode) { // 현재 노드가 NULL이 아니라면
		inorder(CurrentNode->LeftChild); // 왼쪽 자식 가지고 순환하고
		cout << CurrentNode->data << " "; // 그다음에 리턴되면, 현재 노드의 데이터 출력
		inorder(CurrentNode->RightChild); // 오른쪽 자식 가지고 순환
	}
}
