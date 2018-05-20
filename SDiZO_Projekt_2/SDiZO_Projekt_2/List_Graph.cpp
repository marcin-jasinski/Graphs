#include "stdafx.h"
#include "List_Graph.h"
#include "BinaryHeap.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

List_Graph::List_Graph()
{
}

List_Graph::~List_Graph()
{
	for (int i = 0; i < vertex; i++) delete adjacencyList[i];
	delete[] adjacencyList;
}

void List_Graph::readFromFile(std::string sourceFile, std::string type)
{
	std::fstream file;
	file.open(sourceFile, std::ios::in);

	if (file.good() == true)
	{
		file >> edges >> vertex;	
		
		Node* node;
		adjacencyList = new Node*[vertex];
		for (int i = 0; i < vertex; i++) adjacencyList[i] = NULL;
			
		int startVertex, endVertex, weight;
		int i = 0;

		for (int i = 0; i < edges; i++)
		{
			file >> startVertex >> endVertex >> weight;		

			node = new Node();
			node->vertex = endVertex;
			node->weight = weight;
			node->next = adjacencyList[startVertex];
			adjacencyList[startVertex] = node;

			if (type == "nieskierowany")
			{
				node = new Node();
				node->vertex = startVertex;
				node->weight = weight;
				node->next = adjacencyList[endVertex];
				adjacencyList[endVertex] = node;
			}
		}

		file.close();
	}
	else std::cout << "Error opening file!!!" << std::endl;
}

void List_Graph::print()
{
	Node* node;

	std::cout << "\nList representation:" << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < vertex; i++)
	{
		std::cout << "[" << i << "] =";
		node = adjacencyList[i];

		while (node)
		{
			std::cout << std::setw(3) << node->vertex;
			node = node->next;
		}
		std::cout << std::endl;
	}
}

Node* List_Graph::getNeighboursList(int vertex)
{
	return adjacencyList[vertex];
}

void List_Graph::Prims_algorithm()
{
	BinaryHeap queue = BinaryHeap();
	Array primsEdges = Array();
	Edge* edge = nullptr;
	Node* node = nullptr;
	bool* visited = new bool[vertex];	// tablica z informacj�, czy dany wierzcho�ek zosta� odwiedzony

	visited[0] = true;	// odwiedzamy od razu pierwszy wierzcho�ek
	for (int i = 1; i < vertex; i++) visited[i] = false;	// a reszty na razie nie

	int v = 0;
	for (int i = 0; i < vertex-1 ; i++)          // Do drzewa dodamy n - 1 kraw�dzi grafu
	{
		//std::cout << "\n==> Current vertex: " << v << std::endl;
		node = getNeighboursList(v);
		while (node)
		{
			if (!visited[node->vertex])
			{
				//std::cout << "New edge found! -> " << v << " " << node->vertex << " weight: " << node->weight << std::endl;
				queue.addNewElement(new Edge(v, node->vertex, node->weight));
			}
			node = node->next;
		}

		/*
		std::cout << "\nList of edges currently in queue: " << std::endl;	// wypisanie aktualnej kolejki wierzcho�k�w
		for (int x = 0; x < queue.getSize(); x++)
		{
			std::cout << queue.getFromIndex(x)->startVertex << " " << queue.getFromIndex(x)->endVertex << " weight: " << queue.getFromIndex(x)->weight << std::endl;
		}
		*/

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
		//std::cout << "\nEdge added to primsEdges: " << edge->startVertex << " " << edge->endVertex << " weight: " << edge->weight << std::endl;
		visited[edge->endVertex] = true;
		queue.deleteRoot();
		v = edge->endVertex;
	}

	/*
	int e = primsEdges.getSize();
	int totalCost = 0;
	std::cout << "\n\nMinimal Spanning Tree" << std::endl;
	for (int i = 0; i < e; i++)
	{
		std::cout << "Edge " << i << " -> " << primsEdges[i]->startVertex << " " << primsEdges[i]->endVertex << " weight: " << primsEdges[i]->weight << std::endl;
		totalCost += primsEdges[i]->weight;
	}
	std::cout << "\nTotal cost: " << totalCost << std::endl;;
	*/

	delete edge;
	delete node;
	delete[] visited;
}
