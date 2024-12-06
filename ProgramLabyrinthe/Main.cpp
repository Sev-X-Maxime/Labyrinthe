#include <iostream>
#include "Macro.h"
#include "Game.h"

using namespace std;
using namespace Tools;


int main()
{
    Config();
	//SetConsoleOutputCP(CP_UTF8);
	Game _game;
	_game.Launch();
	/*string _utf8 = "\xF0\x9F\x94\x89";
	cout << _utf8 << endl;*/
	return EXIT_SUCCESS;
}
