#pragma once
#include "GameObject.h"

class Button: public GameObject
{
public:
	enum class ButtonTypes {Start, Option, Quit, White, Black, NoButton, Back, ResolutionA, ResolutionB, ResolutionC};
	Button(ButtonTypes buttonType, int objectWidth, int objectHeight, int xPos, int yPos);
	~Button();
	bool IsButtonClicked(int xPos, int yPos);
private:
	const char* startButton = "assets/start_button.png";
	const char* optionButton = "assets/option_button.png";
	const char* quitButton = "assets/quit_button.png";
	const char* whiteButton = "assets/choose_color_white.png";
	const char* blackButton = "assets/choose_color_black.png";
	const char* backButton = "assets/back_button.png";
	const char* resolutionA = "assets/1152x872.png";
	const char* resolutionB = "assets/1024x768.png";
	const char* resolutionC = "assets/800x600.png";
};

