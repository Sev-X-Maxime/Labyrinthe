#include <iostream>
#include "Macro.h"
#include "Game.h"

using namespace std;
using namespace Tools;


int main()
{
    Config();
	Game _game;
	while (!_kbhit())
	{
		_game.Display();
	}

	return EXIT_SUCCESS;
}
