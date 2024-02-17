#include "Game.h"
#include "ExternDecl.h"

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 550;

Game* game = nullptr;

const int FPS = 60;
int delta = 1000 / FPS;

int main(int num_args, char* argv[]) {
	int startLoop, frameTime;

	game = new Game();
	game->init("DINO DASH", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	while (game->running()) {
		startLoop = SDL_GetTicks();

		game->handleEvent();
		game->render();
		game->update();

		frameTime = SDL_GetTicks() - startLoop;

		if (frameTime < delta) {
			SDL_Delay(delta - frameTime);
		}
	}
	game->clean();
	return 0;
}