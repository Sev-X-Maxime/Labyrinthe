#include <iostream>
#include "Macro.h"
#include "Game.h"

using namespace std;
using namespace Tools;


int main()
{
    Config();
	Game _game;
	_game.Launch();/*
	int _key;
	do
	{
		_key = _getch();
		system("cls");
		cout << "Key :" << _key << endl;
	}while (_key != 13);*/
	return EXIT_SUCCESS;
}
