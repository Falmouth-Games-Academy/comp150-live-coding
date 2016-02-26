#pragma once

#include "Texture.h"
#include "Coin.h"
#include "Spike.h"

class CoinGame
{
public:
	CoinGame();
	~CoinGame();

	void run();

	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 600;
	static const int SPRITE_SIZE = 64;
	static const int PLAYER_MOVEMENT_SPEED = 4;
	static const int NUM_COINS = 20;
	static const int NUM_SPIKES = 6;

	Texture* getCoinSprite() { return &coinSprite; }
	Texture* getSpikeSprite() { return &spikeSprite; }

	int getPlayerX() { return playerX; }
	int getPlayerY() { return playerY; }

	void killPlayer();
	void collectCoin();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Texture playerSprite;
	Texture coinSprite;
	Texture spikeSprite;

	std::vector<GameObject*> objects;
	int playerX, playerY;
	bool running;
	int coinsCollected;
};

