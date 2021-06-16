#include <iostream>
#include "Term.h"
#include "Polynomial.h"
using namespace std;

int main() {
	int n;
	Polynomial A, B, C;
	float tcoef;
	int texp;

	//다항식 a 입력 시작
	cout << "다항식 A의 항의 수: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "다항식 A의 " << i + 1 << "번째 항의 계수와 지수: ";
		cin >> tcoef;
		cin >> texp;
		A.NewTerm(tcoef, texp);
	}
	//다항식 a 입력 끝!
	cout << endl;
	//다항식 b 입력 시작
	cout << "다항식 B의 항의 수: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "다항식 B의 " << i + 1 << "번째 항의 계수와 지수: ";
		cin >> tcoef >> texp;
		B.NewTerm(tcoef, texp);
	}
	//다항식 b 입력 끝!

	cout << endl << "----------------------------------------------------" << endl;
	cout << "<입력된 다항식>" << endl;
	cout << "A = ";
	A.Print();

	cout << endl;
	cout << "B = ";
	B.Print();

	cout << endl << endl << "<계산된 다항식 (A * B = C)>" << endl;
	cout << "C = ";
	C = A.Multiply(B);
	C.Print();
}
