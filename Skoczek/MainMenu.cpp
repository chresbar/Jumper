#include "MainMenu.h"

MainMenu::MainMenu(int windowWidth, int windowHeight)
{
	int elementWidth = windowWidth / 2;
	int elemnstHeight = windowHeight / 6;
	int elementPosX = windowWidth / 4;
	int temp = elementPosX + (elementPosX / 4);
	int temp2 = 2 * elemnstHeight;
	gameName = new GameObject(gameNameTexture, elementWidth, elemnstHeight, elementPosX, elemnstHeight);
	elementWidth = windowWidth / 2.7;
	start = new Button(Button::ButtonTypes::Start, elementWidth , elemnstHeight, temp, temp2 + (elementPosX*0,1));
	temp2 += elemnstHeight;
	option = new Button(Button::ButtonTypes::Option, elementWidth, elemnstHeight, temp, temp2 + (elementPosX * 0, 3));
	temp2 += elemnstHeight;
	quit  = new Button(Button::ButtonTypes::Quit, elementWidth, elemnstHeight, temp, temp2 + (elementPosX * 0, 3));
}

MainMenu::~MainMenu()
{
}

Button::ButtonTypes MainMenu::WhichButtonWasClicked(int xPos, int yPos)
{
	if (start->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(0);
	else if (option->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(1);
	else if (quit->IsButtonClicked(xPos, yPos))
		return Button::ButtonTypes(2);
	else
		return Button::ButtonTypes(5);
}

void MainMenu::Render() const
{
	gameName->Render();
	start->Render();
	option->Render();
	quit->Render();
}
