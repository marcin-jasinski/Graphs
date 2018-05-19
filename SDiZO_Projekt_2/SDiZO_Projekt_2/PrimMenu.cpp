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
	std::cout << "Wybierz Ÿród³o danych: " << std::endl;
	std::cout << "1 - wczytanie z pliku." << std::endl;
	std::cout << "2 - losowy graf" << std::endl;
	std::cout << "\\>";
	
	int userChoice;
	int vertices, edges, maxEdges;
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
		std::cout << "Graph density (0.0 to 1.0) ";
		std::cin >> density;
		maxEdges = vertices * (vertices - 1) / 2;
		edges = density * maxEdges;
		generateRandomGraph(vertices, edges);
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

void PrimMenu::generateRandomGraph(int vertex, int edges)
{
	std::fstream file;
	file.open("random_data.txt", std::ios::out);

	if (file.good())
	{
		file << edges << " " << vertex << std::endl;

		int startVertex, endVertex, weight;

		srand(time(NULL));

		for (int i = 0; i < vertex; i++)
		{
			do
			{
				endVertex = rand() % vertex;
			} while (endVertex == i);

			weight = rand() % 10000;

			file << i << " " << endVertex << " " << weight << std::endl;
		}

		for (int i = vertex; i < edges; i++)
		{
			startVertex = rand() % vertex;
			do
			{
				endVertex = rand() % vertex;
			} while (endVertex == startVertex);

			weight = rand() % 10000;

			file << startVertex << " " << endVertex << " " << weight << std::endl;
		}

		file.close();
		std::cout << "Done." << std::endl;
	}
	else std::cout << "File acces denied!" << std::endl;
}
