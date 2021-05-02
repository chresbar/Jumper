#include "Board.h"
#include <iostream>

Board::Board(int windowWidth, int windowHeight, Pawn::PawnColor playerColor): playerColor(playerColor), elementWidth(windowHeight/9), buffor((windowWidth - windowHeight) / 2), select(nullptr)
{
	buffor += elementWidth;
	frame = new GameObject(frameTexture, elementWidth*9, elementWidth*9, buffor - elementWidth, 0);
	for (int i = 0; i < boardWidth; ++i)
		for (int j = 0; j < boardWidth; ++j)
			if (isEven(i + j))
			{
				if (j < rowsWithPawnsAtTheStart)
					board[i][j] = new Square(Square::SquaerType::Brown, elementWidth, elementWidth, buffor + (i * elementWidth), elementWidth + (j * elementWidth), Pawn::ReverseColor(playerColor));
				else if (j >= rowsWithPawnsAtTheStart && j < boardWidth - rowsWithPawnsAtTheStart)
					board[i][j] = new Square(Square::SquaerType::Brown, elementWidth, elementWidth, buffor + (i * elementWidth), elementWidth + (j * elementWidth));
				else if (j >= boardWidth - rowsWithPawnsAtTheStart)
					board[i][j] = new Square(Square::SquaerType::Brown, elementWidth, elementWidth, buffor + (i * elementWidth), elementWidth + (j * elementWidth), playerColor);
			}
			else
				board[i][j] = new Square(Square::SquaerType::Yellow, elementWidth, elementWidth, buffor + (i * elementWidth), elementWidth + (j * elementWidth));
}

std::pair<int, int> Board::getMoveDirectionCoordinates(MoveDirection direction)
{
	switch (direction) // wybranie w kótr¹ stronê siê bêdziemy ruszaæ 
	{
	case Board::MoveDirection::LeftUp:
		return std::make_pair(-1, -1);
		break;
	case Board::MoveDirection::RightUp:
		return std::make_pair(1, -1);
		break;
	case Board::MoveDirection::LeftDown:
		return std::make_pair(-1, 1);
		break;
	case Board::MoveDirection::RightDown:
		return std::make_pair(1, 1);
		break;
	}
}

int Board::squarePositionOnBoard(int windowPosition, bool flag) const
{
	if (flag)
	{
		for (int i = 0; i < boardWidth; ++i)//pêtla przechodz¹ca prze d³ugoœæ planszy w jednym wymiarze 
			if (windowPosition < buffor + (elementWidth * (i + 1)))//sprawdzenie w jakim przedziale znajduje siê wspó³rzêdna 
				return i; //zwrócenie wspó³rzêdnej
	}
	else
	{
		for (int i = 0; i < boardWidth; ++i)//pêtla przechodz¹ca prze d³ugoœæ planszy w jednym wymiarze 
			if (windowPosition < elementWidth + (elementWidth * (i + 1)))//sprawdzenie w jakim przedziale znajduje siê wspó³rzêdna 
				return i; //zwrócenie wspó³rzêdnej
	} 
}

void Board::generateSelectAndSquaresAvaiableToMove(Square* square)
{
	select = new Square(Square::SquaerType::Red, square->getWidth(), square->getHeight(), square->getXpos(), square->getYpos());
	generateSquaresAvaiableToMove(square);
}

void Board::generateSquaresAvaiableToMove(Square* square)
{
	for (int i = 0; i < moveDirectionNumber; ++i)
	{
		auto temp = getSquareInDirection(square, MoveDirection(i));
		if (temp != nullptr)
		{
			if (temp->isFree())
			{
				addAvaiableSquare(temp);
			}		
			else
			{
				temp = getSquareInDirection(temp, MoveDirection(i));
				if (temp != nullptr && temp->isFree() && !temp->getVisited())
				{
					addAvaiableSquare(temp);
					addJumpToAvaiableSquare(temp);
				}
			}
		}
	}
	clearVisited();
}

void Board::Clear()
{
	delete select;
	select = nullptr;
	squaresAvaiableToMove.clear();
	clearVisited();
}

void Board::movePawn(Square* origin, Square* destination)
{
	std::pair<int, int> destinationCoordinates = GetSquareCoordinates(destination);
	std::pair<int, int> originCoordinates = GetSquareCoordinates(origin);
	board[destinationCoordinates.first][destinationCoordinates.second]->setPawn(board[originCoordinates.first][originCoordinates.second]->getPawn());
	board[originCoordinates.first][originCoordinates.second]->freeSquare();
	destination->getPawn()->SetPosition(destination->getXpos(), destination->getYpos());
}

bool Board::IsInRange(int x) const
{
	if (x >= 0 && x < boardWidth)
		return true;
	else
		return false;
}

bool Board::isOneOfTheSquaresAvaiableToMove(Square* square) const
{                                                                                                                                                                         
	for (auto currentSquare : squaresAvaiableToMove)
		if (currentSquare->wasSquareClicked(square->getXpos(), square->getYpos()))
			return true;
	return false;
}

