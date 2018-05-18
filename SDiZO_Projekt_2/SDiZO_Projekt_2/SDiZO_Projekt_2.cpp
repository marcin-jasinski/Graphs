// SDiZO_Projekt_2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Menu.h"
#include <iostream>
#include "Matrix_Graph.h"
#include "List_Graph.h"

int main()
{
	//Matrix_Graph mg = Matrix_Graph();
	//mg.readFromFile();
	//mg.print();
	//mg.Prims_algorithm();

	List_Graph lg = List_Graph();
	lg.readFromFile();
	lg.print();
	lg.Prims_algorithm();

	std::cin.get();
	std::cin.get();
    return EXIT_SUCCESS;
}

