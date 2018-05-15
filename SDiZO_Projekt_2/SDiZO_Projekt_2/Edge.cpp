#include "stdafx.h"
#include "Edge.h"

Edge::Edge()
{
	this->startVertex = 0;
	this->endVertex = 0;
	this->weight = 0;
}

Edge::Edge(int s, int e, int w)
{
	this->startVertex = s;
	this->endVertex = e;
	this->weight = w;
}

Edge::~Edge()
{

}
