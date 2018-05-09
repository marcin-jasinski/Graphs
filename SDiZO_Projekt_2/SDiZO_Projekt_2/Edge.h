#pragma once

class Edge
{
private:
	int startVertex, endVertex;
	int weight;

public:
	Edge();
	Edge(int, int, int);
	~Edge();

	int getStartVertex();
	int getEndVertex();
	int getWeight();
};


