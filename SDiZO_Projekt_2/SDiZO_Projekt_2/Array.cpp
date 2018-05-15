#include "stdafx.h"
#include "Array.h"
#include <fstream>
#include <string>
#include <iostream>
#include <conio.h>

// default constructor of an array
Array::Array()
{
	this->arraySize = 0;
	this->_headPtr = nullptr;
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
	delete [] *_headPtr;
	this->arraySize = 0;
}

// returns current size (number of elements in the array)
int Array::getSize() const
{
	return this->arraySize;
}

// inserts en element on the beginning of the array
void Array::pushFront(Edge* element)
{
	//if the array is empty
	if (this->arraySize == 0) {
		this->_headPtr = new Edge*[1];	// create new one-element array
		this->_headPtr[0] = element;
		this->arraySize++;
	}
	else {
		Edge** _tempPtr = new Edge*[this->arraySize + 1];						// temporal "buffer" array for holding already existing elements
		memcpy(_tempPtr + 1, this->_headPtr, arraySize * sizeof(Edge*));		// copy elements from existing array to buffer shifted by one index up
		delete[] _headPtr;													// free memory currently occupied by old array (elements are safely copied to buffer)
		_tempPtr[0] = element;												// place new element on the beginning of buffer array
		this->_headPtr = _tempPtr;											// assign head pointer to buffer array
		this->arraySize++;
	}
}

// inserts an element on the end of the array
void Array::pushBack(Edge* element)
{
	// if the array is empty
	if (this->arraySize == 0) {
		this->_headPtr = new Edge*[1];	// create new one-element array
		this->_headPtr[0] = element;
		this->arraySize++;
	}
	else {
		Edge** _tempPtr = new Edge*[arraySize + 1];								// same thing as above, but this time element is inserted on the end of array
		memcpy(_tempPtr, _headPtr, arraySize * sizeof(Edge*));
		delete[] _headPtr;
		_tempPtr[arraySize] = element;
		_headPtr = _tempPtr;
		this->arraySize++;
	}
}

// deletes first array element
void Array::popFront()
{
	if (this->arraySize == 0) {
		std::cout << "Array is empty." << std::endl;
		return;
	}

	deleteValueFromIndex(0);
}

// deletes last array element
void Array::popBack()
{
	if (this->arraySize == 0) {
		std::cout << "Array is empty." << std::endl;
		return;
	}

	deleteValueFromIndex(this->arraySize - 1);
}

// relocates array with a new size and places new element on a specified index
// elements originally placed after selected index are shifted by one index number up
void Array::insertValueOnIndex(int index, Edge* element)
{
	// Index out of bounds 
	if (index < 0 || index >= arraySize)
	{
		std::cout << "Index out of bounds." << std::endl;
		return;
	}

	// there is no point of inserting a value to a non-existant array without explicit intention
	if (this->arraySize == 0) return;

	Edge** _tempPtr = new Edge*[this->arraySize + 1];				 // temporal "buffer" array for holding already existing elements
	memcpy(_tempPtr, this->_headPtr, index * sizeof(Edge*));		 // copying to buffer only elements originally being "above" new element (thus index*sizeof(int))
	_tempPtr[index] = element;
	memcpy(_tempPtr + index + 1, this->_headPtr + index, (this->arraySize - index) * sizeof(Edge*)); // placing the rest of the elements back with one index up
	delete[] _headPtr;
	this->_headPtr = _tempPtr;	// assigning head pointer back to point on array
	this->arraySize++;
}

// deletes element from the specified index and relocates array with a new size
// elements originally placed after selected index are shifted by one index number down
void Array::deleteValueFromIndex(int index)
{
	// Index out of bounds 
	if (index < 0 || index >= arraySize)
	{
		std::cout << "Index out of bounds." << std::endl;
		return;
	}

	// there is no point of deleting a value from a non-existant array
	if (arraySize == 0) {
		std::cout << "Array is empty." << std::endl;
		return;
	}

	Edge** _tempPtr = new Edge*[arraySize - 1];						// temporal "buffer" array for holding already existing elements
	memcpy(_tempPtr, _headPtr, index * sizeof(Edge*));
	this->arraySize--;
	memcpy(_tempPtr + index, this->_headPtr + index + 1, (this->arraySize - index) * sizeof(Edge*));
	delete [] _headPtr;
	this->_headPtr = _tempPtr;
}

// replacing an old value at index "index" with a new one "element"
void Array::replaceValueOnIndex(int index, Edge* element)
{
	// Index out of bounds 
	if (index < 0 || index >= arraySize)
	{
		std::cout << "Index out of bounds." << std::endl;
		return;
	}

	this->_headPtr[index] = element;
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

  