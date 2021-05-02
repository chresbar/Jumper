#pragma once
#include "Board.h"
#include "PriorityMenager.h"
#include "GraphMaker.h"
#include "DijkstraPathFinder.h"

class ArtificialIntelligence
{
public:
	ArtificialIntelligence(Board* board, Pawn::PawnColor color);
	bool isSquareAroundEnemyPawns(Square* square);
	void moveMenager();
private:
	void updatePriorities();
	bool movePawnWithLongestJump();
	bool findPawnWithShortestPath();
	bool unblockPawn(Pawn* pawn);
	bool findPath(Square* start, Square* destination, std::vector<Square*>& path);
	std::pair<int, Square*> findPawnJumpLength(Pawn* pawn, Board::MoveDirection direction);
	Square* findFreeWinningSquare();
	bool isOneOfTheWinnigSquares(Square* square) const;
	bool isInFirstWinningRow(Square* square) const;
	bool isInSecondWinningRow(Square* square) const;
	std::pair<int, Square*> calculateJumpLength(Square* square, int jump);
	Board* board;
	std::vector<Pawn*> pawns;
	Pawn::PawnColor computerColor;
	std::vector<Square*> winningPositionsOnBoard;
};

