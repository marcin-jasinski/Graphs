#include "stdafx.h"
#include "Matrix_Graph.h"
#include "Edge.h"
#include "BinaryHeap.h"
#include "Array.h"

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
}

Matrix_Graph::~Matrix_Graph()
{
}

void Matrix_Graph::readFromFile()
{
	std::fstream file;
	int i, j;

	file.open("Dane.txt", std::ios::in);

	if (file.good() == true)
	{
		file >> edges >> vertex;	// odczyt liczby wierzchołków i krawędzi grafu
		graphMatrix = new int*[edges];									// stworzenie dynamicznej tablicy dwuwymiarowej
		for (i = 0; i < edges; i++) graphMatrix[i] = new int[vertex];	// o rozmiarach wierzchołki x krawędzie

		edgeWeights = new int[edges];									// stworzenie tablicy z wagami krawędzi

		for (i = 0; i < vertex; i++) {
			for (j = 0; j < edges; j++) {
				graphMatrix[i][j] = 0;		// początkowe wyzerowanie całej zawartości macierzy grafu
			}
		}

		int startVertex, endVertex, weight;
		int i = 0;

		for (int i = 0; i < edges; i++)
		{
			file >> startVertex >> endVertex >> weight;		// odczytywanie kolejnych krawędzi i zapis do macierzy
			graphMatrix[startVertex][i] = 1;
			graphMatrix[endVertex][i] = 1;
			edgeWeights[i] = weight;
		}

		file.close();
	}
	else std::cout << "Error opening file!!!" << std::endl;
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

	edgeWeights = new int[edges];									// stworzenie tablicy z wagami krawędzi

	for (i = 0; i < vertex; i++) {
		for (j = 0; j < edges; j++) {
			graphMatrix[i][j] = 0;		// początkowe wyzerowanie całej zawartości macierzy grafu
		}
	}

	unsigned int startVertex, endVertex, weight;

	srand(time(NULL));
	for (int i = 0; i < edges; i++)
	{
		startVertex = rand() % vertex;

		do
		{
			endVertex = rand() % vertex;
		} while (startVertex == endVertex);

		graphMatrix[startVertex][i] = 1;
		graphMatrix[endVertex][i] = 1;
		weight = rand() % 10000;
		edgeWeights[i] = weight;

		std::cout << startVertex << " " << endVertex << " -> " << weight << std::endl;
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
	std::cout << std::endl;
	for (i = 0; i < edges; i++) std::cout << std::setw(4) << i;
	std::cout << std::endl << std::endl;
	for (i = 0; i < vertex; i++)
	{
		std::cout << std::setw(3) << i;
		for (j = 0; j < edges; j++) std::cout << std::setw(4) << (int)graphMatrix[i][j];
		std::cout << std::endl;
	}

	std::cout << "\nWeights of edges: " << std::endl;
	for (int i = 0; i < edges; i++)
	{
		std::cout << "[" << edgeWeights[i] << "]";
	}
	std::cout << std::endl;
}

void Matrix_Graph::Prims_algorithm()
{
	BinaryHeap queue = BinaryHeap();
	Array primsEdges = Array();
	Edge* edge;
	bool* visited = new bool[vertex];	// tablica z informacją, czy dany wierzchołek został odwiedzony
	visited[0] = true;	// odwiedzamy od razu pierwszy wierzchołek
	for (unsigned int i = 1; i < vertex; i++) visited[i] = false;	// a reszty na razie nie
	
	unsigned int v = 0;
	for (unsigned int i = 0; i < vertex - 1; i++)	// iterujemy po kolejnych wierzchołkach
	{	
		std::cout << "\n==> Current vertex: " << v << std::endl;
		for (unsigned int e = 0; e < edges; e++) // i szukamy krawędzi zeń wychodzących
		{
			std::cout << "Current edge: " << e << std::endl;
			if (get(v, e) == 1) // jeśli natrafiliśmy na krawędź
			{
				for (unsigned int v2 = 0; v2 < vertex; v2++) // to szukamy końca tej krawędzi
				{
					if (v != v2 && get(v2, e) == 1) // jeśli trafiliśmy na koniec
					{
						if (!visited[v2]) // to sprawdzamy, czy dany wierzchołek już nie był odwiedzony
						{
							std::cout << "New edge found! -> " << v << " " << v2 << " weight: " << edgeWeights[e] << std::endl;
							queue.addNewElement(new Edge(v, v2, edgeWeights[e]));	// wrzucamy go do kolejki wierzchołków
							break;
						}
					}
				}
			}
		}

		std::cout << "\nList of edges currently in queue: " << std::endl;	// wypisanie aktualnej kolejki wierzchołków
		for (int x = 0; x < queue.getSize(); x++)
		{
			std::cout << queue.getFromIndex(x)->startVertex << " " << queue.getFromIndex(x)->endVertex << " weight: " << queue.getFromIndex(x)->weight << std::endl;
		}

		edge = queue.getRoot();
		if (edge == nullptr)
		{
			v++;
			if (v >= vertex) break;
			continue;
		}

		do
		{
			queue.deleteRoot();
		} while (!edge->endVertex);

		primsEdges.pushBack(edge);
		std::cout << "Edge added to primsEdges: " << edge->startVertex << " " << edge->endVertex << " weight: " << edge->weight << std::endl;
		visited[edge->endVertex] = true;
		queue.deleteRoot();
		v = edge->endVertex;
	}

	int e = primsEdges.getSize();
	int totalCost = 0;
	std::cout << "\n\nMinimal Spanning Tree" << std::endl;
	for (int i = 0; i < e; i++)
	{
		std::cout << "Edge " << i << " -> " << primsEdges[i]->startVertex << " " << primsEdges[i]->endVertex << " weight: " << primsEdges[i]->weight << std::endl;
		totalCost += primsEdges[i]->weight;
	}
	std::cout << "\nTotal cost: " << totalCost << std::endl;
}
