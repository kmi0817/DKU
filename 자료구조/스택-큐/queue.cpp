#include <iostream>
#include "queue.h"
#include "ChainNode.h"
using namespace std;


LinkedQueue::LinkedQueue(void) {
	front = 0; rear = 0;
}

void LinkedQueue::Push(const int& e) {
	if (front == 0)
		front = rear = new ChainNode(e, 0); // 공백큐
	else
		rear = rear->link = new ChainNode(e, 0); //노드를 삽입하고 rear를 수정함
}

//큐에 있는 첫 번째 노드를 제거하고 그 데이터의 포인터를 반환
int* LinkedQueue::Pop(int& retvalue) {
	if (front == 0)
		return 0; //공백 큐이므로 null 반환

	ChainNode* delNode = front;
	retvalue = front->data; //삭제되는 값을 retvalue에 저장
	front = front->link; // 앞의 노드 제거
	delete delNode; //노드 반환
	return &retvalue; // null 아닌 값 반환
}

void LinkedQueue::Print() {
	ChainNode* p;

	cout << "큐(FIFO순): ";
	if (front == 0)
		cout << "빈 큐" << endl;

	else { //빈 큐가 아닐 때
		for (p = front; p->link; p = p->link) // p가 마지막 노드를 가리킬 때까지 반복
			cout << p->data << " "; // 그러나 data 출력은 마지막 노드 이전까지만 반복
		cout << p->data << " "; // 따라서 마지막 노드를 가리키는 p로 data 출력
		cout << endl;
	}
}
