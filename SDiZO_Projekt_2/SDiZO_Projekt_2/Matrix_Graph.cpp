﻿#include "stdafx.h"
#include "Matrix_Graph.h"
#include "BinaryHeap.h"
#include "Array.h"
#include "Edge.h"

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>

Matrix_Graph::Matrix_Graph()
{
}

Matrix_Graph::~Matrix_Graph()
{
	for (int i = 0; i < vertex; i++) delete graphMatrix[i];
	delete[] graphMatrix;
	delete[] edgeWeights;
}

void Matrix_Graph::readFromFile(std::string sourceFile, std::string type)
{
	std::fstream file;
	file.open(sourceFile, std::ios::in);

	if (file.good() == true)
	{
		file >> edges >> vertex;
		int i, j;

		graphMatrix = new int*[vertex];		// tworzenie tablicy dynamicznej o rozmiarze = ilości wierzchołków
		for (i = 0; i < vertex; i++) graphMatrix[i] = new int[edges];	// dla każdego wierzchołka nowa tablica o rozmiarze = liczba krawędzi

		edgeWeights = new int[edges];	// tablica wag krawędzi

		for (i = 0; i < vertex; i++) {
			for (j = 0; j < edges; j++) {
				graphMatrix[i][j] = 0;			// początkowa inicjalizacja zerami
			}
		}

		int startVertex, endVertex, weight;

		for (i = 0; i < edges; i++)
		{
			file >> startVertex >> endVertex >> weight;		
			graphMatrix[startVertex][i] = 1;
			if (type == "nieskierowany") graphMatrix[endVertex][i] = 1;
			else graphMatrix[endVertex][i] = -1;
			edgeWeights[i] = weight;
		}

		file.close();
	}
	else std::cout << "Error opening file!!!" << std::endl;
}

int Matrix_Graph::get(int vertex, int edge)
{
	return graphMatrix[vertex][edge];
}

