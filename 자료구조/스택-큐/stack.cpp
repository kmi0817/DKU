#include "stack.h"
#include "ChainNode.h"
#include <iostream>
using namespace std;

//���ὺ�� ������
LinkedStack::LinkedStack(void) { top = 0; }

//���ὺ�� ������ �� ó���� ��带 �����ϴ� ���̹Ƿ�,
//�� ���ὺ���̵� �ƴϵ� ������� ������ top�� �� ��� ����Ű�� ���ش�.
void LinkedStack::Push(const int& e) {
	top = new ChainNode(e, top);
}

//���ÿ� �� ��� �����ϰ� ���� x�� ������ �� x�� �ּҸ� ��ȯ
int* LinkedStack::Pop(int& x) {
	if (top == 0)
		return 0; //�� �����̸� null ��ȯ

	ChainNode* delNode = top;
	x = top->data; // �� ����� data �ʵ带 x�� ����
	top = top->link; //�� ��ġ�� ���� ���� �̵�
	delete delNode; // ��� ����
	return &x; //null �ƴ� �� ��ȯ
}

void LinkedStack::Print() {
	ChainNode* p;

	cout << "����(LIFO��): ";
	if (top == 0)
		cout << "�� ����" << endl;

	else { //�� ���� �ƴ� ��
		for (p = top; p->link; p = p->link) // p�� ������ ��带 ����ų ������ �ݺ�
			cout << p->data << " "; // �׷��� data ����� ������ ��� ���������� �ݺ�
		cout << p->data << " "; // ���� ������ ��带 ����Ű�� p�� data ���
		cout << endl;
	}
}
