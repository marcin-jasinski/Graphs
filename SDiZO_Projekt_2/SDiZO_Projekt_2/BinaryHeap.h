#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "Array.h"
#include "Edge.h"

class BinaryHeap
{
private:
	// using alredy existing Array class with all its functionality 
	Array* heapElements;

	int get_left_child(int);
	int get_right_child(int);
	int parent(int);

	// private functions for fixing heapifying up and down after adding / deleting elements
	void heapFix_UP(int);
	void heapFix_DOWN(int);

public:

	BinaryHeap();
	~BinaryHeap();

	Edge getRoot();
	int getSize();

	void addNewElement(Edge);
	void deleteRoot();
};