#pragma once

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

	void readFromFile();
	void createRandom();

	int get(int, int);
	void print();

	void Prims_algorithm();
};

