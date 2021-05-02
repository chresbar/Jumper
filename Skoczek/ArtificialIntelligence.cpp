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
//metoda szukaj¹ca d³ugoœci ruchu pionka w danym kierunku
std::pair<int, Square*> ArtificialIntelligence::findPawnJumpLength(Pawn* pawn, Board::MoveDirection direction)
{
	int jumpLenght = 0;
	Square* temp = board->getSquareInDirection(board->getSquareWithPawn(pawn), direction); //podpisanie do zmiennej pola w kierunku przekazanym do funkcji 
	if (temp != nullptr) // sprawdzenie, czy wczeœniejsza funkcja zwróci³a pole, czy wysz³a poza plansze 
	{
		if (temp->isFree()) // sprawdzenie, czy wybrane pole jest puste 
		{
			if (temp->getPriotity() != 0) // sprawdzenie czy pole ma 0 piorytet
			{
				board->clearVisited(); // wyczysczenie flagi odwiedzenia pól
				return std::make_pair(jumpLenght, temp); // zwrócenie d³ugoœci skoku oraz pola na którym l¹duje pionek po skoku
			}
		}
		else
		{
			temp = board->getSquareInDirection(temp, direction); //podpisanie kolejnego pola za wczeœniej wybranym polem w tym samym kierunku 
			if (temp != nullptr && temp->isFree()) //sprawdzenie, czy pole jest puste
			{
				++jumpLenght; //zwiêkszenie d³ugoœci skoku
				temp->setToVisited(); //ustawienie pola na odwiedzone
				return calculateJumpLength(temp, jumpLenght); //wywo³anie fukcji dalej szukaj¹cej kolejnych czêœci skoku
			}
		}
		
	}
	board->clearVisited(); //wyczyszczenie flag na odwiedzone pola
	return std::make_pair(-1, nullptr); //zwrócenie braku skoku 
}

Square* ArtificialIntelligence::findFreeWinningSquare()
{
	for (auto currentSquare: winningPositionsOnBoard)//pêtla przechodz¹ca, przez wygrywaj¹ce pola
		if (currentSquare->isFree()) //sprawdzenie, czy pole jest wolne
			return currentSquare; // zwrócenie pola
	return nullptr; // zwrócenie nullptr w przypadku braku wolnego pola
}
//metoda szukaj¹ca d³ugoœci ruchu dla wielokrotnego skoku
std::pair<int, Square*> ArtificialIntelligence::calculateJumpLength(Square* square, int jump)
{
	Square* currentSquare = nullptr;
	int priority = 0;
	for (int i = 0; i < Board::moveDirectionNumber; ++i) // pêtla przechodz¹ca przez wszystkie kierunki ruchu
	{
		currentSquare = board->getSquareInDirection(square, Board::MoveDirection(i)); //podpisanie pola w danym kierunku do zmiennej
		if (currentSquare != nullptr && !currentSquare->isFree()) //sprawdzenie, czy nie wychodzimy poza plansze i czy pole jest wolne
		{
			priority = currentSquare->getPriotity(); //przypisanie piorytetu z obecnego pola
			currentSquare = board->getSquareInDirection(currentSquare, Board::MoveDirection(i)); //podpisanie pola za naszym obecnym polem we wczeœniej wybranym kierunku
			if (currentSquare != nullptr && currentSquare->isFree() && !currentSquare->getVisited() && currentSquare->getPriotity() < priority)//sprawdznie, czy pole nie wychodzi³o poza plansze, by³o wolne, czy by³o ju¿ odwiedzone i czy ma ni¿szy piorytet od poprzedniego pola
			{
				++jump; //zwiêkszenie d³ugoœci ruchu
				currentSquare->setToVisited(); //ustawienie pola na odwiedzone 
				return calculateJumpLength(currentSquare, jump); //wywo³anie funkcji rekurencyjnie 
			}
		}
	}
	board->clearVisited(); //wyczyszczenie flag odwiedzenia pól
	return std::make_pair(jump, square); //zwórcenie d³ugoœci skoku oraz pola na którym wyl¹duje pionek po przejœciu przez wszystkie kiedynki 
}

