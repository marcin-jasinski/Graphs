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

	void pushFront(Edge*);
	void pushBack(Edge*);
	void popFront();
	void popBack();

	void insertValueOnIndex(int, Edge*);
	void deleteValueFromIndex(int);
	void replaceValueOnIndex(int, Edge*);

	Edge* get(int);
	Edge* operator[](int) const;
};
