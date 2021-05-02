#include "ArtificialIntelligence.h"
#include <iostream>

ArtificialIntelligence::ArtificialIntelligence(Board* board, Pawn::PawnColor color): board(board), computerColor(color)
{
	for (int i = 0; i < Board::boardWidth; i++)
	{
		for (int j = 0; j < Board::boardWidth; j++)
		{
			if ((i + j) % 2 == 0)
			{
				auto currentSquare = board->at(j, i);
				currentSquare->setPriority(Board::boardWidth - i);
				if (!currentSquare->isFree())
				{
					if(currentSquare->getPawn()->GetColor() == computerColor)
						pawns.push_back(currentSquare->getPawn());
					else
						winningPositionsOnBoard.push_back(currentSquare);
				}
			}
		}	
	}
}

bool ArtificialIntelligence::isSquareAroundEnemyPawns(Square* square)
{
	for (int i = Board::moveDirectionNumber / 2; i < Board::moveDirectionNumber; i++)
	{
		auto temp = board->at(board->getMoveDirectionCoordinates(Board::MoveDirection(i)).first, board->getMoveDirectionCoordinates(Board::MoveDirection(i)).second);
		if (temp!=nullptr && !temp->isFree() && temp->getPawn()->GetColor()!=computerColor)
			return false;
	}
	return true;
}
//metoda szukaj�ca d�ugo�ci ruchu pionka w danym kierunku
std::pair<int, Square*> ArtificialIntelligence::findPawnJumpLength(Pawn* pawn, Board::MoveDirection direction)
{
	int jumpLenght = 0;
	Square* temp = board->getSquareInDirection(board->getSquareWithPawn(pawn), direction); //podpisanie do zmiennej pola w kierunku przekazanym do funkcji 
	if (temp != nullptr) // sprawdzenie, czy wcze�niejsza funkcja zwr�ci�a pole, czy wysz�a poza plansze 
	{
		if (temp->isFree()) // sprawdzenie, czy wybrane pole jest puste 
		{
			if (temp->getPriotity() != 0) // sprawdzenie czy pole ma 0 piorytet
			{
				board->clearVisited(); // wyczysczenie flagi odwiedzenia p�l
				return std::make_pair(jumpLenght, temp); // zwr�cenie d�ugo�ci skoku oraz pola na kt�rym l�duje pionek po skoku
			}
		}
		else
		{
			temp = board->getSquareInDirection(temp, direction); //podpisanie kolejnego pola za wcze�niej wybranym polem w tym samym kierunku 
			if (temp != nullptr && temp->isFree()) //sprawdzenie, czy pole jest puste
			{
				++jumpLenght; //zwi�kszenie d�ugo�ci skoku
				temp->setToVisited(); //ustawienie pola na odwiedzone
				return calculateJumpLength(temp, jumpLenght); //wywo�anie fukcji dalej szukaj�cej kolejnych cz�ci skoku
			}
		}
		
	}
	board->clearVisited(); //wyczyszczenie flag na odwiedzone pola
	return std::make_pair(-1, nullptr); //zwr�cenie braku skoku 
}

Square* ArtificialIntelligence::findFreeWinningSquare()
{
	for (auto currentSquare: winningPositionsOnBoard)//p�tla przechodz�ca, przez wygrywaj�ce pola
		if (currentSquare->isFree()) //sprawdzenie, czy pole jest wolne
			return currentSquare; // zwr�cenie pola
	return nullptr; // zwr�cenie nullptr w przypadku braku wolnego pola
}
//metoda szukaj�ca d�ugo�ci ruchu dla wielokrotnego skoku
std::pair<int, Square*> ArtificialIntelligence::calculateJumpLength(Square* square, int jump)
{
	Square* currentSquare = nullptr;
	int priority = 0;
	for (int i = 0; i < Board::moveDirectionNumber; ++i) // p�tla przechodz�ca przez wszystkie kierunki ruchu
	{
		currentSquare = board->getSquareInDirection(square, Board::MoveDirection(i)); //podpisanie pola w danym kierunku do zmiennej
		if (currentSquare != nullptr && !currentSquare->isFree()) //sprawdzenie, czy nie wychodzimy poza plansze i czy pole jest wolne
		{
			priority = currentSquare->getPriotity(); //przypisanie piorytetu z obecnego pola
			currentSquare = board->getSquareInDirection(currentSquare, Board::MoveDirection(i)); //podpisanie pola za naszym obecnym polem we wcze�niej wybranym kierunku
			if (currentSquare != nullptr && currentSquare->isFree() && !currentSquare->getVisited() && currentSquare->getPriotity() < priority)//sprawdznie, czy pole nie wychodzi�o poza plansze, by�o wolne, czy by�o ju� odwiedzone i czy ma ni�szy piorytet od poprzedniego pola
			{
				++jump; //zwi�kszenie d�ugo�ci ruchu
				currentSquare->setToVisited(); //ustawienie pola na odwiedzone 
				return calculateJumpLength(currentSquare, jump); //wywo�anie funkcji rekurencyjnie 
			}
		}
	}
	board->clearVisited(); //wyczyszczenie flag odwiedzenia p�l
	return std::make_pair(jump, square); //zw�rcenie d�ugo�ci skoku oraz pola na kt�rym wyl�duje pionek po przej�ciu przez wszystkie kiedynki 
}

