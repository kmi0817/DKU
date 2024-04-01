#include <iostream>
#include "Term.h"
#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial(void) {
	capacity = 1;
	terms = 0;
	termArr = new Term[capacity];
}

Polynomial::~Polynomial(void) {}

void Polynomial::NewTerm(const float theCoeff, const int theExp) {
	if (terms == capacity) {
		capacity *= 2;
		Term* temp = new Term[capacity];
		for (int i = 0; i < terms; i++)
			temp[i] = termArr[i];
		delete[] termArr;
		termArr = temp;
	}

	termArr[terms].coef = theCoeff;
	termArr[terms++].exp = theExp;
}

Polynomial Polynomial::Add(Polynomial b) {
	Polynomial c;
	int aPos = 0, bPos = 0;

	//while�� ����
	while (aPos < terms && bPos < b.terms) {
		if (termArr[aPos].exp == b.termArr[bPos].exp) {
			float t = termArr[aPos].coef + b.termArr[bPos].coef;

			if (t != 0)
				c.NewTerm(t, termArr[aPos].exp);

			aPos++; bPos++;
		}

		else if (termArr[aPos].exp < b.termArr[bPos].exp) {
			c.NewTerm(b.termArr[bPos].coef, b.termArr[bPos].exp);
			bPos++;
		}

		else {
			c.NewTerm(termArr[aPos].coef, termArr[aPos].exp);
			aPos++;
		}
	}
	//while�� ��

	//���׽� A(x)�� ������ �� �߰�
	for (; aPos < terms; aPos++)
		c.NewTerm(termArr[aPos].coef, termArr[aPos].exp);

	//���׽� B(x)�� ������ �� �߰�
	for (; bPos < b.terms; bPos++)
		c.NewTerm(b.termArr[bPos].coef, b.termArr[bPos].exp);

	return c;
}

void Polynomial::Print(void) {
	//�ε��� ��ȣ 0���� ����Ѵ�
	for (int Pos = 0; Pos < terms; Pos++) {

		//����� ���� ����ϴ� if�� ����
		if (termArr[Pos].coef != 0) {
			if (termArr[Pos].coef < 0) //���� ����� �����̸�
				cout << "(" << termArr[Pos].coef << ")"; // ���ȣ�� ����Ѵ� ex: (-1)
			else // ����� ����̸�
				cout << termArr[Pos].coef; //�״�� ����� ����Ѵ�

			cout << "x^";

			if (termArr[Pos].exp < 0) //���� ������ �����̸�
				cout << "(" << termArr[Pos].exp << ")"; // ���ȣ�� ����Ѵ� ex: (-1)
			else //������ ����̸�
				cout << termArr[Pos].exp; // �״�� ������ ����Ѵ�
		}
		//����� ���� ����ϴ� if�� ��

		// + ����ϴ� if�� ����
		if (Pos == (terms - 1)) // ���� ���� ���� ��ȿ�� ������ ���̶��,
			break; // +�� ������� �ʰ� for���� �����Ѵ�

		// ���� ���� ��ȿ�� �������� �ٷ� ���� ���̰�, ������ ���� ����� 0�̶��
		else if (Pos == (terms - 2) && termArr[terms - 1].coef == 0)
			break; // +�� ������� �ʰ� for���� �����Ѵ�

		else // �� 2���� ���ǿ� �ش����� �ʴ´ٸ�
			cout << " + "; // +�� ����Ѵ�
		// + ����ϴ� if�� ��

	}

	cout << endl;
}
// �� ���׽��� ���ϴ� �Լ�
Polynomial Polynomial::Multiply(Polynomial b) {
	Polynomial c; // A * B�� ����� ���� c ��ü ����
	c.NewTerm(0, 0); // c��ü �ʱ�ȭ

	/*A�� B�� ������
		(A�� ��ü ��*B�� ù ��°��) + (A�� ��ü ��*B�� �� ��°��) +
			... + (A�� ��ü ��*B�� ������ ��°��)
	������� ��� ���� for��
	*/
	for (int aPos = 0; aPos < terms; aPos++) {
		Polynomial temp; // �Ʒ� for���� �߰� ����� ���� temp ��ü ����

		for (int bPos = 0; bPos < b.terms; bPos++) {
			//�� ���� ����鳢�� ���� ��� ��� ���� tCoef
			float tCoef = termArr[aPos].coef * b.termArr[bPos].coef;
			//�� ���� �����鳢�� ���� ��� ��� ���� tExp
			int tExp = termArr[aPos].exp + b.termArr[bPos].exp;

			if (tCoef != 0) // ����� ���� 0�� �ƴ϶��,
				temp.NewTerm(tCoef, tExp);
			//B�� �� �װ� A�� ��ü ���� ���� ����� ��´�.
		}

		c = c.Add(temp); // c��ü�� A��ü �׸��� B�� �� ���� ���� ����� �߰��Ѵ�.
		// B�� �� �׾� ���� ����� �����ؼ� c�� ���ϹǷ�, ��������� ���� ���� ����� ����ȴ�.
	}

	return c; //���� ���� ����� ��ȯ��
}

// ����
Polynomial Polynomial::Minus(Polynomial b) {
	Polynomial c;
	for (int bPos = 0; bPos < b.terms; bPos++)
		b.termArr[bPos].coef = (-b.termArr[bPos].coef);

	c = Add(b);

	// �ٽ� b�� ������� ������
	for (int bPos = 0; bPos < b.terms; bPos++)
		b.termArr[bPos].coef = (-b.termArr[bPos].coef);
	return c;
}
