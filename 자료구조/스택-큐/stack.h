#pragma once
#ifndef stack_H
#define stack_H
class ChainNode;
//연결스택
class LinkedStack {
private:
	ChainNode* top;
public:
	LinkedStack(void);
	void Push(const int& e);
	int* Pop(int& x);
	void Print(void);
};
#endif
