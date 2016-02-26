#include "stdafx.h"
#include "Spike.h"
#include "CoinGame.h"

Spike::Spike(CoinGame* game)
	: GameObject(game, game->getSpikeSprite())
{
}


Spike::~Spike()
{
}

void Spike::update()
{
	if (checkCollision(game->getPlayerX(), game->getPlayerY()))
	{
		game->killPlayer();
	}
}
