#pragma once

#include "Texture.h"

class CoinGame;

class GameObject
{
public:
	GameObject(CoinGame* game, Texture* sprite);
	~GameObject();

	int getX() { return x; }
	int getY() { return y; }

	void render(SDL_Renderer* renderer);
	virtual void update() = 0;
	bool checkCollision(int otherX, int otherY);

	bool getIsDead() { return isDead; }

protected:
	CoinGame* game;
	bool isDead;

private:
	Texture* sprite;
	int x, y;
};

