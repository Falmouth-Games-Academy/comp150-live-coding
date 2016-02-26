#include "stdafx.h"
#include "CoinGame.h"
#include "InitialisationError.h"

CoinGame::CoinGame()
	: playerSprite("Sprites\\hudPlayer_green.png"),
	coinSprite("Sprites\\coinGold.png"),
	spikeSprite("Sprites\\spikes.png")
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
}


CoinGame::~CoinGame()
{
	for (GameObject* ob : objects)
	{
		delete ob;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void CoinGame::killPlayer()
{
	MessageBoxA(NULL, "You died :(", "Game over", MB_OK);
	running = false;
}

void CoinGame::collectCoin()
{
	coinsCollected++;
}

void CoinGame::run()
{
	running = true;
	playerX = WINDOW_WIDTH / 2;
	playerY = WINDOW_HEIGHT / 2;
	coinsCollected = 0;

	// Initialise coins
	for (int i = 0; i < NUM_COINS; i++)
	{
		objects.push_back(new Coin(this));
	}
	for (int i = 0; i < NUM_SPIKES; i++)
	{
		objects.push_back(new Spike(this));
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

		// Update all objects
		for (GameObject* ob : objects)
		{
			ob->update();
		}

		// Check for dead objects
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->getIsDead())
			{
				objects.erase(objects.begin() + i);
				i--;
			}
		}

		// Check win
		if (coinsCollected >= NUM_COINS)
		{
			MessageBoxA(NULL, "You win :)", "Game over", MB_OK);
			running = false;
		}

		// Render all objects
		for (GameObject* ob : objects)
		{
			ob->render(renderer);
		}

		// Draw the player
		playerSprite.render(renderer, playerX, playerY, SPRITE_SIZE, SPRITE_SIZE);

		// Present the rendered display
		SDL_RenderPresent(renderer);
	}
}
