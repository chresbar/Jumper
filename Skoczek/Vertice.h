#pragma once
#include <vector>

class Vertice
{
public:
	Vertice();
	~Vertice();
	void setToVisited();
	void setToNotVisited();
	bool getVisited() const;
	int getPriorityDijkstar() const;
	void setPriorityDijkstar(int priority);
	static const int distance = 1;
	static const int infinity = INT_MAX;
protected:
	bool visited;
	int priorityDijkstar;
};

