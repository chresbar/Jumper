#include "PriorityMenager.h"

void PriorityMenager::checkWiningPositionsForSquares(std::vector<Square*> winningPositionsOnBoard, Board* board, Pawn::PawnColor computerColor)
{
	for (auto currentSquare : winningPositionsOnBoard) //p�tla przechodz�ca przez pola wygrywaj�ce 
	{
		if (!currentSquare->isFree() && currentSquare->getPriotity() != 0 && currentSquare->getPawn()->GetColor() == computerColor) // warunek sprawdzaj�cy, czy pole jest zaj�te i jaki pionek stoi na polu
		{
			currentSquare->setPriority(0); // zmiana piorytetu pola na 0
			for (int j = 0; j < Board::moveDirectionNumber; j++) // p�tla przechodz�ca przez kierunki ruchu w g�r� 
			{
				auto temp = board->getSquareInDirection(currentSquare, Board::MoveDirection(j)); //zapisanie pola w danym kierunku do zmienniej pomocniczej 
				if (temp != nullptr && temp->getPriotity() - currentSquare->getPriotity() > 1) // sprawdzenie, czy wcze�niej wykonana funkcja zwr�ci�a nam pole, czy nic oraz, czy r�nica piorytet�w jest wi�ksza ni� 1
					lowerPriorityOfNonoWiningPositions(temp, board); // obni�enie piorytetu dla pola powy�ej 
			}
		}
	}
}

void PriorityMenager::lowerPriorityOfNonoWiningPositions(Square* square, Board* board)
{
	square->lowerPriority(); // Obni�enie piorytetu o 1
	for (int i = 0; i < Board::moveDirectionNumber; i++) //funkcja przechodz�ca przez kierunki poruszania ku g�rze 
	{
		auto temp = board->getSquareInDirection(square, Board::MoveDirection(i)); // zmienna pomocnicza prechowuj�ca pole w danym kierunku
		if (temp != nullptr && temp->getPriotity() - square->getPriotity() > 1) // warunek sprawdzaj�cy, czy zmienna zawiera pola, czy nie oraz czy r�nica piorytet�w jest wi�ksza od 1
			lowerPriorityOfNonoWiningPositions(temp, board);
	}
}

void PriorityMenager::getRidOfSquareWithoutRouteToWinningPosition(Square* square, Board* board)
{
	if (checkIfSquaresUnderAreOfZeroPriority(square, board)) //warunek sprawdzaj�cy, czy pola pod maj� 0 piorytet 
	{
		square->setPriority(0); // ustawienie piorytetu na 0
		for (int k = 0; k < Board::moveDirectionNumber / 2; k++) //przej�cie przez kierunki ruchu w g�re 
		{
			auto temp = board->getSquareInDirection(square, Board::MoveDirection(k)); //podpisania pola w odpowiednim kierunku do zmiennej pomocniczej
			if (temp != nullptr) //sprawdzenie, czy pod zmienn� pomocnicz� znajduje si� pole, czy nic
				getRidOfSquareWithoutRouteToWinningPosition(temp, board); //wywo�anie funkcji rekurencyjnie dla kolejnego pola 
		}
	}
}

void PriorityMenager::getRidOfSquaresWithoutRouteToWinningPositions(std::vector<Square*> winningPositionsOnBoard, Board* board)
{
	for (int i = 0; i < winningPositionsOnBoard.size() / 2; i++) //funkcja przechodz�ca po polach w pierwszym wierszu p�l wygrywaj�cych 
		if (winningPositionsOnBoard[i]->getPriotity() == 0) // sprawdzenie, czy piorytet pola wynisi 0
		{
			if (i + 1 < winningPositionsOnBoard.size() / 2 && winningPositionsOnBoard[i + 1]->getPriotity() == 0) //sprawdenie, czy pole (takie po kt�rym mo�na si� porusza�) na prawo te� ma 0 piorytet
			{
				if (checkIfSquareInDirectionHaveZeroPriority(winningPositionsOnBoard[i], Board::MoveDirection::LeftDown, board) && checkIfSquareInDirectionHaveZeroPriority(winningPositionsOnBoard[i + 1], Board::MoveDirection::RightDown, board))
				{
					auto temp = board->getSquareInDirection(winningPositionsOnBoard[i], Board::MoveDirection::RightUp);
					if (temp != nullptr)
						getRidOfSquareWithoutRouteToWinningPosition(temp, board);
				}
			}
			else if (i + 1 == winningPositionsOnBoard.size() / 2)
			{
				if (checkIfSquareInDirectionHaveZeroPriority(winningPositionsOnBoard[i], Board::MoveDirection::LeftDown, board))
				{
					auto temp = board->getSquareInDirection(winningPositionsOnBoard[i], Board::MoveDirection::RightUp);
					if (temp != nullptr)
						getRidOfSquareWithoutRouteToWinningPosition(temp, board);
				}
			}
		}
}

bool PriorityMenager::checkIfSquareInDirectionHaveZeroPriority(Square* square, Board::MoveDirection direction, Board* board)
{
	auto temp = board->getSquareInDirection(square, direction);
	if (temp == nullptr || temp->getPriotity() == 0)
		return true;
	else
		return false;
}

bool PriorityMenager::checkIfSquaresUnderAreOfZeroPriority(Square* square, Board* board)
{
	for (int i = Board::moveDirectionNumber / 2; i < Board::moveDirectionNumber; i++)
	{
		auto temp = board->getSquareInDirection(square, Board::MoveDirection(i));
		if (temp != nullptr && temp->getPriotity() != 0)
			return false;
	}
	return true;
}
