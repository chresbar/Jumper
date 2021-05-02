#pragma once
#include "GameObject.h"

class TitleScreen: public GameObject
{
public:
	TitleScreen(int width, int height);
private:
	const char* titleScreenTexture = "assets/Title_screen.png";
};

