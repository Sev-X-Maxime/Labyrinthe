#include <iostream>
#include "Macro.h"
#include "Game.h"

using namespace std;
using namespace Tools;


int main()
{
    Config();
	Game _game;
	_game.Launch();
	return EXIT_SUCCESS;
}