bool ArtificialIntelligence::movePawnWithLongestJump()
{
	Pawn* pawnWithLongestJump = nullptr; //zmienna przechowuj�ca pionek mog�cy wykona� najd�uzszy skok
	std::pair<int, Square*> jump (0, nullptr); //zmienna pomocnicza przechowuj�ca d�ugo�� aktualnie sprawdzanego ruchu oraz pole na, kt�rym pionek wyl�duje 
	std::pair<int, Square*> longestJump (-1, nullptr); //zmienna przechowuj�ca najd�u�sz� d�ugo�� ruchu oraz pole na kt�rym wyl�duje pionek
	for (auto currentPawn : pawns) // pl�tla przechodz�ca przez pionki gracza komputerowego
	{
		auto temp = board->getSquareWithPawn(currentPawn); //przypisanie pola na kt�rym stoi wybrany pionek do zmiennej pomocniczej
		if (temp->getPriotity() != 0) //warunek sprawdzaj�cy, czy pole nie ma 0 piorytetu (czy nie jest pozycj� wygrywaj�c�)
		{
			for (int j = 0; j < Board::moveDirectionNumber; j++) //p�tla przechodz�ca przez wszystkie dost�pne kierunki ruchu 
			{
				jump = findPawnJumpLength(currentPawn, Board::MoveDirection(j)); // wywo�anie funkcji obliczaj�cej d�ugo�� skoku i przypisanie jej wyniku do zmiennej 
				if (jump.second != nullptr && jump.second->getPriotity()!=0 &&jump.first > longestJump.first) //warunek sprawdzaj�cy, czy ruch wykonany w dan� ston� jest d�u�szy od dotychczasowengo naj�u�szego ruchu
				{
					if (isOneOfTheWinnigSquares(jump.second) || (temp->getPriotity() > jump.second->getPriotity() && !board->areSquaresInTheSameRow(temp, jump.second)) || (temp->getPriotity() == jump.second->getPriotity() && board->isSquareUnder(temp, jump.second)))
					{ // warunek sprawdzaj�cy, czy 
						longestJump = jump; //zapisanie najd�u�szego ruchu (d�ugo�� ruchu i pole na kt�rym l�duje pionek)
						pawnWithLongestJump = currentPawn; //zapisanie pionka mog�cego wykona� najd�u�szy ruch
					}
				}
			}
		}
	}
	if (longestJump.second != nullptr)
	{
		board->movePawn(board->getSquareWithPawn(pawnWithLongestJump), longestJump.second);
		updatePriorities();
		return true;
	}
	else
		return false;
}

bool ArtificialIntelligence::findPawnWithShortestPath()
{
	std::vector<Square*> path;
	Square* origin = nullptr;
	Square* destination = nullptr;
	for (auto currentPawn : pawns)
	{
		origin = board->getSquareWithPawn(currentPawn);
		if (!isOneOfTheWinnigSquares(origin))
		{
			GraphMaker::createGraph(origin, board);
			board->clearVisited();
			destination = findFreeWinningSquare();
			if (destination != nullptr)
				findPath(origin, destination, path);
			GraphMaker::clearGraph(board);
		}
	}
	if (!path.empty())
	{
		board->movePawn(origin, path[1]);
		updatePriorities();
	}
	else
		return false;
}

