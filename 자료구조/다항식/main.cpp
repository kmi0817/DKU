#include <iostream>
#include "Term.h"
#include "Polynomial.h"
using namespace std;

int main() {
	int n;
	Polynomial A, B, C;
	float tcoef;
	int texp;

	//���׽� a �Է� ����
	cout << "���׽� A�� ���� ��: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "���׽� A�� " << i + 1 << "��° ���� ����� ����: ";
		cin >> tcoef;
		cin >> texp;
		A.NewTerm(tcoef, texp);
	}
	//���׽� a �Է� ��!
	cout << endl;
	//���׽� b �Է� ����
	cout << "���׽� B�� ���� ��: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "���׽� B�� " << i + 1 << "��° ���� ����� ����: ";
		cin >> tcoef >> texp;
		B.NewTerm(tcoef, texp);
	}
	//���׽� b �Է� ��!

	cout << endl << "----------------------------------------------------" << endl;
	cout << "<�Էµ� ���׽�>" << endl;
	cout << "A = ";
	A.Print();

	cout << endl;
	cout << "B = ";
	B.Print();

	cout << endl << endl << "<���� ���׽� (A * B = C)>" << endl;
	cout << "C = ";
	C = A.Multiply(B);
	C.Print();
}
