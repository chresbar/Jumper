#pragma once
#include "Square.h"
#include <algorithm>

struct CompareVertices
{
	bool operator() (const Square* n1, const Square* n2)
	{
		return n1->getPriorityDijkstar() > n2->getPriorityDijkstar();
	}
};

class DijkstarPathFinder
{
public:
	DijkstarPathFinder();
	DijkstarPathFinder(Square* origin, Square* destination);
	~DijkstarPathFinder();
	void SetStart(Square* start);
	void SetGoal(Square* goal);
	void ClearStart();
	void ClearGoal();
	void FillQuaue(Square* root);
	void Sort();
	bool FindPath(std::vector<Square*>& path);
	void ReconstructPath(Square* node, std::vector<Square*>& path);
private:
	Square* start;
	Square* goal;
	std::vector<Square*> pq;
};

