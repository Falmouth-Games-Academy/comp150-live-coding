// comp150-live-coding.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "comp150-live-coding.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SPRITE_SIZE = 64;
const int PLAYER_MOVEMENT_SPEED = 4;
const int NUM_COINS = 20;
const int NUM_SPIKES = 6;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		MessageBoxA(NULL, SDL_GetError(), "SDL_Init failed", MB_OK | MB_ICONERROR);
	}
	else
	{
		SDL_Window* window = SDL_CreateWindow("COMP150 live coding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			MessageBoxA(NULL, SDL_GetError(), "SDL_CreateWindow failed", MB_OK | MB_ICONERROR);
		}
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

			if (renderer == nullptr)
			{
				MessageBoxA(NULL, SDL_GetError(), "SDL_CreateRenderer failed", MB_OK | MB_ICONERROR);
			}
			else
			{
				SDL_Texture* playerSprite = IMG_LoadTexture(renderer, "Sprites\\hudfrgfdgdgdfdg.png");
				SDL_Texture* coinSprite = IMG_LoadTexture(renderer, "Sprites\\coinGold.png");
				SDL_Texture* spikeSprite = IMG_LoadTexture(renderer, "Sprites\\spikes.png");

				if (playerSprite == nullptr || coinSprite == nullptr || spikeSprite == nullptr)
				{
					MessageBoxA(NULL, SDL_GetError(), "IMG_LoadTexture failed", MB_OK | MB_ICONERROR);
				}
				else
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

							SDL_Rect dest;
							dest.x = spikeX[i] - SPRITE_SIZE / 2;
							dest.y = spikeY[i] - SPRITE_SIZE / 2;
							dest.w = SPRITE_SIZE;
							dest.h = SPRITE_SIZE;
							SDL_RenderCopy(renderer, spikeSprite, nullptr, &dest);
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

							SDL_Rect dest;
							dest.x = coinX[i] - SPRITE_SIZE / 2;
							dest.y = coinY[i] - SPRITE_SIZE / 2;
							dest.w = SPRITE_SIZE;
							dest.h = SPRITE_SIZE;
							SDL_RenderCopy(renderer, coinSprite, nullptr, &dest);
						}

						// Check win
						if (coinsCollected >= NUM_COINS)
						{
							MessageBoxA(NULL, "You win :)", "Game over", MB_OK);
							running = false;
						}

						// Draw the player
						SDL_Rect dest;
						dest.x = playerX - SPRITE_SIZE / 2;
						dest.y = playerY - SPRITE_SIZE / 2;
						dest.w = SPRITE_SIZE;
						dest.h = SPRITE_SIZE;
						SDL_RenderCopy(renderer, playerSprite, nullptr, &dest);
						
						// Present the rendered display
						SDL_RenderPresent(renderer);
					}
				}

				SDL_DestroyTexture(playerSprite);
				SDL_DestroyTexture(coinSprite);
				SDL_DestroyTexture(spikeSprite);
			}

			SDL_DestroyRenderer(renderer);
		}

		SDL_DestroyWindow(window);
	}

	SDL_Quit();

	return 0;
}
