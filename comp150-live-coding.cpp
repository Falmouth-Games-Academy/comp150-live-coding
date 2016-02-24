// comp150-live-coding.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "comp150-live-coding.h"
#include "CoinGame.h"
#include "InitialisationError.h"

int main(int argc, char* args[])
{
	try
	{
		CoinGame game;
		game.run();
	}
	catch (InitialisationError &err)
	{
		MessageBoxA(NULL, err.what(), "Initialisation error", MB_OK | MB_ICONERROR);
		return 1;
	}

	return 0;
}
