#include <iostream>
#include "Macro.h"
#include "Game.h"

using namespace std;
using namespace Tools;


int main()
{
    Config();
	/*Game _game;
	_game.Launch();*/

	for (u_int _index = 0; _index < 20; ++_index)
	{
		if (_index == MDT_RIGHT)
		{
			cout << "trouver : " << _index << endl;
		}
	}
	return EXIT_SUCCESS;
}
