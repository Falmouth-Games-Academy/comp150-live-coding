#pragma once

class Coin
{
public:
	Coin();
	~Coin();

	int getX() { return x; }
	int getY() { return y; }

private:
	int x, y;
};

