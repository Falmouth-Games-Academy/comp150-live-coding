#include "stdafx.h"
#include "GameObject.h"
#include "CoinGame.h"

GameObject::GameObject(CoinGame* game, Texture* sprite)
	: game(game), sprite(sprite), isDead(false)
{
	x = rand() % CoinGame::WINDOW_WIDTH;
	y = rand() % CoinGame::WINDOW_HEIGHT;
}


GameObject::~GameObject()
{
}

void GameObject::render(SDL_Renderer* renderer)
{
	sprite->render(renderer, x, y, CoinGame::SPRITE_SIZE, CoinGame::SPRITE_SIZE);
}

bool GameObject::checkCollision(int otherX, int otherY)
{
	double distance = sqrt(pow(otherX - x, 2) + pow(otherY - y, 2));
	return (distance < CoinGame::SPRITE_SIZE / 2);
}
