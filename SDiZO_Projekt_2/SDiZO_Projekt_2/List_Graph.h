#pragma once
#include "Node.h"

class List_Graph
{
private:
	int vertex;
	int edges;

	Node** adjacencyList;

public:
	List_Graph();
	~List_Graph();

	void readFromFile();
	void createRandom();

	Node* getNeighboursList(int);
	void Prims_algorithm();

	void print();
};

