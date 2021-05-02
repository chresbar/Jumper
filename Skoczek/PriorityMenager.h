#pragma once
#include <vector>
#include "Board.h"

class PriorityMenager
{
public:
	static void checkWiningPositionsForSquares(std::vector<Square*> winningPositionsOnBoard, Board* board, Pawn::PawnColor computerColor); //funkcja sprawdzaj¹ca ostatnie 2 wiersze na planszy i zmieniaj¹ca piorytety pól z pionkami komputera na 0
	static void getRidOfSquaresWithoutRouteToWinningPositions(std::vector<Square*> winningPositionsOnBoard, Board* board);
	static bool checkIfSquareInDirectionHaveZeroPriority(Square* square, Board::MoveDirection direction, Board* board);
	static bool checkIfSquaresUnderAreOfZeroPriority(Square* square, Board* board);
private:
	static void lowerPriorityOfNonoWiningPositions(Square* square, Board* board);
	static void getRidOfSquareWithoutRouteToWinningPosition(Square* square, Board* board);
};

