#pragma once
#include <string>

class Matrix_Graph
{
private:
	int vertex;
	int edges;

	int** graphMatrix;
	int* edgeWeights;

public:
	Matrix_Graph();
	~Matrix_Graph();

	void readFromFile(std::string, std::string);

	int get(int, int);
	void print();

	void Prims_algorithm();
};