void Matrix_Graph::print()
{
	int i, j;

	std::cout << "\nMatrix representation: " << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(4) << " ";

	for (i = 0; i < edges; i++) std::cout << std::setw(4) << i;
	std::cout << std::endl << std::endl;

	for (i = 0; i < vertex; i++)
	{
		std::cout << std::setw(4) << i;
		for (j = 0; j < edges; j++) std::cout << std::setw(4) << (int)graphMatrix[i][j];
		std::cout << std::endl;
	}

	std::cout << "\nWeights of edges: " << std::endl;
	for (int i = 0; i < edges; i++)
	{
		std::cout << std::setw(2) << i << "->(" << edgeWeights[i] << ")";
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
	for (int i = 1; i < vertex; i++) visited[i] = false;	// a reszty na razie nie
	
	int v = 0;
	for (int i = 0; i < vertex - 1; i++)	// iterujemy po kolejnych wierzchołkach
	{	
		//std::cout << "\n==> Current vertex: " << v << std::endl;
		for (int e = 0; e < edges; e++) // i szukamy krawędzi zeń wychodzących
		{
			//std::cout << "Current edge: " << e << std::endl;
			if (get(v, e) == 1) // jeśli natrafiliśmy na krawędź
			{
				for (int v2 = 0; v2 < vertex; v2++) // to szukamy końca tej krawędzi
				{
					if (v != v2 && get(v2, e) == 1) // jeśli trafiliśmy na koniec
					{
						if (!visited[v2]) // to sprawdzamy, czy dany wierzchołek już nie był odwiedzony
						{
							//std::cout << "New edge found! -> " << v << " " << v2 << " weight: " << edgeWeights[e] << std::endl;
							queue.addNewElement(new Edge(v, v2, edgeWeights[e]));	// wrzucamy go do kolejki wierzchołków
							break;
						}
					}
				}
			}
		}

		/*
		std::cout << "\nList of edges currently in queue: " << std::endl;	// wypisanie aktualnej kolejki wierzchołków
		for (int x = 0; x < queue.getSize(); x++)
		{
			std::cout << queue.getFromIndex(x)->startVertex << " " << queue.getFromIndex(x)->endVertex << " weight: " << queue.getFromIndex(x)->weight << std::endl;
		}
		*/

		edge = queue.getRoot(); // pobranie pierwszej krawędzi z kopca (krawędź o najmniejszej wadze)

		if (edge == nullptr)
		{
			v++;
			if (v >= vertex) break;
			continue;
		}

		do	// czyszczenie kopca
		{
			queue.deleteRoot();
		} while (!edge->endVertex);

		primsEdges.pushBack(edge);
		//std::cout << "Edge added to primsEdges: " << edge->startVertex << " " << edge->endVertex << " weight: " << edge->weight << std::endl;
		visited[edge->endVertex] = true;
		queue.deleteRoot();
		v = edge->endVertex;
	}

	/*
	int e = primsEdges.getSize();
	int totalCost = 0;
	std::cout << "\n\nMinimal Spanning Tree for incidency matrix representation" << std::endl;
	for (int i = 0; i < e; i++)
	{
	std::cout << "Edge " << i << " -> " << primsEdges[i]->startVertex << " " << primsEdges[i]->endVertex << " weight: " << primsEdges[i]->weight << std::endl;
	totalCost += primsEdges[i]->weight;
	}
	std::cout << "\nTotal cost: " << totalCost << std::endl;
	*/
}

void Matrix_Graph::Dijikstras_algorithm(int startVertex, int endVertex)
{
	int* d = new int[vertex]; // tablica kosztów dojścia od startVertex do d[i]
	int* p = new int[vertex]; // tablica poprzedników na ścieżce

	bool* visited = new bool[vertex];
	for (int i = 0; i < vertex; i++) visited[i] = false;

	for (int i = 0; i < vertex; i++)
	{
		d[i] = INT32_MAX;	// tablica kosztów unstawiona na największą wartość ("nieskończoność")
		p[i] = -1;		// NULL oznacza brak poprzednika na najkrótszej ścieżce
	}
		
	d[startVertex] = 0;		// koszt odwiedzenia samego siebie równy zero
	visited[startVertex] = true;

	BinaryHeap queue = BinaryHeap();
	queue.addNewElement(new Edge(-1, startVertex, d[startVertex]));

	Array dijikstrasEdges = Array();
	Edge* edge;

	int unvisitedVertices = vertex - 1;
	int v;
	bool breakFlag = false;
	
	while (unvisitedVertices > 0)
	{
		while (true)
		{
			if (queue.getRoot() == nullptr)
			{
				breakFlag == true;
				break;
			}

			v = queue.getRoot()->endVertex;
			if (visited[v] == false) break;

			queue.deleteRoot();
		}
		
		if (breakFlag == true) break;

		if (v == endVertex) break;
		
		queue.deleteRoot();
		//std::cout << "\n==> Current vertex: " << v << std::endl;
		visited[v] = true;

		for (int e = 0; e < edges; e++) 
		{
			if (get(v, e) == 1) 
			{
				for (int v2 = 0; v2 < vertex; v2++) 
				{
					if (get(v2, e) == -1 && v2 != startVertex) 
					{
						//std::cout << "New edge found! -> " << v << " " << v2 << " weight: " << edgeWeights[e] << std::endl;
						int currentCost = d[v] + edgeWeights[e];
						if (currentCost < d[v2])
						{
							d[v2] = currentCost;
							p[v2] = v;
						}
						queue.addNewElement(new Edge(v, v2, d[v2]));
						break;
					}
				}
			}
		}
		
		/*
		std::cout << "\nList of edges currently in queue: " << std::endl;	
		for (int x = 0; x < queue.getSize(); x++)
		{
		std::cout << queue.getFromIndex(x)->startVertex << " " << queue.getFromIndex(x)->endVertex << " weight: " << queue.getFromIndex(x)->weight << std::endl;
		}
		*/

		unvisitedVertices--;
	}

	if (d[endVertex] == INT32_MAX) // jeżeli wierzchołek ani razu nie został odwiedzony
	{
		//std::cout << "Shortes path from " << startVertex << " to " << endVertex << " does not exist in matrix representation" << std::endl;
		return;
	}

	/*
	int e = dijikstrasEdges.getSize();
	int currentVertex = endVertex;
	std::cout << "\n\nShortest path for incidency matrix representation " << std::endl;
	while (currentVertex != -1)
	{
		std::cout << currentVertex << " <- ";
		currentVertex = p[currentVertex];
	}
	std::cout << "\nTotal cost: " << d[endVertex] << std::endl;
	*/
}
