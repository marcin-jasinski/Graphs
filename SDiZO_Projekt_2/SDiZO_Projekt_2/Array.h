#pragma once
#include "Edge.h"
#include <iostream>

class Array
{
private:
	Edge* _headPtr;	// pointer to dynamic array of Edges
	int arraySize;  // current number of Edges in the array

public:
	Array();
	Array(int);
	~Array();

	int getSize() const;
	Edge* getHeadPtr();

	void pushFront(Edge);
	void pushBack(Edge);
	void popFront();
	void popBack();

	void insertValueOnIndex(int, Edge);
	void deleteValueFromIndex(int);
	void replaceValueOnIndex(int, Edge);

	Edge get(int);
	Edge operator[](int) const;
};

