#include "Pawn.h"

Pawn::Pawn(Pawn::PawnColor color, int objectWidth, int objectHeight, int xPos, int yPos) : GameObject(objectWidth, objectHeight, xPos, yPos), color(color)
{
	switch (color)
	{
	case Pawn::PawnColor::White:
		this->SetTexture(whiteColor);
		break;
	case Pawn::PawnColor::Black:
		this->SetTexture(blackColor);
		break;
	default:
		break;
	}
}

Pawn::PawnColor Pawn::GetColor() const
{
	return color;
}

Pawn::PawnColor Pawn::ReverseColor(Pawn::PawnColor color)
{
	if(color==PawnColor::White)
		return Pawn::PawnColor::Black;
	else
		return Pawn::PawnColor::White;
}
