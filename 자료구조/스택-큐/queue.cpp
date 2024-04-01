#include <iostream>
#include "queue.h"
#include "ChainNode.h"
using namespace std;


LinkedQueue::LinkedQueue(void) {
	front = 0; rear = 0;
}

void LinkedQueue::Push(const int& e) {
	if (front == 0)
		front = rear = new ChainNode(e, 0); // ����ť
	else
		rear = rear->link = new ChainNode(e, 0); //��带 �����ϰ� rear�� ������
}

//ť�� �ִ� ù ��° ��带 �����ϰ� �� �������� �����͸� ��ȯ
int* LinkedQueue::Pop(int& retvalue) {
	if (front == 0)
		return 0; //���� ť�̹Ƿ� null ��ȯ

	ChainNode* delNode = front;
	retvalue = front->data; //�����Ǵ� ���� retvalue�� ����
	front = front->link; // ���� ��� ����
	delete delNode; //��� ��ȯ
	return &retvalue; // null �ƴ� �� ��ȯ
}

void LinkedQueue::Print() {
	ChainNode* p;

	cout << "ť(FIFO��): ";
	if (front == 0)
		cout << "�� ť" << endl;

	else { //�� ť�� �ƴ� ��
		for (p = front; p->link; p = p->link) // p�� ������ ��带 ����ų ������ �ݺ�
			cout << p->data << " "; // �׷��� data ����� ������ ��� ���������� �ݺ�
		cout << p->data << " "; // ���� ������ ��带 ����Ű�� p�� data ���
		cout << endl;
	}
}
