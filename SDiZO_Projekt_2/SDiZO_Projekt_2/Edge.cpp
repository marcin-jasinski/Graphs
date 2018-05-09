#include "stdafx.h"
#include "Edge.h"

Edge::Edge()
{
	this->startVertex = 0;
	this->endVertex = 0;
	this->weight = 0;
}

Edge::Edge(int start, int end, int weight)
{
	this->startVertex = start;
	this->endVertex = end;
	this->weight = weight;
}

Edge::~Edge()
{
}

int Edge::getStartVertex()
{
	return startVertex; 
}

int Edge::getEndVertex()
{ 
	return endVertex; 
}

int Edge::getWeight()
{
	return weight; 
}
