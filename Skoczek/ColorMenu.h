#pragma once
#include "GameObject.h"
#include "Button.h"

class ColorMenu
{
public:
	ColorMenu(int windowWidth, int windowHeight);
	void Render() const;
	Button::ButtonTypes WhichButtonWasClicked(int xPos, int yPos);
private:
	GameObject* chooseColor;
	const char* chooseColorTexture = "assets/color_choose.png";
	Button* white;
	Button* black;
};

