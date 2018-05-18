#include "stdafx.h"
#include "Menu.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::showMainMenu()
{
	std::cout << "<=== BADANIE EFEKTYWNOŒCI ALGORYTMÓW GRAFOWYCH ===>" << std::endl;
	std::cout << "\nWybierz Ÿród³o danych: " << std::endl;
	std::cout << "1 - wczytaj z pliku" << std::endl;
	std::cout << "2 - wygeneruj graf losowo" << std::endl;
	std::cout << "3 - WYJSCIE" << std::endl;
	std::cout << "//> ";
}

void Menu::generateRandomData(int edges, int vertex)
{
	std::fstream file;
	file.open("random_data.txt", std::ios::out);

	if (file.good())
	{
		file << edges << " " << vertex << std::endl;

		int startVertex, endVertex, weight;

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


