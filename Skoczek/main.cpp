#include <SDL.h>
#include "Game.h"

int main(int argc, char* argv[])
{
	const int FPS = 60; //iloœæ klatek na sekune gry
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Game* game = new Game("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running()) // pêtla gry
	{
		frameStart = SDL_GetTicks();

		game->handleEvents(); //funkcja przejmuj¹ca input od u¿ytkowanika, i zarz¹dzaj¹ca nimi 
		game->update(); // funcja aktualizuj¹ca pozycjê obiektów gry na posdtawie inputu od u¿ytkownika 
		game->render(); // Funcja renderuj¹ca obiekty gry na ekranie 


		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game->clean(); //czyszczenie i zamykanie ekranu z gr¹ 

	return 0;
}
