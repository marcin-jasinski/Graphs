#include "stdafx.h"
#include "DijikstraMenu.h"

#include <fstream>
#include <cstdlib>
#include <ctime>

DijikstraMenu::DijikstraMenu()
{
}

DijikstraMenu::~DijikstraMenu()
{
}

void DijikstraMenu::showDijikstraMenu()
{
	system("cls");
	std::cout << "1 - read from file." << std::endl;
	std::cout << "2 - random graph" << std::endl;
	std::cout << "\\>";

	int userChoice, vertices;
	int startingVertex, endingVertex;
	double density;
	std::cin >> userChoice;

	switch (userChoice)
	{
	case 1:
		mg.readFromFile("Dane.txt", "skierowany");
		lg.readFromFile("Dane.txt", "skierowany");
		std::cout << "Done reading from file." << std::endl;
		mg.print();
		lg.print();
		std::cout << "\nStarting vertex: ";
		std::cin >> startingVertex;
		std::cout << "Ending vertex: ";
		std::cin >> endingVertex;
		mg.Dijikstras_algorithm(startingVertex, endingVertex);
		lg.Dijikstras_algorithm(startingVertex, endingVertex);
		break;

	case 2:
		std::cout << "Number of vertices: ";
		std::cin >> vertices;
		std::cout << "Density: ";
		std::cin >> density;
		generateRandomGraph(vertices, density);
		mg.readFromFile("random_data.txt", "skierowany");
		lg.readFromFile("random_data.txt", "skierowany");
		mg.print();
		lg.print();
		std::cout << "\nStarting vertex: ";
		std::cin >> startingVertex;
		std::cout << "Ending vertex: ";
		std::cin >> endingVertex;
		mg.Dijikstras_algorithm(startingVertex, endingVertex);
		lg.Dijikstras_algorithm(startingVertex, endingVertex);
		break;

	default:
		std::cout << "Wrong input." << std::endl;
		break;
	}
}

void DijikstraMenu::generateRandomGraph(int vertex, double density)
{
	int maxEdges = vertex * (vertex - 1) / 2;
	int edges = density * maxEdges;

	int** edgesMatrix = new int*[vertex];
	for (int i = 0; i < vertex; i++) edgesMatrix[i] = new int[vertex];

	for (int i = 0; i < vertex; i++)
	{
		for (int j = 0; j < vertex; j++) edgesMatrix[i][j] = INT32_MAX;
	}

	std::fstream file;
	file.open("random_data.txt", std::ios::out);

	if (file.good())
	{

		file << edges << " " << vertex << std::endl;

		int startVertex, endVertex, weight;

		srand(time(NULL));

		for (int i = 0; i < vertex; i++)
		{
			if (i == 0) continue;
			do
			{
				endVertex = rand() % i;
			} while (endVertex == i);

			weight = rand() % 10000;
			edgesMatrix[i][endVertex] = weight;
			edgesMatrix[endVertex][i] = weight;
			file << i << " " << endVertex << " " << weight << std::endl;
		}

		for (int i = vertex; i <= edges; i++)
		{
			startVertex = rand() % vertex;
			do
			{
				endVertex = rand() % vertex;
			} while (endVertex == startVertex || edgesMatrix[startVertex][endVertex] != INT32_MAX || edgesMatrix[endVertex][startVertex] != INT32_MAX);

			weight = rand() % 10000;
			edgesMatrix[startVertex][endVertex] = weight;
			edgesMatrix[endVertex][startVertex] = weight;
			file << startVertex << " " << endVertex << " " << weight << std::endl;
		}

		file.close();
	}
	else std::cout << "File acces denied!" << std::endl;
}
