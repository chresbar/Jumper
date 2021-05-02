#include "GraphMaker.h"

void GraphMaker::createGraph(Square* root, Board* board)
{
	root->setToVisited(); // ustawienia pola jako ju¿ odwiedzone
	for (int i = 0; i < Board::moveDirectionNumber; ++i) //pêtla przechodz¹ca przez wszyskie dostepne kierunki ruchu
	{
		auto currentSquare = board->getSquareInDirection(root, Board::MoveDirection(i)); //wybranie pola w ustalonym kierunku
		if (currentSquare != nullptr) //sprawdzenie, czy funkcja zwróci³¹ nam, pole, czy nie
		{
			if (currentSquare->isFree()) //sprawdzenie, czy wybrane pole jest puste
			{
				root->addChild(currentSquare); // dodanie pola jako dziecko elementu przekazanego do funkcji 
				if (!currentSquare->getVisited()) // warunek sprawdzaj¹cy, czy pole by³o ju¿ odwiedzone
					createGraph(currentSquare, board); // wywo³anie rekurencyjnie funkcji dla pola
			}
			else // sprawdzenie pola za pierwszym polem
			{
				currentSquare = board->getSquareInDirection(currentSquare, Board::MoveDirection(i)); // wybranie kolejnego pola w tym samym kierunku 
				if (currentSquare != nullptr && currentSquare->isFree()) 
				{ // warunke sprawdzaj¹cy, czy funkcja zwóci³a nam pole, czy nie oraz, czy zwrócceone pole jest wolne
					root->addChild(currentSquare); // dodanie pola jako dziecko elementu przekazanego do funkcji 
					if (!currentSquare->getVisited()) // sprawdzenie, czy wybrane pole by³o ju¿ odwiezone 
						createGraph(currentSquare, board); // wywo³anie rekurencyjnie funkcji dla pola
				}
			}
		}
	}
}

void GraphMaker::clearGraph(Board* board)
{
	for (int i = 0; i < Board::boardWidth; ++i)
		for (int j = 0; j < Board::boardWidth; ++j)
			if ((i + j) % 2 == 0)
			{
				board->at(i, j)->clearChildren();
				board->at(i, j)->clearParent();
				board->at(i, j)->setPriorityDijkstar(Vertice::infinity);
			}
	board->clearVisited();
}