#include "Game.h"
#include "ExternDecl.h"
#include "Entity.h"
#include "LevelMaker.h"
#include "TileMap.h"
#include <iostream>
using namespace std;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

int stay_on_floor = 1;

// HORIZONTAL
float speedX = 2.0f;
float lt_accel = 0;
float rt_accel = 0;
float maxX = 20.5f;

// VERTICAL
float speedY = 0.0f;
float gravity = 2.2f;
float jumpStr = 14.2f;

// flags
int up = 0;
int collision = 1;

Entity* player = nullptr;
LevelMaker* level1 = nullptr;
SDL_Rect intersect{};
vector<Tile*> group_of_tiles{};

//Camera* cam = nullptr;

void Game::init(const char* title, int x, int y, int w, int h, int flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		// create window
		gWindow = SDL_CreateWindow(title, x, y, w, h, flags);

		if (gWindow != NULL) {

			// create renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, 0);

			isRunning = true;
		}
		else {
			isRunning = false;
		}
	}
	else {
		isRunning = false;
	}
	player = new Entity;
	player->loadTexture("assets/hobbit.png");

	level1 = new LevelMaker;
	level1->make_level(tile_map, "assets/floating.png", "assets/extensions/mudUp1.png", "assets/top_grass/top1.png", "assets/top_grass/top2.png", "assets/top_grass/top3.png", "assets/mid_grass/middle1.png", "assets/mid_grass/middle2.png", "assets/mid_grass/middle3.png", "assets/bot_grass/bottom1.png", "assets/bot_grass/bottom2.png", "assets/bot_grass/bottom3.png", "assets/extensions/grassUp1.png", "assets/extensions/mudDown1.png", "assets/extensions/grassUp2.png");

	//cam = new Camera;
}

void Game::handleEvent() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {

		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
}

void Game::update() {
	//cam->setPos(player->getRect()->x - (950 / 2), player->getRect()->y - (550 / 2));

	if (SDL_GetKeyboardState(0)[SDL_GetScancodeFromKey(SDLK_d)]) {
		rt_accel += 0.4;
		if (rt_accel >= maxX) { rt_accel = maxX; }
	}
	else {
		rt_accel = 0;
	}

	if (SDL_GetKeyboardState(0)[SDL_GetScancodeFromKey(SDLK_a)]) {
		lt_accel += 0.4;
		if (lt_accel <= -maxX) { lt_accel = -maxX; }
	}
	else {
		lt_accel = 0;
	}

	if (SDL_GetKeyboardState(0)[SDL_GetScancodeFromKey(SDLK_SPACE)]) {
		up = 1;
		gravity = 0;
	}
	else {
		up = 0;
	}

	for (int count = 0; count < group_of_tiles.size(); count++) {
		// check for collision btwn tiles and player's vertical detector
		if (SDL_IntersectRect(group_of_tiles[count]->getTile(), player->getVertical(), &intersect)) {

			if (intersect.y == group_of_tiles[count]->getTile()->y) {
				gravity = 0;
				collision = 0;
				speedY -= (intersect.h - stay_on_floor);
			}

			if (intersect.y > group_of_tiles[count]->getTile()->y + stay_on_floor) {
				gravity *= 0.5;
				up = 0; // stops player from going up any further so, pushing the player down is unnecessary.
			}
			break;
		}
	}

	for (int count = 0; count < group_of_tiles.size(); count++) {
		// check for collision btwn tiles and player's horizontal detector
		if (SDL_IntersectRect(group_of_tiles[count]->getTile(), player->getHorizontal(), &intersect)) {

			if (intersect.x == group_of_tiles[count]->getTile()->x) {
				rt_accel = 0;
				speedX -= (intersect.w / 2);
			}

			if (intersect.x > group_of_tiles[count]->getTile()->x) {
				lt_accel = 0;
				speedX += intersect.w;
			}
		}
		else {
			collision = 1;
		}
	}

	// Horizontal movement equation
	speedX += rt_accel - lt_accel;

	gravity++;

	// Vertical movement equation
	speedY += (collision * gravity) - (up * jumpStr);
}

void Game::render() {
	SDL_RenderClear(gRenderer);
	// ------------------------------------------

	player->drawTexture(350, 50);

	for (int count = 0; count < group_of_tiles.size(); count++) {
		group_of_tiles[count]->drawTile();
	}

	//cam->drawCam();

	// ------------------------------------------
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 1);
	SDL_RenderPresent(gRenderer);
}

void Game::clean() {
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
}