#pragma once
#include "UserInteract.h"
#include "Grid.h"

using namespace UserInteraction;

class Game
{
	vector<Player*> players;
	Grid grid;
	map<pair<u_int, u_int>, Tile> staticTiles;
	vector<Object> treasures;
	vector<Card> cards;

public:
	Game();

private:
	void DeletePlayers();
	void InitPlayers();
	void InitStaticTiles();
	void InitStaticTilesTreasure();
	void InitGrid(const u_int& _gridSize = 7);
	void InitTreasures();
	void InitCards();
	vector<vector<Card>> DistributeCards(const int _playerCount);

public:
	void Display();
};

