#pragma once

#include "Texture.h"

class CoinGame
{
public:
	CoinGame();
	~CoinGame();

	void run();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Texture* playerSprite;
	Texture* coinSprite;
	Texture* spikeSprite;
};

