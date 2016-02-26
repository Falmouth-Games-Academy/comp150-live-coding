#include "stdafx.h"
#include "Coin.h"
#include "CoinGame.h"

Coin::Coin(CoinGame* game)
	: GameObject(game, game->getCoinSprite())
{
}


Coin::~Coin()
{
}

void Coin::update()
{
	if (checkCollision(game->getPlayerX(), game->getPlayerY()))
	{
		game->collectCoin();
		isDead = true;
	}
}
