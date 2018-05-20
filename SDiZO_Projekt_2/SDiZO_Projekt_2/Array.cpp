#include "stdafx.h"
#include "Array.h"

#include <fstream>
#include <string>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <cstdlib>

// default constructor of an array
Array::Array()
{
	this->arraySize = 0;
	this->_headPtr = new Edge*[0];
}

// constructor creating an array of a specified size
// assigns new dynamicly allocated array of pointers to edges to _headPtr
Array::Array(int arraySize)
{
	this->arraySize = arraySize;
	this->_headPtr = new Edge*[arraySize];
}

// default destructor
// releasing memory 
Array::~Array()
{
	delete[] _headPtr;
	this->arraySize = 0;
}

// returns current size (number of elements in the array)
int Array::getSize() const
{
	return arraySize;
}

// inserts an element on the end of the array
void Array::pushBack(Edge* element)
{
	// if the array is empty
	if (arraySize == 0) {
		_headPtr = new Edge*[1];	// create new one-element array
		_headPtr[0] = element;
		arraySize++;
	}
	else {
		Edge** _tempPtr = new Edge*[arraySize + 1];						// same thing as above, but this time element is inserted on the end of array
		memcpy(_tempPtr, _headPtr, arraySize * sizeof(Edge*));
		delete[] _headPtr;
		_tempPtr[arraySize] = element;
		_headPtr = _tempPtr;
		arraySize++;
	}
}

// deletes last array element
void Array::popBack()
{
	if (arraySize == 0) {
		//std::cout << "Array is empty." << std::endl;
		return;
	}

	deleteValueFromIndex(arraySize - 1);
}

// deletes element from the specified index and relocates array with a new size
// elements originally placed after selected index are shifted by one index number down
void Array::deleteValueFromIndex(int index)
{
	// Index out of bounds 
	if (index < 0 || index >= arraySize)
	{
		//std::cout << "Index out of bounds." << std::endl;
		return;
	}

	// there is no point of deleting a value from a non-existant array
	if (arraySize == 0) {
		//std::cout << "Array is empty." << std::endl;
		return;
	}

	Edge** _tempPtr = new Edge*[arraySize - 1];						// temporal "buffer" array for holding already existing elements
	memcpy(_tempPtr, _headPtr, index * sizeof(Edge*));
	arraySize--;
	memcpy(_tempPtr + index, this->_headPtr + index + 1, (this->arraySize - index) * sizeof(Edge*));
	delete[] _headPtr;
	_headPtr = _tempPtr;
}

// replacing an old value at index "index" with a new one "element"
void Array::replaceValueOnIndex(int index, Edge* element)
{
	// Index out of bounds 
	if (index < 0 || index >= arraySize)
	{
		//std::cout << "Index out of bounds." << std::endl;
		return;
	}

	_headPtr[index] = element;
}

Edge* Array::get(int index)
{
	return *(_headPtr + index);
}

// overloaded [] operator for array-like element acces
Edge* Array::operator[](int index) const
{
	return *(_headPtr + index);
}
