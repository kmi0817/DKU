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

	//while문 시작
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
	//while문 끝

	//다항식 A(x)의 나머지 항 추가
	for (; aPos < terms; aPos++)
		c.NewTerm(termArr[aPos].coef, termArr[aPos].exp);

	//다항식 B(x)의 나머지 항 추가
	for (; bPos < b.terms; bPos++)
		c.NewTerm(b.termArr[bPos].coef, b.termArr[bPos].exp);

	return c;
}

void Polynomial::Print(void) {
	//인덱스 번호 0부터 출력한다
	for (int Pos = 0; Pos < terms; Pos++) {

		//계수와 지수 출력하는 if문 시작
		if (termArr[Pos].coef != 0) {
			if (termArr[Pos].coef < 0) //만약 계수가 음수이면
				cout << "(" << termArr[Pos].coef << ")"; // 양괄호를 출력한다 ex: (-1)
			else // 계수가 양수이면
				cout << termArr[Pos].coef; //그대로 계수만 출력한다

			cout << "x^";

			if (termArr[Pos].exp < 0) //만약 지수가 음수이면
				cout << "(" << termArr[Pos].exp << ")"; // 양괄호를 출력한다 ex: (-1)
			else //지수가 양수이면
				cout << termArr[Pos].exp; // 그대로 지수만 출력한다
		}
		//계수와 지수 출력하는 if문 끝

		// + 출력하는 if문 시작
		if (Pos == (terms - 1)) // 만약 지금 항이 유효한 마지막 항이라면,
			break; // +를 출력하지 않고 for문을 종료한다

		// 지금 항이 유효한 마지막의 바로 이전 항이고, 마지막 항의 계수가 0이라면
		else if (Pos == (terms - 2) && termArr[terms - 1].coef == 0)
			break; // +를 출력하지 않고 for문을 종료한다

		else // 위 2개의 조건에 해당하지 않는다면
			cout << " + "; // +를 출력한다
		// + 출력하는 if문 끝

	}

	cout << endl;
}
// 두 다항식을 곱하는 함수
Polynomial Polynomial::Multiply(Polynomial b) {
	Polynomial c; // A * B의 결과를 담을 c 객체 생성
	c.NewTerm(0, 0); // c객체 초기화

	/*A와 B의 곱셈을
		(A의 전체 항*B의 첫 번째항) + (A의 전체 항*B의 두 번째항) +
			... + (A의 전체 항*B의 마지막 번째항)
	방식으로 얻기 위한 for문
	*/
	for (int aPos = 0; aPos < terms; aPos++) {
		Polynomial temp; // 아래 for문의 중간 결과를 담을 temp 객체 생성

		for (int bPos = 0; bPos < b.terms; bPos++) {
			//두 항의 계수들끼리 곱한 결과 담는 변수 tCoef
			float tCoef = termArr[aPos].coef * b.termArr[bPos].coef;
			//두 항의 지수들끼리 더한 결과 담는 변수 tExp
			int tExp = termArr[aPos].exp + b.termArr[bPos].exp;

			if (tCoef != 0) // 계수의 곱이 0이 아니라면,
				temp.NewTerm(tCoef, tExp);
			//B의 한 항과 A의 전체 항을 곱한 결과를 담는다.
		}

		c = c.Add(temp); // c객체에 A전체 항마다 B의 한 항을 곱한 결과를 추가한다.
		// B의 한 항씩 곱한 결과를 누적해서 c에 더하므로, 결과적으론 최종 곱셈 결과가 저장된다.
	}

	return c; //최종 곱셈 결과를 반환함
}

// 뺄셈
Polynomial Polynomial::Minus(Polynomial b) {
	Polynomial c;
	for (int bPos = 0; bPos < b.terms; bPos++)
		b.termArr[bPos].coef = (-b.termArr[bPos].coef);

	c = Add(b);

	// 다시 b를 원래대로 돌려줌
	for (int bPos = 0; bPos < b.terms; bPos++)
		b.termArr[bPos].coef = (-b.termArr[bPos].coef);
	return c;
}
