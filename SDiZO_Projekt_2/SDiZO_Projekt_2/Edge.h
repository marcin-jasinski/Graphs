#pragma once

class Edge
{
public:

	int startVertex, endVertex;
	int weight;

	Edge();
	Edge(int, int, int);
	~Edge();

	int getStartVertex();
	int getEndVertex();
	int getWeight();
};


