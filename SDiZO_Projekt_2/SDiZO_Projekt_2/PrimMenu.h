#pragma once

#include "List_Graph.h"
#include "Matrix_Graph.h"

#include <iostream>
#include <fstream>
#include <string>

class PrimMenu
{
private:
	List_Graph lg;
	Matrix_Graph mg;

public:
	PrimMenu();
	~PrimMenu();

	void showPrimsMenu();
	void generateRandomGraph(int, int);
};

