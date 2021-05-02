#pragma once
#include "GameObject.h"

class Pawn: public GameObject
{
public:
	enum class PawnColor {White, Black};
	Pawn(Pawn::PawnColor color, int objectWidth, int objectHeight, int xPos, int yPos);
	Pawn::PawnColor GetColor() const;
	static Pawn::PawnColor ReverseColor(Pawn::PawnColor color);
private:
	PawnColor color;
	const char* whiteColor = "assets/pawn_white.png";
	const char* blackColor = "assets/pawn_black.png";
};

