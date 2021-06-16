#include "stack.h"
#include "ChainNode.h"
#include <iostream>
using namespace std;

//연결스택 생성자
LinkedStack::LinkedStack(void) { top = 0; }

//연결스택 삽입은 맨 처음에 노드를 삽입하는 것이므로,
//빈 연결스택이든 아니든 상관없이 무조건 top이 새 노드 가리키게 해준다.
void LinkedStack::Push(const int& e) {
	top = new ChainNode(e, top);
}

//스택에 톱 노드 삭제하고 값을 x에 저장한 후 x의 주소를 반환
int* LinkedStack::Pop(int& x) {
	if (top == 0)
		return 0; //빈 스택이면 null 반환

	ChainNode* delNode = top;
	x = top->data; // 톱 노드의 data 필드를 x에 저장
	top = top->link; //톱 위치를 다음 노드로 이동
	delete delNode; // 노드 삭제
	return &x; //null 아닌 값 반환
}

void LinkedStack::Print() {
	ChainNode* p;

	cout << "스택(LIFO순): ";
	if (top == 0)
		cout << "빈 스택" << endl;

	else { //빈 스택 아닐 때
		for (p = top; p->link; p = p->link) // p가 마지막 노드를 가리킬 때까지 반복
			cout << p->data << " "; // 그러나 data 출력은 마지막 노드 이전까지만 반복
		cout << p->data << " "; // 따라서 마지막 노드를 가리키는 p로 data 출력
		cout << endl;
	}
}
