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
#include <vector>
#include <functional>   // std::greater
#include <algorithm>    // std::sort

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
	std::ifstream file;
	int i, j;

	file.open("Dane.txt");
	if (file.good())
	{
		file >> edges >> vertex;	// odczyt liczby wierzcho�k�w i kraw�dzi grafu
		graphMatrix = new int*[edges];									// stworzenie dynamicznej tablicy dwuwymiarowej
		for (i = 0; i < edges; i++) graphMatrix[i] = new int[vertex];	// o rozmiarach wierzcho�ki x kraw�dzie

		edgeWeights = new int[edges];									// stworzenie tablicy z wagami kraw�dzi

		for (i = 0; i < vertex; i++) {
			for (j = 0; j < edges; j++) {
				graphMatrix[i][j] = 0;		// pocz�tkowe wyzerowanie ca�ej zawarto�ci macierzy grafu
			}
		}

		int startVertex, endVertex, weight;
		int i = 0;

		for (int i = 0; i < edges; i++)
		{
			file >> startVertex >> endVertex >> weight;		// odczytywanie kolejnych kraw�dzi i zapis do macierzy
			graphMatrix[startVertex][i] = 1;
			graphMatrix[endVertex][i] = -1;
			edgeWeights[i] = weight;
		}
	}

	file.close();
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

	edgeWeights = new int[edges];									// stworzenie tablicy z wagami kraw�dzi

	for (i = 0; i < vertex; i++) {
		for (j = 0; j < vertex; j++) {
			graphMatrix[i][j] = 0;		// pocz�tkowe wyzerowanie ca�ej zawarto�ci macierzy grafu
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

		graphMatrix[startVertex][i] = 1;
		graphMatrix[endVertex][i] = -1;
		weight = rand() % 100000 + 0;
		edgeWeights[i-1] = weight;
	}
}

int Matrix_Graph::get(int row, int column)
{
	return graphMatrix[row][column];
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

	std::cout << "\nWeights of edges: " << std::endl;
	for (int i = 0; i < edges; i++)
	{
		std::cout << edgeWeights[i] << " ";
	}
	std::cout << std::endl;
}

/*
void Matrix_Graph::Prims_algorithm()
{
	bool* visited = new bool[vertex];	// tablica z informacj�, czy dany wierzcho�ek zosta� odwiedzony
	visited[0] = true;	// odwiedzamy od razu pierwszy wierzcho�ek
	for (unsigned int i = 1; i < vertex; i++) visited[i] = false;	// a reszty na razie nie

	unsigned int v = 0;
	for (unsigned int i = 0; i < vertex - 1; i++)	// iterujemy po kolejnych wierzcho�kach
	{	
		for (unsigned int e = 0; e < edges; e++) // i szukamy kraw�dzi ze� wychodz�cych
		{
			if (get(v, e) == 1) // je�li natrafili�my na kraw�d�
			{
				for (unsigned int v2 = 0; v2 < vertex; v2++) // to szukamy ko�ca tej kraw�dzi
				{
					if (v != v2 && get(v2, e) == -1) // je�li trafili�my na koniec
					{
						if (!visited[v2]) // to sprawdzamy, czy dany wierzcho�ek ju� nie by� odwiedzony
						{
							std::cout << "New edge found!" << v << " " << v2 << " weight: " << edgeWeights[e] << std::endl;
							queue.push(Edge(v, v2, edgeWeights[e]));	// wrzucamy go do kolejki wierzcho�k�w
							break;
						}
					}
				}
			}
		}

		Edge edge;
		do
		{
			edge = queue.top();
		} while (visited[edge.endVertex]);
		visited[edge.endVertex] = true;
		primsEdges.push_back(edge);
		std::cout << "\nEdge added to primsEdges: " << edge.startVertex << " " << edge.endVertex << " " << edge.weight << std::endl;
		v = edge.endVertex;
	}

	primsEdges.shrink_to_fit();
	int e = primsEdges.size();
	int totalCost = 0;
	std::cout << "Minimal Spanning Tree" << std::endl;
	for (int i = 0; i < e; i++)
	{
		std::cout << primsEdges[i].startVertex << " " << primsEdges[i].endVertex << " weight: " << primsEdges[i].weight << std::endl;
		totalCost += primsEdges[i].weight;
	}

	std::cout << "\nTotal cost: " << totalCost << std::endl;
}
*/