bool Board::checkIfPlayerHasWon()
{
	for (int i = 0; i < boardWidth; ++i)
		for (int j = 0; j < rowsWithPawnsAtTheStart; ++j)
			if (isEven(i + j) && (board[i][j]->isFree() || board[i][j]->getPawn()->GetColor() != playerColor))
				return false;
	return true;
}

bool Board::checkIfComputerHasWon()
{
	for (int i = 0; i < boardWidth; ++i)
		for (int j = boardWidth - rowsWithPawnsAtTheStart; j < boardWidth; ++j)
			if (isEven(i + j) && (board[i][j]->isFree() || board[i][j]->getPawn()->GetColor() == playerColor))
				return false;
	return true;
}

Square* Board::getSquare(int xPos, int yPos) const
{
	for (int i = 0; i < boardWidth; ++i)
		for (int j = 0; j < boardWidth; ++j)
			if (board[i][j]->wasSquareClicked(xPos, yPos))
				return board[i][j];
	return nullptr;
}

Square* Board::getSquareWithPawn(Pawn* pawn) const
{
	return at(squarePositionOnBoard(pawn->getXpos(), true), squarePositionOnBoard(pawn->getYpos(), false));
}

Square* Board::at(int x, int y) const
{
	if (IsInRange(x) && IsInRange(y))
		return board[x][y];
	else
		return nullptr;
}

std::pair<int, int> Board::GetSquareCoordinates(Square* square)
{
	return std::make_pair(squarePositionOnBoard(square->getXpos(), true), squarePositionOnBoard(square->getYpos(), false));
}

Square* Board::getSquareInDirection(Square* square, MoveDirection direction)
{
	std::pair<int, int> moveDirection = getMoveDirectionCoordinates(direction);
	std::pair<int, int> squareCoordinates = GetSquareCoordinates(square);
	if (IsInRange(moveDirection.first + squareCoordinates.first) && IsInRange(moveDirection.second + squareCoordinates.second))
		return board[moveDirection.first + squareCoordinates.first][moveDirection.second + squareCoordinates.second];
	else
		return nullptr;
}

Square* Board::getSelect() const
{
	return select;
}

Square* Board::getSquareOnTheRightOfTheSameColor(Square* square)
{
	std::pair<int, int> squareCoordinates = GetSquareCoordinates(square);
	if (IsInRange(squareCoordinates.first + 2) && IsInRange(squareCoordinates.second + 2))
		return board[squareCoordinates.first + 2][squareCoordinates.second + 2];
	else
		return nullptr;
}

Square* Board::getSquareOnTheLeftOfTheSameColor(Square* square)
{
	std::pair<int, int> squareCoordinates = GetSquareCoordinates(square);
	if (IsInRange(squareCoordinates.first - 2) && IsInRange(squareCoordinates.second - 2))
		return board[squareCoordinates.first - 2][squareCoordinates.second - 2];
	else
		return nullptr;
}

Board::MoveDirection Board::isSquareOnLeftOrRight(Square* origin, Square* destination)
{
	auto originCoordinates = GetSquareCoordinates(origin);
	auto destinationCoordinates = GetSquareCoordinates(destination);
	if (originCoordinates.first < destinationCoordinates.first)
		return Board::MoveDirection::LeftDown;
	else
		return Board::MoveDirection::RightDown;
}

void Board::Render() const
{
	frame->Render();
	for (int i = 0; i < boardWidth; ++i)
		for (int j = 0; j < boardWidth; ++j)
			board[i][j]->render();
	if (select != nullptr)
		select->render();
	for (auto currentSquare : squaresAvaiableToMove)
		currentSquare->render();
	
}

bool Board::areSquaresInTheSameRow(Square* origin, Square* destination)
{
	auto originCoordinates = GetSquareCoordinates(origin);
	auto destinationCoordinates = GetSquareCoordinates(destination);
	if (originCoordinates.second == destinationCoordinates.second)
		return true;
	else
		return false;
}

bool Board::isSquareUnder(Square* origin, Square* destination)
{
	auto originCoordinates = GetSquareCoordinates(origin);
	auto destinationCoordinates = GetSquareCoordinates(destination);
	if (originCoordinates.second < destinationCoordinates.second)
		return true;
	else
		return false;
}

bool Board::isEven(int number) const
{
	if(number%2==0)
		return true;
	else
		return false;
}

void Board::addAvaiableSquare(Square* square)
{
	squaresAvaiableToMove.push_back(new Square(Square::SquaerType::Green, elementWidth, elementWidth, square->getXpos(), square->getYpos()));
	square->setToVisited();
}

void Board::addJumpToAvaiableSquare(Square* square)
{
	Square* temp = nullptr;
	for (int i = 0; i < moveDirectionNumber; ++i)
	{
		temp = getSquareInDirection(square, MoveDirection(i));
		if (temp != nullptr && !temp->isFree())
		{
			temp = getSquareInDirection(temp, MoveDirection(i));
			if (temp != nullptr && temp->isFree() && !temp->getVisited())
			{
				addAvaiableSquare(temp);
				addJumpToAvaiableSquare(temp);
			}
		}
	}
}

void Board::clearVisited()
{
	for (int i = 0; i < boardWidth; ++i)
		for (int j = 0; j < boardWidth; ++j)
			if (isEven(i + j))
				board[i][j]->setToNotVisited();
}
