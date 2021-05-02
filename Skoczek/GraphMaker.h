#pragma once
#include "Board.h"

class GraphMaker
{
public:
	static void createGraph(Square* root, Board* board);
	static void clearGraph(Board* board);
};

