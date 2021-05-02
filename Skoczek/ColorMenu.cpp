#include "ColorMenu.h"

ColorMenu::ColorMenu(int windowWidth, int windowHeight)
{
	int elementWidth = windowWidth / 2;
	int elementHeight = elementWidth / 4;
	int elementPosX = windowWidth / 4;
	chooseColor = new GameObject(chooseColorTexture, elementWidth, elementHeight, elementPosX, elementHeight);
	white = new Button(Button::ButtonTypes::White, elementHeight, elementHeight, elementPosX, 3*elementHeight);
	elementPosX += elementWidth - elementHeight;
	black = new Button(Button::ButtonTypes::Black, elementHeight, elementHeight, elementPosX, 3 * elementHeight);
}

void ColorMenu::Render() const
{
	chooseColor->Render();
	white->Render();
	black->Render();
}

Button::ButtonTypes ColorMenu::WhichButtonWasClicked(int xPos, int yPos)
{
	if (white->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(3);
	else if (black->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(4);
	else
		return Button::ButtonTypes(5);
}
