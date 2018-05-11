#pragma once

class Edge
{
public:
	int startVertex;
	int endVertex;
	int weight;

	Edge();
	Edge(int, int, int);
	~Edge();
};

