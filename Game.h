#pragma once

#include <SDL.h>

class Game {
private:
	bool isRunning = false;

public:
	void init(const char*, int, int, int, int, int);
	void handleEvent();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
};

