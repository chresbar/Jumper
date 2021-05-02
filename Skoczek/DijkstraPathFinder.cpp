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
//metoda do wype�niania kolejki piorytetowej
void DijkstraPathFinder::FillQuaue(Square* root)
{
	pq.push_back(root); // dodanie pola do kolejki
	root->setToVisited(); //ustawienie pola na odwiedzone
	for (auto currentChild: root->getChildren()) 
		if (!currentChild->getVisited()) //sprawdzenie, czy dziecko nie by�o ju� odwiedzone
			FillQuaue(currentChild); //wywo�anie metody rekurencyjnie na dziecku
}

void DijkstraPathFinder::Sort()
{
	std::sort(pq.begin(), pq.end(), CompareVertices());
}

bool DijkstraPathFinder::FindPath(std::vector<Square*>& path, Board* board)
{
	Square* currentVertice; // zmienna przechowuj�ca pole zdj�te z kolejki pioretytowej
	int dist; // zmianne przechowuj�ca dystans elementu zdj�tego z kolejki + 1
	FillQuaue(origin); // wype�nienie kolejki polami 
	board->clearVisited();
	Sort(); //posortowanie kolejki
	while (!pq.empty()) // warunek sprawdzaj�cy, czy kolejka jest pusta
	{
		currentVertice = pq.back(); // zdj�cie z kolejki elementu o najmniejszym piorytecie
		pq.pop_back(); 
		currentVertice->setToVisited(); //ustawienie pola na odwiedzone
		if (currentVertice == destination)
		{ // warunek sprawdzaj�y, czy zdj�ty element jest naszym szukanym polem
			ReconstructPath(currentVertice, path); // zrekonstruowanie �cie�ki
			return true; // zwr�cenie prawdy w przypadku znalezienia �cie�ki
		}
		for (auto child : currentVertice->getChildren())
		{ // p�tla przechodz�ca przez wszystkie dzieci zdj�tego elementu
			dist = currentVertice->getPriorityDijkstar() + Vertice::distance;
			if (!child->getVisited() && dist < child->getPriorityDijkstar())
			{//warunek sprawdzaj�cy, czy dzieko by�o ju� odwiedzone i czy jego piorytet jest wi�kszy od piorytetu elementu
				child->setPriorityDijkstar(dist); // ustawienie piorystetu dziecka na piorytet elementu + 1
				child->addParent(currentVertice); // ustawienie rodzica dziecka na element
			}
		}
		Sort(); // posortowanie kolejki piorytetowej
	}
	return false; // zwr�cenie fa�szu w przypadku nie znalezienia �cie�ki
}

void DijkstraPathFinder::ReconstructPath(Square* node, std::vector<Square*>& path)
{ // funkcja przyjmuje w argumentach szukane pole oraz �cie�k� 
	while(node->getParent() != nullptr) //sprawdzenie czy pole posida rodzica
	{
		path.push_back(node); //dodanie pola do �cie�ki 
		node = node->getParent(); //ustawienie rodzica pola na aktualnie sprawdzane pole
	}
	std::reverse(path.begin(), path.end());
	//odwr�cenie vectora ze �cie�k� tak, zaczyna� si� od pola z ktorego szukali�my �cie�ki
}

/*void DijkstarPathFinder::ReconstructPath(Square* node, std::vector<Square*>& path)
{
Square* parent = node->getParent(); //wybranie rodzica przes�anego pola
	path.push_back(node); //dodanie pola do �cie�ki
	while (parent != nullptr) //warunek sprawdzaj�cy czy pola ma rodzica
	{
		path.push_back(parent); //dodanie rodzica do �cie�ki
		parent = parent->getParent(); //ustawienie spr
	}
	std::reverse(path.begin(), path.end());
	ClearStart();
	ClearGoal();
	pq.clear();
}*/
