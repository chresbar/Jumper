#include "Game.h"
#include "GameObject.h"

SDL_Renderer* Game::renderer = nullptr;

Game::~Game()
{
}

Game::Game(const char* title, int Xpos, int Ypos, int width, int height, bool fullscreen): resolution(width, height), board(nullptr), optionMenu(nullptr), colorMenu(nullptr), artificialIntelligence(nullptr), banner(nullptr), mainMenu(nullptr), mouseClickPosition(std::make_pair(0, 0))
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		if (fullscreen) //sprawdzenie, czy okno aplikacji ma byæ fullsceen, czy tylko w okienku 
			window = SDL_CreateWindow(title, Xpos, Ypos, resolution.first, resolution.second, SDL_WINDOW_FULLSCREEN);
		else
			window = SDL_CreateWindow(title, Xpos, Ypos, resolution.first, resolution.second, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
		isRunning = true;
	}
	else
		isRunning = false;
	titleScreen = new TitleScreen(resolution.first, resolution.second);
	//mainMenu = new MainMenu(resolution.first, resolution.second);
}



void Game::handleEvents()
{
	SDL_Event event; //obiekt z biblioteki SDL przechowuj¹cy input urzytkownika z okienka
	SDL_PollEvent(&event); //pobranie inputa z okna
	switch (event.type) //obs³u¿enie poszczególnych inputów u¿ytkownika 
	{
	case SDL_QUIT: //naciœniêcie krzy¿yka w górnym prawym rogu okna 
		isRunning = false; //zmiana zmiennej o tym, czy gra dzia³a na fa³sz
		break;
	case SDL_MOUSEBUTTONDOWN: //naciœniecie przycisku myszki przez gracza
		if (event.button.button == SDL_BUTTON_LEFT) //warunek sprawdzaj¹cy, czy u¿ytkownik u¿y³ lewego przycisku myszki 
		{
			mouseClickPosition = std::make_pair(event.motion.x, event.motion.y);
			//std::cout << event.motion.x << " "<< event.motion.y << std::endl;
		}
		break;
	case SDL_KEYDOWN:
		if (titleScreen != nullptr)
		{
			clearMousePosition();
			delete titleScreen;
			titleScreen = nullptr;
			mainMenu = new MainMenu(resolution.first, resolution.second);
		}
	default:
		break;
	}
}

void Game::update()
{
	if (mainMenu != nullptr)
		handleButtons();
	else if (colorMenu != nullptr)
		handleColorMenu();
	else if (optionMenu != nullptr)
		handleOptionMenu();
	else if (board != nullptr)
		handleBoard();
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	if (titleScreen != nullptr)
		titleScreen->Render();
	else if (mainMenu != nullptr)
		mainMenu->Render();
	else if (colorMenu != nullptr)
		colorMenu->Render();
	else if (optionMenu != nullptr)
		optionMenu->Render();
	else if (board != nullptr)
	{
		board->Render();
		if (banner != nullptr)
			banner->Render();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window); //zniszczenie okna
	SDL_DestroyRenderer(renderer); //zniszczenie renderera
	SDL_Quit(); //zamkniêcie podsystemów 
}

bool Game::running() const
{
	return isRunning;
}

