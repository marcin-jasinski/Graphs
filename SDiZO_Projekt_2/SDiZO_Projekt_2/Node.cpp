#include "stdafx.h"
#include "Node.h"

// creates an empty node
Node::Node()
{
	this->next = nullptr;
	this->vertex = 0;
	this->weight = 0;
}

// creates a Node element with specified value, left and right neighbour
Node::Node(Node* _rightPtrArg, int endVertex, int edgeWeight)
{
	this->next = _rightPtrArg;
	this->vertex = endVertex;
	this->weight = edgeWeight;
}

// destructor sets current node neighbours to point at each other (so as if to "bypass" current node)
Node::~Node()
{
}
