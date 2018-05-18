#include "stdafx.h"
#include "BinaryHeap.h"

#include <fstream>
#include <iostream>
#include <string>

// default heap constructor is empty
// no need to pre-initialize elements array
BinaryHeap::BinaryHeap()
{
	this->heapElements = new Array();
}

// default destructor
BinaryHeap::~BinaryHeap()
{
	delete[] heapElements;
}

// returns current size (number of heap elements)
int BinaryHeap::getSize()
{
	return heapElements->getSize();
}

// adding new element to the heap using already existing pushBack function from the Array class
// fixing heap up after adding new element
void BinaryHeap::addNewElement(Edge* element)
{
	heapElements->pushBack(element);
	heapFix_UP(heapElements->getSize() - 1);
}

// deleting root element from the heap
void BinaryHeap::deleteRoot()
{
	if (heapElements->getSize() == 0)
	{
		std::cout << "Heap is empty" << std::endl;
		return;
	}

	heapElements->replaceValueOnIndex(0, heapElements->get(heapElements->getSize() - 1));		// copying last added element to the root node (on the top of the heap)
	heapElements->popBack();																	// deleting last added element 
	heapFix_DOWN(0);																			// fixing heap downwards
	std::cout << "Root Element Deleted" << std::endl;
}

// returns current maximum element (root)
Edge* BinaryHeap::getRoot()
{
	if (heapElements->getSize() == 0)
	{
		std::cout << "\nHeap is empty" << std::endl;
		return nullptr;
	}

	else return heapElements->get(0);
}

Edge * BinaryHeap::getFromIndex(int index)
{
	return heapElements->get(index);
}

// returns left child index of the selected element
int BinaryHeap::get_left_child(int parentIndex)
{
	int l_childIndex = 2 * parentIndex + 1;									// calculating left child index
	if (l_childIndex < heapElements->getSize()) return l_childIndex;		// if it's index fits in the current array (heap) size
	else return -1;															// -1 indicates that parent element has no left child
}

// returns right child index of the selected element
int BinaryHeap::get_right_child(int parentIndex)
{
	int r_childIndex = 2 * parentIndex + 2;									// calculating left child index
	if (r_childIndex < heapElements->getSize()) return r_childIndex;		// if it's index fits in the current array (heap) size
	else return -1;															// -1 indicates that parent element has no right child
}

// returns parent index for the selected child
int BinaryHeap::parent(int childIndex)
{
	int parentIndex = (childIndex - 1) / 2;									// calculating parent index
	if (childIndex == 0) return -1;											// if the selected element is root, return -1 (has no parent)
	else return parentIndex;
}

// fixing the heap upwards
// function compares current child element with its parent and if the parent element is smaller than it's child - swaps them
void BinaryHeap::heapFix_UP(int startIndex)
{
	if (startIndex >= 0 && parent(startIndex) >= 0 && heapElements->get(parent(startIndex))->weight > heapElements->get(startIndex)->weight)
	{
		Edge* tempHold = heapElements->get(startIndex); // temporary holding parent element
		heapElements->replaceValueOnIndex(startIndex, heapElements->get(parent(startIndex)));
		heapElements->replaceValueOnIndex(parent(startIndex), tempHold);
		delete tempHold;

		heapFix_UP(parent(startIndex));
	}
}

// fixing the heap downwards
// function compares current parent element with it's children
// if one of the children is bigger than it's parent - function swaps them
// if both children are bigger than their parent - function swaps parent element with bigger of it's children
void BinaryHeap::heapFix_DOWN(int startIndex)
{
	int first_child = get_left_child(startIndex);
	int second_child = get_right_child(startIndex);

	// if both children indexes are in the array and left child is smaller than right child - swap 
	if (first_child >= 0 && second_child >= 0 && heapElements->get(first_child)->weight > heapElements->get(second_child)->weight)
	{
		first_child = second_child;
	}

	// if parent element is smaller than it's current child - swap
	if (first_child > 0 && heapElements->get(startIndex)->weight > heapElements->get(first_child)->weight)
	{
		Edge* temp = heapElements->get(startIndex);	// temporary holding parent element
		heapElements->replaceValueOnIndex(startIndex, heapElements->get(first_child));
		heapElements->replaceValueOnIndex(first_child, temp);
		delete temp;

		heapFix_DOWN(first_child);
	}
}
