#include <iostream>
#include "stack.h"
#include "queue.h"
#include "ChainNode.h"
#include <string> // string�� �ٷ�Ƿ� ����
#include <sstream> //stringsteam ����ϰ��� ����
using namespace std;

int main() {
	string input;
	int num[2] = { 0, 0 }; // �⺻���� ��� �ִ� ���� 0. �Էµ� �޴� ��ȣ�� ��� �迭
	LinkedStack ms;
	LinkedQueue mq;

	cout << "\t----�޴�----\t" << endl;
	cout << "1. ���ÿ� ����\t\t2. ť�� ����" << endl;
	cout << "3. ���ÿ� ����\t\t4. ť���� ����" << endl;
	cout << "5. ���� ���� ����\t6. ť ���� ����" << endl;
	cout << "* 0 �Է� �� ����" << endl; //�Ʒ��� ���ѹݺ��� ������ ������ ����ϰ��� ����
	cout << "----------------------------------------" << endl;
	while (1) {
		cout << "�� ";
		getline(cin, input); // ���鹮�� ������ �Է� ����

	/* case 1) 1 30 �Է� �� split���� string 1�� 30���� �ٲ��,
	while������ ���� int�� ��ȯ�Ǿ� num �迭�� ������� ����. ex) num: {1, 30} */
	/* case 2) 3�� �Է� �� split���� string3���� �ٲ��,
	while������ �Էµ� 3�� int�� ��ȯ�Ǿ� num �迭 ù ��° ��ҷ� ����. ex) num:{3, 0} */
		stringstream split(input); // ���鹮�ڸ� �������� split�� input
		string temp; // split�� �� ���� ����
		int i = 0; // �޴� �Է� ��ȣ ��� �迭�� �ε���
		while (split >> temp) { // split�� ������� ������ŭ �ݺ�
			int t; // split�� string�� int�� �ٲٸ� ���� ����
			stringstream s_to_int(temp); // split�� �� temp�� ����� �ִ�
			s_to_int >> t; // temp�� �ִ� string�� int������ ������ t�� ��´�
			num[i++] = t; // �Է� ���� �޴� ��ȣ(t)�� �迭�� �����Ѵ�
		} // ���� while�� ��

		switch (num[0]) {
		case 0: goto here; // while�� ������ 0�� �Է��ϸ� ���� ���̺��� ���� �������� �̵��Ѵ�
		case 1: ms.Push(num[1]); break;
		case 2: mq.Push(num[1]); break;
		case 3: ms.Pop(num[1]); break;
		case 4: mq.Pop(num[1]); break;
		case 5: ms.Print(); break;
		case 6: mq.Print(); break;
		} // switch ��
	} // ū while�� ��
here: // while�� �� switch, case 0�� �� ����� �´�.
	cout << ">> ���α׷� ����..." << endl;
}
