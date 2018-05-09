#include "stdafx.h"
#include "Matrix_Graph.h"
#include "Edge.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>

Matrix_Graph::Matrix_Graph()
{
	std::cout << "Read from file(1) or create at random(2)? " << std::endl;
	int choice;
	std::cin >> choice;

	switch (choice) {
	case 1:
		readFromFile();
		break;
	case 2:
		createRandom();
		break;
	default:
		std::cout << "Error." << std::endl;
		break;
	}
}

Matrix_Graph::~Matrix_Graph()
{
}

void Matrix_Graph::readFromFile()
{
	std::fstream file;
	int i, j;

	file.open("Dane.txt", std::ios::in);
	if (file.good())
	{
		file >> edges >> vertex;	// odczyt liczby wierzcho³ków i krawêdzi grafu
		graphMatrix = new int*[edges];									// stworzenie dynamicznej tablicy dwuwymiarowej
		for (i = 0; i < edges; i++) graphMatrix[i] = new int[vertex];	// o rozmiarach wierzcho³ki x krawêdzie

		edgeWeights = new int[edges];									// stworzenie tablicy z wagami krawêdzi

		for (i = 0; i < vertex; i++) {
			for (j = 0; j < edges; j++) {
				graphMatrix[i][j] = 0;		// pocz¹tkowe wyzerowanie ca³ej zawartoœci macierzy grafu
			}
		}

		int startVertex, endVertex, weight;
		int i = 0;

		for (int i = 0; i < edges; i++)
		{
			file >> startVertex >> endVertex >> weight;
			graphMatrix[startVertex][i] = 1;
			graphMatrix[endVertex][i] = -1;
			edgeWeights[i] = weight;
		}

		file.close();
	}
}

void Matrix_Graph::createRandom()
{
	std::cout << "Number of vertex: ";
	std::cin >> vertex;
	std::cout << "Number of edges: ";
	std::cin >> edges;

	int i, j;
	graphMatrix = new int*[vertex];									// stworzenie dynamicznej tablicy dwuwymiarowej
	for (i = 0; i < vertex; i++) graphMatrix[i] = new int[vertex];	// o rozmiarach n x n

	edgeWeights = new int[edges];									// stworzenie tablicy z wagami krawêdzi

	for (i = 0; i < vertex; i++) {
		for (j = 0; j < vertex; j++) {
			graphMatrix[i][j] = 0;		// pocz¹tkowe wyzerowanie ca³ej zawartoœci macierzy grafu
		}
	}

	int startVertex, endVertex, weight;
	for (i = 1; i <= edges; i++)
	{
		startVertex = (std::rand() % vertex) + 0;
		do
		{
			endVertex = (std::rand() % vertex) + 0;
		} while (endVertex == startVertex);

		graphMatrix[startVertex][endVertex] = 1;
		weight = rand() % 1000000 + 0;
		edgeWeights[i-1] = weight;
	}
}

int Matrix_Graph::get(int column, int row)
{
	return graphMatrix[column][row];
}

void Matrix_Graph::print()
{
	int i, j;

	std::cout << "\nMatrix representation: " << std::endl;
	std::cout << "   ";
	for (i = 0; i < edges; i++) std::cout << std::setw(3) << i;
	std::cout << std::endl << std::endl;
	for (i = 0; i < vertex; i++)
	{
		std::cout << std::setw(3) << i;
		for (j = 0; j < edges; j++) std::cout << std::setw(3) << (int)graphMatrix[i][j];
		std::cout << std::endl;
	}

	std::cout << "\n\Weights of edges: " << std::endl;
	for (int i = 0; i < edges; i++)
	{
		std::cout << edgeWeights[i] << " ";
	}
}

void Matrix_Graph::Prims_algorithm()
{

}
