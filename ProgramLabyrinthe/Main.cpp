#include <iostream>
#include "Macro.h"
#include "Tile.h"

using namespace std;
using namespace Tools;


int main()
{
    Config();
    Tile _tile = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true) 
        , make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });
    while (!_kbhit())
    {
        system("cls");
        cout << _tile.ToString()<< endl;
           _tile.Rotate(RT_LEFT);
        sleep_for(1000ms);
    }


	return EXIT_SUCCESS;
}