bool ArtificialIntelligence::movePawnWithLongestJump()
{
	Pawn* pawnWithLongestJump = nullptr; //zmienna przechowuj¹ca pionek mog¹cy wykonaæ najd³uzszy skok
	std::pair<int, Square*> jump (0, nullptr); //zmienna pomocnicza przechowuj¹ca d³ugoœæ aktualnie sprawdzanego ruchu oraz pole na, którym pionek wyl¹duje 
	std::pair<int, Square*> longestJump (-1, nullptr); //zmienna przechowuj¹ca najd³u¿sz¹ d³ugoœæ ruchu oraz pole na którym wyl¹duje pionek
	for (auto currentPawn : pawns) // plêtla przechodz¹ca przez pionki gracza komputerowego
	{
		auto temp = board->getSquareWithPawn(currentPawn); //przypisanie pola na którym stoi wybrany pionek do zmiennej pomocniczej
		if (temp->getPriotity() != 0) //warunek sprawdzaj¹cy, czy pole nie ma 0 piorytetu (czy nie jest pozycj¹ wygrywaj¹c¹)
		{
			for (int j = 0; j < Board::moveDirectionNumber; j++) //pêtla przechodz¹ca przez wszystkie dostêpne kierunki ruchu 
			{
				jump = findPawnJumpLength(currentPawn, Board::MoveDirection(j)); // wywo³anie funkcji obliczaj¹cej d³ugoœæ skoku i przypisanie jej wyniku do zmiennej 
				if (jump.second != nullptr && jump.second->getPriotity()!=0 &&jump.first > longestJump.first) //warunek sprawdzaj¹cy, czy ruch wykonany w dan¹ stonê jest d³u¿szy od dotychczasowengo naj¿u¿szego ruchu
				{
					if (isOneOfTheWinnigSquares(jump.second) || (temp->getPriotity() > jump.second->getPriotity() && !board->areSquaresInTheSameRow(temp, jump.second)) || (temp->getPriotity() == jump.second->getPriotity() && board->isSquareUnder(temp, jump.second)))
					{ // warunek sprawdzaj¹cy, czy 
						longestJump = jump; //zapisanie najd³u¿szego ruchu (d³ugoœæ ruchu i pole na którym l¹duje pionek)
						pawnWithLongestJump = currentPawn; //zapisanie pionka mog¹cego wykonaæ najd³u¿szy ruch
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
	int shortestPathLength = INT_MAX; //zmienna przechwuj¹ca d³ugoœæ najkrótszej œcie¿ki
	Pawn* selectedPawn = nullptr; //zmienna przechowuj¹ca pionek zwalniaj¹cy miejsce
	std::vector<Square*> path; //zmiaenna przechowuj¹ca aktualnie obliczan¹ œcie¿kê 
	std::vector<Square*> shortestPath; //zmienna przechowuj¹ca najkrótsz¹ œcie¿kê 
	Square* destination = findFreeWinningSquare(); // zmienna przechowuj¹ca pole docelowe 
	Board::MoveDirection direction = board->isSquareOnLeftOrRight(board->getSquareWithPawn(pawn), destination); //zmienna przechuj¹ca kierunek w kótrym znajduje siê pole docelowe
	auto currentSquare = board->getSquareInDirection(board->getSquareWithPawn(pawn), direction); //zmienna przechowuj¹ca aktualnie sprawdzane pole
	while (currentSquare!=nullptr) // warunaek sprawdzaj¹cy, czy funkcja zwróci³a pole, czy nie
	{
		if (!currentSquare->isFree() && findPath(currentSquare, destination, path))
		{//warunek sprawdzaj¹cy, czy wybrane pole jest zajête oraz czy istanieje œcie¿ka od niego do pola docelowego
			if (path.size() < shortestPathLength)
			{//warunek sprawdzaj¹cy, czy wyliczona œcie¿ka jest którsza od dotychczasowej najkrótszej
				shortestPathLength = path.size(); //ustawienie d³ugoœci najkrótszej œcie¿ki
				selectedPawn = currentSquare->getPawn(); //ustawienie pionka, który ma zwolniæ miejsce 
				shortestPath = path; //ustawienie œcie¿ki jako najkrótsz¹ 
			}
		}
		path.clear(); //wyczyszczenie zmiennej przechowuj¹c¹ wygenerown¹ œcie¿kê 
		currentSquare = board->getSquareInDirection(currentSquare, direction);//wybranie kolejenego pola w ustalonym kierunku
	}
	if (selectedPawn != nullptr)
	{
		board->movePawn(board->getSquareWithPawn(selectedPawn), shortestPath[1]);//ruch pionkiem, który zwalnia pole dla wczeœniej zablkowoanego pionka
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


