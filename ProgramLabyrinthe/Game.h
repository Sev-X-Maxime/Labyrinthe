#pragma once
#include "Grid.h"

class Game
{
	vector<Player> players;
	u_int playersCount;
	Grid* grid;
	map<pair<u_int, u_int>, Tile> staticTiles;
	vector<Object> treasures;
	vector<Card> cards;

public:
	Game();

	void InitPlayers(const u_int& _playersCount);
	void InitStaticTiles();
	void InitGrid();
	void InitTreasure();
	void InitCards();
	void DistributeCards();
};

