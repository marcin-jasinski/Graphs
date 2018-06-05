#include "stdafx.h"
#include "PrimMenu.h"

#include <ctime>
#include <cstdlib>

PrimMenu::PrimMenu()
{
}

PrimMenu::~PrimMenu()
{
}

void PrimMenu::showPrimsMenu()
{
	system("cls");
	std::cout << "1 - read from file." << std::endl;
	std::cout << "2 - random graph" << std::endl;
	std::cout << "\\>";
	
	int userChoice;
	int vertices;
	double density;
	std::cin >> userChoice;

	switch (userChoice)
	{
	case 1:
		mg.readFromFile("Dane.txt", "nieskierowany");
		lg.readFromFile("Dane.txt", "nieskierowany");
		std::cout << "Done reading from file." << std::endl;
		mg.print();
		lg.print();
		std::cout << "\n\nPress ENTER to run Prim's algorithm." << std::endl;
		std::cin.get();
		std::cin.get();
		mg.Prims_algorithm();
		lg.Prims_algorithm();
		break;
		
	case 2:
		std::cout << "Number of vertices: ";
		std::cin >> vertices;
		std::cout << "Density : ";
		std::cin >> density;
		generateRandomGraph(vertices, density);
		mg.readFromFile("random_data.txt", "nieskierowany");
		lg.readFromFile("random_data.txt", "nieskierowany");
		mg.print();
		lg.print();
		std::cout << "\n\nPress ENTER to run Prim's algorithm." << std::endl;
		std::cin.get();
		std::cin.get();
		mg.Prims_algorithm();
		lg.Prims_algorithm();
		break;

	default:
		std::cout << "Wrong input." << std::endl;
		break;
	}
}

void PrimMenu::generateRandomGraph(int vertex, double density)
{
	int maxEdges = vertex * (vertex - 1) / 2;
	int edges = density * maxEdges;

	if (edges < vertex - 1)
	{
		std::cout << "Przy tej gestosci graf moze nie byc spojny!" << std::endl;
		return;
	}

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

			weight = rand() % 100000;
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

			weight = rand() % 100000;
			edgesMatrix[startVertex][endVertex] = weight;
			edgesMatrix[endVertex][startVertex] = weight;
			file << startVertex << " " << endVertex << " " << weight << std::endl;
		}

		file.close();
	}
	else std::cout << "File acces denied!" << std::endl;
}
