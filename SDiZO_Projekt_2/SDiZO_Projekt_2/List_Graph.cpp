#include "stdafx.h"
#include "List_Graph.h"

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
}

void List_Graph::readFromFile()
{
	std::fstream file;
	file.open("Dane.txt", std::ios::in);

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

			node = new Node();
			node->vertex = startVertex;
			node->weight = weight;
			node->next = adjacencyList[endVertex];
			adjacencyList[endVertex] = node;
		}

		file.close();
	}
	else std::cout << "Error opening file!!!" << std::endl;
}

void List_Graph::createRandom()
{
	std::cout << "Number of vertex: ";
	std::cin >> vertex;
	std::cout << "Number of edges: ";
	std::cin >> edges;

	Node* node;
	adjacencyList = new Node*[vertex];
	for (int i = 0; i < vertex; i++) adjacencyList[i] = NULL;
	
	unsigned int startVertex, endVertex, weight;

	srand(time(NULL));

	for (int i = 0; i < edges; i++)
	{
		startVertex = rand() % vertex;

		do
		{
			endVertex = rand() % vertex;
		} while (startVertex == endVertex);

		weight = rand() % 10000;

		node = new Node();
		node->vertex = endVertex;
		node->weight = weight;
		node->next = adjacencyList[startVertex];
		adjacencyList[startVertex] = node;

		node = new Node();
		node->vertex = startVertex;
		node->weight = weight;
		node->next = adjacencyList[endVertex];
		adjacencyList[endVertex] = node;
	}
}

void List_Graph::print()
{

	Node* node;

	std::cout << "List representation:" << std::endl;
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
