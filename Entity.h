#pragma once

#include <SDL.h>

class Entity {
private:
	SDL_Texture* texture;
	SDL_Rect src, dest, vertical_detector, horizontal_detector;

public:
	void loadTexture(const char*);
	void drawTexture(int, int);
	SDL_Rect* getRect() { return &dest; }
	SDL_Rect* getVertical() { return &vertical_detector; }
	SDL_Rect* getHorizontal() { return &horizontal_detector; }
	~Entity() { SDL_DestroyTexture(texture); }
};

