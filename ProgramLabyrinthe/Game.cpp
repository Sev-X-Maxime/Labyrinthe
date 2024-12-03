#include "Game.h"

void Game::InitStaticTiles()
{
	staticTiles[make_pair(0, 0)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(0, 2)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(0, 4)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(0, 6)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(2, 0)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(2, 2)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(2, 4)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(2, 6)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(4, 0)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(4, 2)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	staticTiles[make_pair(4, 4)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(4, 6)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) });

	staticTiles[make_pair(6, 0)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	staticTiles[make_pair(6, 2)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	staticTiles[make_pair(6, 4)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });

	staticTiles[make_pair(6, 6)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) });
}