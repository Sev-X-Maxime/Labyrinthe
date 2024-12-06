#pragma once
#include "Grid.h"
#include "UnderMacro.h"
#include "structPathFinding.h"
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <climits> 
#include <cmath> 
#include <random>
#define TAB "   "
#define RESET_SCREEN_LINE(_x) for (u_int _index = 0; _index < 100; _index++)\
{\
	SetCursorPosition(_index, _x, false);\
	cout << " ";\
}

class Game
{
	vector<Entity*> players;
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
	Object ChoosePawn(map<u_int, bool>& _isPawnIndexColorTaken);
	Object ChoosePawnComputer(map<u_int, bool>& _isPawnIndexColorTaken);
	void InitStaticTiles();
	void InitStaticTilesTreasure();
	void InitGrid(const u_int& _gridSize = 7);
	void InitTreasures();
	void InitCards();
	void PlacePawnInSpawn();
	vector<vector<Card>> DistributeCards(const int _playerCount);
	int ChooseAction(const vector<string>& _options);
	void DoAction(const u_int& _indexAction);
	pair<string, pair<u_int, u_int>> OptionAction(const vector<pair<string, vector<u_int>>>& _options,
		const bool _hasQuitOptions = true, const pair<u_int, u_int>& _selector = make_pair(0,0));
	void DoOptionAction(const pair<string, pair<u_int, u_int>>& _actionIndex);
	void Display();
	void Display(const vector<pair<string, vector<u_int>>>& _options,const u_int& _sizeOptions, const pair<u_int, u_int>& _selector, const bool _hasQuitOptions = true);
	void DisplayPawn(const vector<Object>& _pawns, int _pawnsCount, int _selector, const vector<string>& _separator, map<u_int, bool> _isPawnIndexColorTaken);
	pair<string, pair<u_int, u_int>> Selector(pair<u_int, u_int> _selector, const vector<pair<string, vector<u_int>>>& _options,const u_int& _sizeOptions, const bool _hasQuitOptions = true);
	void Option();
	void Play();
	bool IsOver();
	void PlacementTile();
	void PlacementTileComputer();
	void UpdateIfOnGoodCase();
	void MovementPlayer(Player* _currentPlayer);
	void MovementComputer(Computer* _currentPlayer);


	double Distance(const pair<int, int>& _p1, const pair<int, int>& _p2);
	void ShortestWay(const Grid& _grid, const Node& _goal, const Node& _start);
	void MoveToGoal(Grid _grid, Node* _goal);
public:
	void Launch();
};

