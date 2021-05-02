#include "DijkstraPathFinder.h"

DijkstraPathFinder::DijkstraPathFinder(Square* origin, Square* destination) : origin(origin), destination(destination)
{
	origin->setPriorityDijkstar(0);
}


DijkstraPathFinder::~DijkstraPathFinder()
{
	ClearStart();
	ClearGoal();
	pq.clear();
}

void DijkstraPathFinder::SetStart(Square* start)
{
	this->origin = start;
	start->setPriorityDijkstar(0);
}

void DijkstraPathFinder::SetGoal(Square* goal)
{
	this->destination = goal;
}

void DijkstraPathFinder::ClearStart()
{
	origin = nullptr;
}

void DijkstraPathFinder::ClearGoal()
{
	destination = nullptr;
}
//metoda do wype³niania kolejki piorytetowej
void DijkstraPathFinder::FillQuaue(Square* root)
{
	pq.push_back(root); // dodanie pola do kolejki
	root->setToVisited(); //ustawienie pola na odwiedzone
	for (auto currentChild: root->getChildren()) 
		if (!currentChild->getVisited()) //sprawdzenie, czy dziecko nie by³o ju¿ odwiedzone
			FillQuaue(currentChild); //wywo³anie metody rekurencyjnie na dziecku
}

void DijkstraPathFinder::Sort()
{
	std::sort(pq.begin(), pq.end(), CompareVertices());
}

bool DijkstraPathFinder::FindPath(std::vector<Square*>& path, Board* board)
{
	Square* currentVertice; // zmienna przechowuj¹ca pole zdjête z kolejki pioretytowej
	int dist; // zmianne przechowuj¹ca dystans elementu zdjêtego z kolejki + 1
	FillQuaue(origin); // wype³nienie kolejki polami 
	board->clearVisited();
	Sort(); //posortowanie kolejki
	while (!pq.empty()) // warunek sprawdzaj¹cy, czy kolejka jest pusta
	{
		currentVertice = pq.back(); // zdjêcie z kolejki elementu o najmniejszym piorytecie
		pq.pop_back(); 
		currentVertice->setToVisited(); //ustawienie pola na odwiedzone
		if (currentVertice == destination)
		{ // warunek sprawdzajæy, czy zdjêty element jest naszym szukanym polem
			ReconstructPath(currentVertice, path); // zrekonstruowanie œcie¿ki
			return true; // zwrócenie prawdy w przypadku znalezienia œcie¿ki
		}
		for (auto child : currentVertice->getChildren())
		{ // pêtla przechodz¹ca przez wszystkie dzieci zdjêtego elementu
			dist = currentVertice->getPriorityDijkstar() + Vertice::distance;
			if (!child->getVisited() && dist < child->getPriorityDijkstar())
			{//warunek sprawdzaj¹cy, czy dzieko by³o ju¿ odwiedzone i czy jego piorytet jest wiêkszy od piorytetu elementu
				child->setPriorityDijkstar(dist); // ustawienie piorystetu dziecka na piorytet elementu + 1
				child->addParent(currentVertice); // ustawienie rodzica dziecka na element
			}
		}
		Sort(); // posortowanie kolejki piorytetowej
	}
	return false; // zwrócenie fa³szu w przypadku nie znalezienia œcie¿ki
}

void DijkstraPathFinder::ReconstructPath(Square* node, std::vector<Square*>& path)
{ // funkcja przyjmuje w argumentach szukane pole oraz œcie¿kê 
	while(node->getParent() != nullptr) //sprawdzenie czy pole posida rodzica
	{
		path.push_back(node); //dodanie pola do œcie¿ki 
		node = node->getParent(); //ustawienie rodzica pola na aktualnie sprawdzane pole
	}
	std::reverse(path.begin(), path.end());
	//odwrócenie vectora ze œcie¿k¹ tak, zaczyna³ siê od pola z ktorego szukaliœmy œcie¿ki
}

/*void DijkstarPathFinder::ReconstructPath(Square* node, std::vector<Square*>& path)
{
Square* parent = node->getParent(); //wybranie rodzica przes³anego pola
	path.push_back(node); //dodanie pola do œcie¿ki
	while (parent != nullptr) //warunek sprawdzaj¹cy czy pola ma rodzica
	{
		path.push_back(parent); //dodanie rodzica do œcie¿ki
		parent = parent->getParent(); //ustawienie spr
	}
	std::reverse(path.begin(), path.end());
	ClearStart();
	ClearGoal();
	pq.clear();
}*/
