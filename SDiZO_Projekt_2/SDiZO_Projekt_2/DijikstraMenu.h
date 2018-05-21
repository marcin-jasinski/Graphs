#pragma once

#include "List_Graph.h"
#include "Matrix_Graph.h"

#include <iostream>

class DijikstraMenu
{
private:
	List_Graph lg;
	Matrix_Graph mg;

public:
	DijikstraMenu();
	~DijikstraMenu();

	void showDijikstraMenu();
	void generateRandomGraph(int, double);
};

