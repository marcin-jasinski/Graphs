#pragma once
#include "Matrix_Graph.h"
#include "List_Graph.h"
#include <Windows.h>

class Benchmark_tests
{
private:
	Matrix_Graph mg;
	List_Graph lg;

	LARGE_INTEGER li;
	double PCFreq = double(li.QuadPart) / 1000000.0;
	__int64 CounterStart = 0;

public:
	Benchmark_tests();
	~Benchmark_tests();

	void StartCounter();
	double GetCounter();

	void runTests(int, double);
	void generateRandomGraph(int, double);
};

