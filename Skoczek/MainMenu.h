#pragma once
#include "GameObject.h"
#include "Button.h"
#include <iostream>

class MainMenu
{
public:
	MainMenu(int windowWidth, int windowHeight); 
	~MainMenu();
	Button::ButtonTypes WhichButtonWasClicked(int xPos, int yPos);
	void Render() const;
private:
	GameObject *gameName;
	const char* gameNameTexture = "assets/Game_name.png";
	Button* start;
	Button* option;
	Button* quit;
};

