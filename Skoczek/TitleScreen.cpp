#include "TitleScreen.h"

TitleScreen::TitleScreen(int width, int height): GameObject(width, height, 0, 0)
{
	this->SetTexture(titleScreenTexture);
}
