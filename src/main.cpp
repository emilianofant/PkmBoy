#include "Game.h"

Game *game = nullptr;

int main(int argc, const char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	// An unsigned 32-bit integer type. Always positive int numbers.
	Uint32 frameStart;
	int frameTime;

	// Create a new instance of Game.
	game = new Game();

	// @todo: make window resolution/size related to scaling 
	game->init("pkmBoy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 288, false, 2.0f);

	while(game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}