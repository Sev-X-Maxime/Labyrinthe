#include <iostream>
#include "Macro.h"
#include "Tile.h"

using namespace std;
using namespace Tools;


int main()
{
    Config();
	Tile _tile0 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
									  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	Tile _tile2 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	Tile _tile4 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	Tile _tile6 = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	Tile _tile8 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	Tile _tile10 = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	Tile _tile12 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	Tile _tile14 = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	Tile _tile16 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	Tile _tile18 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	Tile _tile20 = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	Tile _tile22 = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	Tile _tile24 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	Tile _tile26 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	Tile _tile28 = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	Tile _tile30 = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	cout << _tile0 << endl << endl;
	cout << _tile2 << endl << endl;
	cout << _tile4 << endl << endl;
	cout << _tile6 << endl << endl;
	cout << _tile8 << endl << endl;
	cout << _tile10 << endl << endl;
	cout << _tile12 << endl << endl;
	cout << _tile14 << endl << endl;
	cout << _tile16 << endl << endl;
	cout << _tile18 << endl << endl;
	cout << _tile20 << endl << endl;
	cout << _tile22 << endl << endl;
	cout << _tile24 << endl << endl;
	cout << _tile26 << endl << endl;
	cout << _tile28 << endl << endl;
	cout << _tile30 << endl << endl;
	return EXIT_SUCCESS;
}
