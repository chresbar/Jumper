#pragma once
#include "Game.h"

class TextureMenager //obiekt funkcyjny do �adowania obietku tekstury z biblioteki SDL
{
public:
	static SDL_Texture* LoadTexture(const char* filename);
};