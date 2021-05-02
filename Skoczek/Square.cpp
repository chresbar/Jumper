#include "Square.h"

Square::Square(SquaerType type, int objectWidth, int objectHeight, int xPos, int yPos): GameObject(objectWidth, objectHeight, xPos, yPos), priority(0), Vertice(), pawn(nullptr), parent(nullptr)
{
	switch (type)
	{
	case Square::SquaerType::Yellow:
		this->SetTexture(yellowSquare);
		break;
	case Square::SquaerType::Brown:
		this->SetTexture(brownSquare);
		break;
	case Square::SquaerType::Green:
		this->SetTexture(greenSquare);
		break;
	case Square::SquaerType::Red:
		this->SetTexture(redSquare);
		break;
	default:
		break;
	}
}

Square::Square(SquaerType type, int objectWidth, int objectHeight, int xPos, int yPos, Pawn::PawnColor color) : Square(type, objectHeight, objectWidth, xPos, yPos)
{
	pawn = new Pawn(color, objectHeight, objectWidth, xPos, yPos);
}

void Square::setPriority(int priority)
{
	this->priority = priority;
}

void Square::lowerPriority()
{
	--priority;
}

int Square::getPriotity() const
{
	return priority;
}

Pawn* Square::getPawn() const
{
	return pawn;
}

void Square::setPawn(Pawn* pawn)
{
	this->pawn = pawn;
}

void Square::freeSquare()
{
	pawn = nullptr;
}

bool Square::isFree() const
{
	if (pawn == nullptr)
		return true;
	else
		return false;
}

bool Square::wasSquareClicked(int xPos, int yPos) const
{
	if (xPos >= Rec.x && xPos < Rec.x + Rec.w)
	{
		if (yPos >= Rec.y && yPos < Rec.y + Rec.h)
			return true;
		else
			return false;
	}
	else
		return false;
}

void Square::addParent(Square* parent)
{
	this->parent = parent;
}

Square* Square::getParent()
{
	return parent;
}

void Square::clearParent()
{
	this->parent = nullptr;
}

void Square::addChild(Square* child)
{
	this->children.push_back(child);
}

std::vector<Square*> Square::getChildren()
{
	return children;
}

void Square::clearChildren()
{
	this->children.clear();
}

void Square::render() const
{
	GameObject::Render();
	if (pawn != nullptr)
		pawn->Render();
}
