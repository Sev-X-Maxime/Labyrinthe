#include <iostream>
#include "Macro.h"
#include "Game.h"

using namespace std;
using namespace Tools;


int main()
{
    //Config()
	SetConsoleOutputCP(CP_UTF8);

	while (true)
	{
		cout << "Key = " << _getch() << endl;
	}
	Game _game;
	_game.Launch();
	return EXIT_SUCCESS;
}
