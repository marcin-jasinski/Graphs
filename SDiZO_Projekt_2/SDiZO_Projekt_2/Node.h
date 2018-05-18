#pragma once

class Node
{
public:
	Node * next;

	int vertex;
	int weight;

	Node();
	Node(Node*, int, int);
	~Node();
};
