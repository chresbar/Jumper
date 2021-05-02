#include <SDL.h>
#include "Game.h"

int main(int argc, char* argv[])
{
	const int FPS = 60; //ilo�� klatek na sekune gry
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Game* game = new Game("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running()) // p�tla gry
	{
		frameStart = SDL_GetTicks();

		game->handleEvents(); //funkcja przejmuj�ca input od u�ytkowanika, i zarz�dzaj�ca nimi 
		game->update(); // funcja aktualizuj�ca pozycj� obiekt�w gry na posdtawie inputu od u�ytkownika 
		game->render(); // Funcja renderuj�ca obiekty gry na ekranie 


		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game->clean(); //czyszczenie i zamykanie ekranu z gr� 

	return 0;
}
