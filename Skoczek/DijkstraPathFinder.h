#pragma once
#include "Square.h"
#include "Board.h"
#include <algorithm>

struct CompareVertices
{
	bool operator() (const Square* n1, const Square* n2)
	{
		return n1->getPriorityDijkstar() > n2->getPriorityDijkstar();
	}
};

class DijkstraPathFinder
{
public:
	DijkstraPathFinder(Square* origin, Square* destination);
	~DijkstraPathFinder();
	void SetStart(Square* start);
	void SetGoal(Square* goal);
	void ClearStart();
	void ClearGoal();
	void FillQuaue(Square* root);
	void Sort();
	bool FindPath(std::vector<Square*>& path, Board* board);
	void ReconstructPath(Square* node, std::vector<Square*>& path);
private:
	Square* origin;
	Square* destination;
	std::vector<Square*> pq;
};

