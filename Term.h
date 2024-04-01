#pragma once
#ifndef Term_h
#define Term_h
class Polynomial;
class Term {
	friend Polynomial;
private:
	float coef;
	int exp;
};
#endif;
