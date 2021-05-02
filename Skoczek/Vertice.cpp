#include "Vertice.h"

Vertice::Vertice(): visited(false), priorityDijkstar(infinity)
{
}

Vertice::~Vertice()
{
}

void Vertice::setToVisited()
{
	this->visited = true;
}


void Vertice::setToNotVisited()
{
	this->visited = false;
}

bool Vertice::getVisited() const
{
	return this->visited;
}

void Vertice::setPriorityDijkstar(int priority)
{
	this->priorityDijkstar = priority;
}

int Vertice::getPriorityDijkstar() const
{
	return priorityDijkstar;
}