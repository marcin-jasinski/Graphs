#pragma once
#include "Edge.h"

class Array
{
private:
	Edge** _headPtr;	// pointer to dynamic array of integers
	int arraySize;  // current number of elements in the array

public:
	Array();
	Array(int);
	~Array();

	int getSize() const;

	void pushBack(Edge*);
	void popBack();

	void deleteValueFromIndex(int);
	void replaceValueOnIndex(int, Edge*);

	Edge* get(int);
	Edge* operator[](int) const;
};