void Game::handleButtons()
{
	switch (mainMenu->WhichButtonWasClicked(mouseClickPosition.first, mouseClickPosition.second))
	{
	case Button::ButtonTypes(0):
		delete mainMenu;
		mainMenu = nullptr;
		clearMousePosition();
		colorMenu = new ColorMenu(resolution.first, resolution.second);
		break;
	case Button::ButtonTypes(1):
		delete mainMenu;
		mainMenu = nullptr;
		clearMousePosition();
		optionMenu = new OptionMenu(resolution.first, resolution.second);
		break;
	case Button::ButtonTypes(2):
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::handleColorMenu()
{
	switch (colorMenu->WhichButtonWasClicked(mouseClickPosition.first, mouseClickPosition.second))
	{
	case Button::ButtonTypes(3):
		std::cout << "white" << std::endl;
		delete colorMenu;
		colorMenu = nullptr;
		playerColor = Pawn::PawnColor::White;
		clearMousePosition();
		isPlayerTurn = true;
		board = new Board(resolution.first, resolution.second, playerColor);
		artificialIntelligence = new ArtificialIntelligence(board, Pawn::ReverseColor(playerColor));
		break;
	case Button::ButtonTypes(4):
		std::cout << "black" << std::endl;
		delete colorMenu;
		colorMenu = nullptr;
		playerColor = Pawn::PawnColor::Black;
		clearMousePosition();
		isPlayerTurn = false;
		board = new Board(resolution.first, resolution.second, playerColor);
		artificialIntelligence = new ArtificialIntelligence(board, Pawn::ReverseColor(playerColor));
		break;
	default:
		break;
	}
}

void Game::handleOptionMenu()
{
	switch (optionMenu->WhichButtonWasClicked(mouseClickPosition.first, mouseClickPosition.second))
	{
	case Button::ButtonTypes(6):
		delete optionMenu;
		optionMenu = nullptr;
		clearMousePosition();
		mainMenu = new MainMenu(resolution.first, resolution.second);
		break;
	case Button::ButtonTypes(7):
		clearMousePosition();
		changeResolution(OptionMenu::resA.first, OptionMenu::resA.second);
		delete optionMenu;
		optionMenu = new OptionMenu(resolution.first, resolution.second);
		break;
	case Button::ButtonTypes(8):
		clearMousePosition();
		changeResolution(OptionMenu::resB.first, OptionMenu::resB.second);
		delete optionMenu;
		optionMenu = new OptionMenu(resolution.first, resolution.second);
		break;
	case Button::ButtonTypes(9):
		clearMousePosition();
		changeResolution(OptionMenu::resC.first, OptionMenu::resC.second);
		delete optionMenu;
		optionMenu = new OptionMenu(resolution.first, resolution.second);
		break;
	default:
		break;
	}
}

void Game::handleBoard()
{
	if (banner == nullptr)
	{
		if (isPlayerTurn)
		{
			Square* temp = board->getSquare(mouseClickPosition.first, mouseClickPosition.second);
			if (temp != nullptr)
				if (!temp->isFree() && temp->getPawn()->GetColor() == playerColor)
				{
					board->Clear();
					board->generateSelectAndSquaresAvaiableToMove(temp);
				}
				else if (board->isOneOfTheSquaresAvaiableToMove(temp))
				{
					board->movePawn(board->getSelect(), temp);
					board->Clear();
					clearMousePosition();
					if (board->checkIfPlayerHasWon())
					{
						banner = new Banner(Banner::BannerType::Win, resolution.first, resolution.second);
					}
					isPlayerTurn = false;
				}
		}
		else
		{
			SDL_Delay(500);
			artificialIntelligence->moveMenager();
			if (board->checkIfComputerHasWon())
			{
				banner = new Banner(Banner::BannerType::Lose, resolution.first, resolution.second);
			}
			isPlayerTurn = true;
		}
	}
	else
	{
		if (banner->wasBannerClicked(mouseClickPosition.first, mouseClickPosition.second))
		{
			delete board;
			board = nullptr;
			delete banner;
			banner = nullptr;
			mainMenu = new MainMenu(resolution.first, resolution.second);
			clearMousePosition();
		}
	}
	
}

void Game::clearMousePosition()
{
	mouseClickPosition = std::make_pair(0, 0);
}

void Game::changeResolution(int width, int height)
{
	resolution = std::make_pair(width, height);
	SDL_SetWindowSize(this->window, resolution.first, resolution.second);
	SDL_RenderSetLogicalSize(this->renderer, resolution.first, resolution.second);
}
