#pragma once
#include "Grid.h"
#include "UnderMacro.h"

class Game
{
	vector<Player*> players;
	Grid grid;
	Tile currentTile;
	map<pair<u_int, u_int>, Tile> staticTiles;
	vector<Object> treasures;
	vector<Card> cards;

public:
	Game();
	~Game();
private:
	void DeletePlayers();
	void InitPlayers();
	void InitStaticTiles();
	void InitStaticTilesTreasure();
	void InitGrid(const u_int& _gridSize = 7);
	void InitTreasures();
	void InitCards();
	vector<vector<Card>> DistributeCards(const int _playerCount);
	int ChooseAction(vector<string> _options);
	void DoAction(u_int _indexAction);
	void Option();
	pair<u_int, u_int> OptionAction(vector<vector<string>> _options, vector<string> _texts);
	void DoOptionAction(pair<u_int, u_int> _actionIndex);
	void Start();
	bool IsOver();

public:
	void Display();
	void Display(vector<vector<string>> _options, vector<string> _texts, int _sizeOptions, pair<int, int> _selector);
	pair<int, int> Selector(pair<int, int> _selector, vector<string> _texts, vector<vector<string>> _options, int _sizeOptions);
	void Launch();
};

