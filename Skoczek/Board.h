#pragma once
#include <vector>
#include <utility>
#include "Square.h"
#include "Pawn.h"

class Board
{
public:
	enum class MoveDirection {LeftUp, RightUp, LeftDown, RightDown};
	Board(int windowWidth, int windowHeight, Pawn::PawnColor playerColor);
	std::pair<int, int> getMoveDirectionCoordinates(MoveDirection direction);
	int squarePositionOnBoard(int windowPosition, bool flag) const;
	void generateSelectAndSquaresAvaiableToMove(Square* square);
	void generateSquaresAvaiableToMove(Square* square);
	void Clear();
	void movePawn(Square* origin, Square* destination);
	bool IsInRange(int x) const;
	bool isOneOfTheSquaresAvaiableToMove(Square* square) const;
	bool checkIfPlayerHasWon();
	bool checkIfComputerHasWon();
	bool areSquaresInTheSameRow(Square* origin, Square* destination);
	bool isSquareUnder(Square* origin, Square* destination);
	Square* getSquare(int xPos, int yPos) const;
	Square* getSquareWithPawn(Pawn* pawn) const;
	Square* at(int x, int y) const;
	std::pair<int, int> GetSquareCoordinates(Square* square);
	Square* getSquareInDirection(Square* square, MoveDirection direction);
	Square* getSelect() const;
	Square* getSquareOnTheRightOfTheSameColor(Square* square);
	Square* getSquareOnTheLeftOfTheSameColor(Square* square);
	MoveDirection isSquareOnLeftOrRight(Square* origin, Square* destination);
	void clearVisited();
	void Render() const;
	const static int boardWidth = 8;
	const static int moveDirectionNumber = 4;
	const static int rowsWithPawnsAtTheStart = 2;
private:
	bool isEven(int number) const;
	void addAvaiableSquare(Square* square);
	void addJumpToAvaiableSquare(Square* square);
	GameObject* frame;
	Pawn::PawnColor playerColor;
	Square* board[boardWidth][boardWidth];
	Square* select;
	std::vector<Square*> squaresAvaiableToMove;
	int buffor;
	int elementWidth;
	const char* frameTexture = "assets/frame.png";
};

