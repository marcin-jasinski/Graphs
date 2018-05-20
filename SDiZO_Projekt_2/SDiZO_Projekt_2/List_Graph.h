#pragma once
#include "Node.h"
#include <string>

class List_Graph
{
private:
	int vertex;
	int edges;

	Node** adjacencyList;

public:
	List_Graph();
	~List_Graph();

	void readFromFile(std::string, std::string);

	Node* getNeighboursList(int);
	void Prims_algorithm();

	void print();
};

