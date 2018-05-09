#pragma once
#include "Edge.h"

class PriorityQueue
{
private:
	Edge * edgeQueue;
	int heapPosition;

public:
	PriorityQueue(int n);
	~PriorityQueue();

	Edge getFirst();
	void push(Edge);
	void pop();
};

