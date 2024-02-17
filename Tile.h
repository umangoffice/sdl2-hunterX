#pragma once

#include <SDL.h>

class Tile {
private:
	SDL_Rect src, tile;
	SDL_Texture* texture;

public:
	Tile(int, int, const char*);
	void drawTile();
	SDL_Rect* getTile() { return &tile; }
};

