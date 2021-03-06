// SDiZO_Projekt_2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Menu.h"
#include "Matrix_Graph.h"
#include "List_Graph.h"
#include "Benchmark_tests.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

int main()
{	
	//Menu menu = Menu();

	// Following code was runned only once to perfom benchmark tests

	Benchmark_tests tests = Benchmark_tests();

	tests.runTests(50, 0.25);
	tests.runTests(50, 0.50);
	tests.runTests(50, 0.75);
	tests.runTests(50, 0.99);

	tests.runTests(75, 0.25);
	tests.runTests(75, 0.50);
	tests.runTests(75, 0.75);
	tests.runTests(75, 0.99);

	tests.runTests(100, 0.25);
	tests.runTests(100, 0.50);
	tests.runTests(100, 0.75);
	tests.runTests(100, 0.99);

	tests.runTests(125, 0.25);
	tests.runTests(125, 0.50);
	tests.runTests(125, 0.75);
	tests.runTests(125, 0.99);

	tests.runTests(150, 0.25);
	tests.runTests(150, 0.50);
	tests.runTests(150, 0.75);
	tests.runTests(150, 0.99);
	
	std::cin.get();
	std::cin.get();
    return EXIT_SUCCESS;
}

