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
	matrixGraph.print();
	matrixGraph.Prims_algorithm();

	std::cin.get();
	std::cin.get();
    return EXIT_SUCCESS;
}

