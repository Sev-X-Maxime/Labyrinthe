#pragma once
#include "Grid.h"
#include "UnderMacro.h"

class Game
{
	vector<Player*> players;
	Grid grid;
	map<pair<u_int, u_int>, Tile> staticTiles;
	vector<Object> treasures;
	vector<Card> cards;
	map<string, vector<u_int>> options;
	map<string, u_int> currentOptions;
	
	Tile currentTile;
	u_int currentPlayerIndex;

public:
	Game();
	~Game();
private:
	void DeletePlayers();
	void InitPlayers();
	void DisplayPawn(const vector<Object>& _pawns, int _pawnsCount, int _selector, const vector<string>& _separator, map<u_int, bool> _isPawnIndexColorTaken);
	Object ChoosePawn(u_int _indexPlayer, map<u_int, bool>& _isPawnIndexColorTaken);
	void InitStaticTiles();
	void InitStaticTilesTreasure();
	void InitGrid(const u_int& _gridSize = 7);
	void InitTreasures();
	void InitCards();
	vector<vector<Card>> DistributeCards(const int _playerCount);
	void PlacePawnInSpawn();
	int ChooseAction(const vector<string>& _options);
	void DoAction(const u_int& _indexAction);
	pair<string, pair<u_int, u_int>> OptionAction(const vector<pair<string, vector<u_int>>>& _options,
		const bool _hasQuitOptions = true, const pair<u_int, u_int>& _selector = make_pair(0,0));
	void DoOptionAction(const pair<string, pair<u_int, u_int>>& _actionIndex);
	void Display();
	void Display(const vector<pair<string, vector<u_int>>>& _options,const u_int& _sizeOptions, const pair<u_int, u_int>& _selector, const bool _hasQuitOptions = true);
	pair<string, pair<u_int, u_int>> Selector(pair<u_int, u_int> _selector, const vector<pair<string, vector<u_int>>>& _options,const u_int& _sizeOptions, const bool _hasQuitOptions = true);
	void Option();
	void Start();
	bool IsOver();
	void PlacementTile();
public:
	void Launch();
};

