#include "stdafx.h"
#include "Benchmark_tests.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

Benchmark_tests::Benchmark_tests()
{
}


Benchmark_tests::~Benchmark_tests()
{
}

void Benchmark_tests::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li)) std::cout << "QueryPerformanceFrequency failed!\n";
	PCFreq = double(li.QuadPart) / 1000.0;
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double Benchmark_tests::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void Benchmark_tests::runTests(int vertex, double density)
{
	double endTime;
	double totalTime;
	double averageTime;

	std::fstream file;
	file.open("benchmark.txt", std::ios::out | std::ios::app);
	if (file.good())
	{
		std::cout << "Benchmark file opened, ready for input data." << std::endl;
		//file << "\nTesting for " << vertex << " vertices with density of " << density << std::endl;
	}
	else
	{
		std::cout << "Error opening benchmark file, abort." << std::endl;
		return;
	}

	system("cls");
	file << "\nPrim's algorithm for matrix graph. Vertices: " << vertex << ", density: " << density << std::endl;
	std::cout << "\nPrim's algorithm for matrix graph. Vertices: " << vertex << ", density: " << density << std::endl;
	totalTime = 0;
	averageTime = 0;
	for (int i = 1; i <= 100; i++)
	{
		generateRandomGraph(vertex, density);
		mg.readFromFile("random_data.txt", "nieskierowany");

		StartCounter();
		mg.Prims_algorithm();
		endTime = GetCounter();

		std::cout << i << ") -> " << endTime << std::endl;
		//file << endTime << std::endl;

		totalTime += endTime;

		mg.~Matrix_Graph();
	}
	averageTime = totalTime / 100;
	std::cout << "Average performance time: " << averageTime << std::endl;
	file << "Average time: " << averageTime << std::endl;

	system("cls");
	file << "\nPrim's algorithm for list graph. Vertices: " << vertex << ", density: " << density << std::endl;
	std::cout << "\nPrim's algorithm for list graph. Vertices: " << vertex << ", density: " << density << std::endl;
	totalTime = 0;
	averageTime = 0;
	for (int i = 1; i <= 100; i++)
	{
		generateRandomGraph(vertex, density);
		lg.readFromFile("random_data.txt", "nieskierowany");

		StartCounter();
		lg.Prims_algorithm();
		endTime = GetCounter();

		std::cout << i << ") -> " << endTime << std::endl;
		//file << endTime << std::endl;

		totalTime += endTime;

		lg.~List_Graph();
	}
	averageTime = totalTime / 100;
	std::cout << "Average performance time: " << averageTime << std::endl;
	file << "Average time: " << averageTime << std::endl;
}

void Benchmark_tests::generateRandomGraph(int vertex, double density)
{
	int maxEdges = vertex * (vertex - 1) / 2;
	int edges = density * maxEdges;

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
	}
	else std::cout << "File acces denied!" << std::endl;
}
