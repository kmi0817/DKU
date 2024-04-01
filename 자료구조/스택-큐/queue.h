#pragma once
#ifndef queue_H
#define queue_H
class ChainNode;
//ø¨∞·≈•
class LinkedQueue {
private:
	ChainNode* front;
	ChainNode* rear;
public:
	LinkedQueue(void);
	void Push(const int& e);
	int* Pop(int& retvalue);
	void Print(void);
};
#endif
