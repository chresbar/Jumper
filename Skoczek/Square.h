#pragma once
#include "GameObject.h"
#include "Vertice.h"
#include "Pawn.h"

class Square: public GameObject, public Vertice
{
public:
	enum class SquaerType {Yellow, Brown, Green, Red};
	Square(SquaerType type, int objectWidth, int objectHeight, int xPos, int yPos);
	Square(SquaerType type, int objectWidth, int objectHeight, int xPos, int yPos, Pawn::PawnColor color);
	void setPriority(int priority);
	void lowerPriority();
	int getPriotity() const;
	Pawn* getPawn() const;
	void setPawn(Pawn* pawn);
	void freeSquare();
	bool isFree() const;
	bool wasSquareClicked(int xPos, int yPos) const;
	void addParent(Square* parent);
	Square* getParent();
	void clearParent();
	void addChild(Square* child);
	std::vector<Square*> getChildren();
	void clearChildren();
	void render() const;
private:
	int priority;
	Pawn* pawn;
	Square* parent;
	std::vector<Square*> children;
	const char* yellowSquare = "assets/yellow.png";
	const char* brownSquare = "assets/brown.png";
	const char* greenSquare = "assets/AvaiableSquare.png";
	const char* redSquare = "assets/Select.png";
};

