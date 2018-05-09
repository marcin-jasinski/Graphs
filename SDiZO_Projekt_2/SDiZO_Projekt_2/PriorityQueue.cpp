#include "stdafx.h"
#include "PriorityQueue.h"


PriorityQueue::PriorityQueue()
{
}


PriorityQueue::PriorityQueue(int size)
{
	edgeQueue = new Edge[size];
	heapPosition = 0;
}

PriorityQueue::~PriorityQueue()
{
	delete[] edgeQueue;
}

Edge PriorityQueue::getFirst()
{
	return edgeQueue[0];
}

void PriorityQueue::push(Edge edge)
{
	int i, parentIndex;

	i = heapPosition++;             // i ustawiamy na koniec kopca
	parentIndex = (i - 1) >> 1;     // Obliczamy pozycjê rodzica

	while (i && (edgeQueue[parentIndex].getWeight() > edge.getWeight()))
	{
		edgeQueue[i] = edgeQueue[parentIndex];
		i = j;
		j = (i - 1) >> 1;
	}

	edgeQueue[i] = edge;                    // KrawêdŸ e wstawiamy do kopca
}
