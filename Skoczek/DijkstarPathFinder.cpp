#include "DijkstarPathFinder.h"
#include "DijkstarPathFinder.h"


DijkstarPathFinder::DijkstarPathFinder() : start(nullptr), goal(nullptr)
{
}

DijkstarPathFinder::DijkstarPathFinder(Square* origin, Square* destination) : start(origin), goal(destination)
{
	start->setPriorityDijkstar(0);
}


DijkstarPathFinder::~DijkstarPathFinder()
{
}

void DijkstarPathFinder::SetStart(Square* start)
{
	this->start = start;
	start->setPriorityDijkstar(0);
}

void DijkstarPathFinder::SetGoal(Square* goal)
{
	this->goal = goal;
}

void DijkstarPathFinder::ClearStart()
{
	start = nullptr;
}

void DijkstarPathFinder::ClearGoal()
{
	goal = nullptr;
}

void DijkstarPathFinder::FillQuaue(Square* root)
{
	pq.push_back(root);
	root->setToVisited();
	std::vector<Square*> children = root->getChildren();
	for (auto i = children.begin(); i != children.end(); ++i)
		if (!(*i)->getVisited())
			FillQuaue(*i);
}

void DijkstarPathFinder::Sort()
{
	std::sort(pq.begin(), pq.end(), CompareVertices());
}

bool DijkstarPathFinder::FindPath(std::vector<Square*>& path)
{
	Square* currentVertice;
	Square* childVertice;
	int dist;
	FillQuaue(start);
	Sort();
	while (!pq.empty())
	{
		currentVertice = pq.back();
		pq.pop_back();
		currentVertice->setToNotVisited();
		if (currentVertice == goal)
		{
			ReconstructPath(currentVertice, path);
			return true;
		}
		for (const auto& children : currentVertice->getChildren())
		{
			childVertice = children;
			dist = currentVertice->getPriorityDijkstar() + Vertice::distance;
			if (childVertice->getVisited() && dist < childVertice->getPriorityDijkstar())
			{
				childVertice->setPriorityDijkstar(dist);
				childVertice->addParent(currentVertice);
			}
		}
		Sort();
	}
	return false;
}

void DijkstarPathFinder::ReconstructPath(Square* node, std::vector<Square*>& path)
{
	Square* parent = node->getParent();
	path.push_back(node);
	while (parent != nullptr)
	{
		path.push_back(parent);
		parent = parent->getParent();
	}
	std::reverse(path.begin(), path.end());
	ClearStart();
	ClearGoal();
	pq.clear();
}
