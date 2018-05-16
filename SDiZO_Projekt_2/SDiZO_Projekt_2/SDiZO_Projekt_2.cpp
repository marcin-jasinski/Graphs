// SDiZO_Projekt_2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Menu.h"
#include <iostream>
#include "Matrix_Graph.h"

int main()
{
	//Menu mainMenu = Menu();

	Matrix_Graph matrixGraph = Matrix_Graph();

	std::cout << "Read from file(1) or create at random(2)? " << std::endl;
	int choice;
	std::cin.clear();
	fflush(stdin);
	std::cin >> choice;

	switch (choice) {
	case 1:
		matrixGraph.readFromFile();
		break;
	case 2:
		matrixGraph.createRandom();
		break;
	default:
		std::cout << "Error." << std::endl;
		break;
	}

	matrixGraph.print();
	matrixGraph.Prims_algorithm();

	std::cin.get();
	std::cin.get();
    return EXIT_SUCCESS;
}

