#pragma once
#include "stack.h"
#include "queue.h"
#ifndef chainNode_H
#define chainNode_H
class LinkedStack;
class LinkedQueue;
//노드 생성
class ChainNode {
	friend class LinkedStack;
	friend class LinkedQueue;
private:
	int data;
	ChainNode* link;
public:
	ChainNode(int element, ChainNode* next) { data = element; link = next; }
};
#endif
