#pragma once

#include "GameObject.h"

class Spike :
	public GameObject
{
public:
	Spike(CoinGame* game);
	~Spike();

	virtual void update();
};

