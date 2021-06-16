#pragma once
#ifndef Polynomial_H
#define Polynomial_H
#include "Term.h"
class Polynomial {
private:
	int terms;
	int capacity;
	Term* termArr;
public:
	Polynomial Add(Polynomial b);
	Polynomial Multiply(Polynomial b);
	Polynomial Minus(Polynomial b);
	void NewTerm(const float theCoef, const int theExp);
	void Print(void);
	Polynomial(void);
	~Polynomial(void);
};
#endif
