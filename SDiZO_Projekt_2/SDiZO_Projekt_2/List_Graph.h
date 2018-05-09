#pragma once
#include "Edge.h"
#include <list>

class List_Graph
{
private:
	int vertex;
	int edges;
	std::list<Edge[]> edgesList;

public:
	List_Graph();
	~List_Graph();

	void Prims_algorithm();
	void Dijikstras_algorithm();
};

