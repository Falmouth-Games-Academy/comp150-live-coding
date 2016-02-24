#include "stdafx.h"
#include "CoinGame.h"
#include "InitialisationError.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SPRITE_SIZE = 64;
const int PLAYER_MOVEMENT_SPEED = 4;
const int NUM_COINS = 20;
const int NUM_SPIKES = 6;

CoinGame::CoinGame()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitialisationError("SDL_Init failed");
	}

	window = SDL_CreateWindow("COMP150 live coding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		throw InitialisationError("SDL_CreateWindow failed");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		throw InitialisationError("SDL_CreateRenderer failed");
	}

	playerSprite = new Texture(renderer, "Sprites\\hudPlayer_green.png");
	coinSprite = new Texture(renderer, "Sprites\\coinGold.png");
	spikeSprite = new Texture(renderer, "Sprites\\spikes.png");
}


CoinGame::~CoinGame()
{
	delete playerSprite;
	delete coinSprite;
	delete spikeSprite;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void CoinGame::run()
{
	bool running = true;
	int playerX = WINDOW_WIDTH / 2;
	int playerY = WINDOW_HEIGHT / 2;
	int coinsCollected = 0;

	// Initialise coins
	std::vector<int> coinX, coinY, spikeX, spikeY;
	for (int i = 0; i < NUM_COINS; i++)
	{
		int x = rand() % WINDOW_WIDTH;
		int y = rand() % WINDOW_HEIGHT;
		coinX.push_back(x);
		coinY.push_back(y);
	}
	for (int i = 0; i < NUM_SPIKES; i++)
	{
		int x = rand() % WINDOW_WIDTH;
		int y = rand() % WINDOW_HEIGHT;
		spikeX.push_back(x);
		spikeY.push_back(y);
	}

	while (running)
	{
		// Handle events
		SDL_Event ev;
		if (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			default:
				break;
			}
		}

		// Check keyboard state
		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
		if (keyboardState[SDL_SCANCODE_UP])
			playerY -= PLAYER_MOVEMENT_SPEED;
		if (keyboardState[SDL_SCANCODE_DOWN])
			playerY += PLAYER_MOVEMENT_SPEED;
		if (keyboardState[SDL_SCANCODE_LEFT])
			playerX -= PLAYER_MOVEMENT_SPEED;
		if (keyboardState[SDL_SCANCODE_RIGHT])
			playerX += PLAYER_MOVEMENT_SPEED;

		// Clear the screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Check and draw the spikes
		for (int i = 0; i < spikeX.size(); i++)
		{
			double distance = sqrt(pow(playerX - spikeX[i], 2) + pow(playerY - spikeY[i], 2));
			if (distance < SPRITE_SIZE / 2)
			{
				MessageBoxA(NULL, "You died :(", "Game over", MB_OK);
				running = false;
			}

			spikeSprite->render(renderer, spikeX[i], spikeY[i], SPRITE_SIZE, SPRITE_SIZE);
		}

		// Check and draw the coins
		for (int i = 0; i < coinX.size(); i++)
		{
			double distance = sqrt(pow(playerX - coinX[i], 2) + pow(playerY - coinY[i], 2));
			if (distance < SPRITE_SIZE / 2)
			{
				coinsCollected++;
				coinX.erase(coinX.begin() + i); // Erase the coin from the lists
				coinY.erase(coinY.begin() + i);
				i--;                            // Check the new i'th coin on the next iteration
				continue;                       // Skip to the next iteration
			}

			coinSprite->render(renderer, coinX[i], coinY[i], SPRITE_SIZE, SPRITE_SIZE);
		}

		// Check win
		if (coinsCollected >= NUM_COINS)
		{
			MessageBoxA(NULL, "You win :)", "Game over", MB_OK);
			running = false;
		}

		// Draw the player
		playerSprite->render(renderer, playerX, playerY, SPRITE_SIZE, SPRITE_SIZE);

		// Present the rendered display
		SDL_RenderPresent(renderer);
	}
}