bool ArtificialIntelligence::unblockPawn(Pawn* pawn)
{
	int shortestPathLength = INT_MAX; //zmienna przechwuj�ca d�ugo�� najkr�tszej �cie�ki
	Pawn* selectedPawn = nullptr; //zmienna przechowuj�ca pionek zwalniaj�cy miejsce
	std::vector<Square*> path; //zmiaenna przechowuj�ca aktualnie obliczan� �cie�k� 
	std::vector<Square*> shortestPath; //zmienna przechowuj�ca najkr�tsz� �cie�k� 
	Square* destination = findFreeWinningSquare(); // zmienna przechowuj�ca pole docelowe 
	Board::MoveDirection direction = board->isSquareOnLeftOrRight(board->getSquareWithPawn(pawn), destination); //zmienna przechuj�ca kierunek w k�trym znajduje si� pole docelowe
	auto currentSquare = board->getSquareInDirection(board->getSquareWithPawn(pawn), direction); //zmienna przechowuj�ca aktualnie sprawdzane pole
	while (currentSquare!=nullptr) // warunaek sprawdzaj�cy, czy funkcja zwr�ci�a pole, czy nie
	{
		if (!currentSquare->isFree() && findPath(currentSquare, destination, path))
		{//warunek sprawdzaj�cy, czy wybrane pole jest zaj�te oraz czy istanieje �cie�ka od niego do pola docelowego
			if (path.size() < shortestPathLength)
			{//warunek sprawdzaj�cy, czy wyliczona �cie�ka jest kt�rsza od dotychczasowej najkr�tszej
				shortestPathLength = path.size(); //ustawienie d�ugo�ci najkr�tszej �cie�ki
				selectedPawn = currentSquare->getPawn(); //ustawienie pionka, kt�ry ma zwolni� miejsce 
				shortestPath = path; //ustawienie �cie�ki jako najkr�tsz� 
			}
		}
		path.clear(); //wyczyszczenie zmiennej przechowuj�c� wygenerown� �cie�k� 
		currentSquare = board->getSquareInDirection(currentSquare, direction);//wybranie kolejenego pola w ustalonym kierunku
	}
	if (selectedPawn != nullptr)
	{
		board->movePawn(board->getSquareWithPawn(selectedPawn), shortestPath[1]);//ruch pionkiem, kt�ry zwalnia pole dla wcze�niej zablkowoanego pionka
		updatePriorities();
		return true;
	}
	return false;
}

bool ArtificialIntelligence::findPath(Square* origin, Square* destination, std::vector<Square*>& path)
{
	DijkstraPathFinder pathFinder(origin, destination);
	return pathFinder.FindPath(path, board);
}

void ArtificialIntelligence::updatePriorities()
{
	PriorityMenager::checkWiningPositionsForSquares(winningPositionsOnBoard, board, computerColor);
	PriorityMenager::getRidOfSquaresWithoutRouteToWinningPositions(winningPositionsOnBoard, board);
	system("cls");
	for (int i = 0; i < Board::boardWidth; i++)
	{
		for (int j = 0; j < Board::boardWidth; j++)
		{
			std::cout << board->at(j, i)->getPriotity() << " ";
		}
		std::cout << std::endl;
	}
}

void ArtificialIntelligence::moveMenager()
{
	if (!movePawnWithLongestJump())
	{
		for (auto currentPawn : pawns)
		{
			if (!isOneOfTheWinnigSquares(board->getSquareWithPawn(currentPawn)))
			{
				if(board->GetSquareCoordinates(board->getSquareWithPawn(currentPawn)).second == Board::boardWidth - Board::rowsWithPawnsAtTheStart + 1)
					unblockPawn(currentPawn);
				else
					findPawnWithShortestPath();
			}
				
		}
	}
}

bool ArtificialIntelligence::isOneOfTheWinnigSquares(Square* square) const
{
	for (auto currentSquare : winningPositionsOnBoard)
		if (currentSquare == square)
			return true;
	return false;
}

bool ArtificialIntelligence::isInFirstWinningRow(Square* square) const
{
	for (auto i = 0; i < winningPositionsOnBoard.size()/2; i++)
		if (winningPositionsOnBoard[i] == square)
			return true;
	return false;
}

bool ArtificialIntelligence::isInSecondWinningRow(Square* square) const
{
	for (auto i = (winningPositionsOnBoard.size() / 2) - 1; i < winningPositionsOnBoard.size(); i++)
		if (winningPositionsOnBoard[i] == square)
			return true;
	return false;
}


