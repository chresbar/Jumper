#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <utility>
#include "MainMenu.h"
#include "ColorMenu.h"
#include "OptionMenu.h"
#include "Board.h"
#include "Pawn.h"
#include "ArtificialIntelligence.h"
#include "Banner.h"
#include "TitleScreen.h"

class Game
{
public:
	~Game();
	Game(const char* title, int Xpos, int Ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render() const;
	void clean();
	bool running() const;
	void handleButtons();
	void handleColorMenu();
	void handleOptionMenu();
	void handleBoard();
	void clearMousePosition();
	void changeResolution(int width, int height);
	static SDL_Renderer* renderer;
private:
	bool isRunning;
	bool isPlayerTurn;
	SDL_Window *window;
	std::pair<int, int> resolution; 
	MainMenu* mainMenu;
	std::pair<int, int> mouseClickPosition;
	ColorMenu* colorMenu;
	OptionMenu* optionMenu;
	Board* board;
	Pawn::PawnColor playerColor;
	ArtificialIntelligence* artificialIntelligence;
	Banner* banner;
	TitleScreen* titleScreen;
};

