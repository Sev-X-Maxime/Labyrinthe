#include "Game.h"

Game::Game()
{
	InitTreasures();
	InitStaticTiles();
	InitCards();

	//deplacer dans le start
	InitPlayers();
	InitGrid();
}

Game::~Game()
{
	DeletePlayers();
}

void Game::DeletePlayers()
{
	const u_int& _playersCount = static_cast<u_int>(players.size());
	for (u_int _index = 0; _index < _playersCount; _index++)
	{
		delete players[_index];
	}
	players.clear();
	players = vector<Player*>();
}

void Game::InitPlayers()
{
	DeletePlayers();
	int _playerCount;
	do
	{
		_playerCount = GetInput<int>("Combien de joueur vont jouer aux jeux ?", "");
	} while (!(_playerCount >= 2 && _playerCount <= 4));
	const vector<vector<Card>>& _cardsPlayer = DistributeCards(_playerCount);
	string _currentPlayerName;
	const vector<Object>& _pawns =
	{
		Object('&', RED),
		Object('&', YELLOW),
		Object('&', BLUE),
		Object('&', GREEN)
	};
	for (int _index = 0; _index < _playerCount; _index++)
	{
		_currentPlayerName = 
			GetLine("Quel est le nom du  joueur  n°" + to_string(_index + 1) +"?");
		players.push_back(new Player(_currentPlayerName, _pawns[_index], _cardsPlayer[_index]));
		system("cls");
	}
}

void Game::InitStaticTiles()
{
	staticTiles = map<pair<u_int, u_int>, Tile>();

	staticTiles[make_pair(0, 0)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(0, 2)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(0, 4)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(0, 6)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(2, 0)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(2, 2)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(2, 4)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, false) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(2, 6)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(4, 0)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(4, 2)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) }, true);

	staticTiles[make_pair(4, 4)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(4, 6)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, true) }, true);

	staticTiles[make_pair(6, 0)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, false),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) }, true);

	staticTiles[make_pair(6, 2)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) }, true);

	staticTiles[make_pair(6, 4)] = Tile({ make_pair(DT_RIGHT, true), make_pair(DT_LEFT, true),
										  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) }, true);

	staticTiles[make_pair(6, 6)] = Tile({ make_pair(DT_RIGHT, false), make_pair(DT_LEFT, true),
									  make_pair(DT_UP, true) , make_pair(DT_DOWN, false) }, true);

	InitStaticTilesTreasure();
}

void Game::InitStaticTilesTreasure()
{
	u_int _currentTreasureIndex = 0;
	for (pair<pair<u_int, u_int>, Tile> _currentTiles : staticTiles)
	{
		if (!(_currentTiles.first.first % 6 && _currentTiles.first.second % 6))
		{
			_currentTiles.second.SetTreasure(_currentTreasureIndex++);
			continue;
		}
		staticTiles[make_pair(0, 0)].SetTreasure(Object('@', HIDDEN_TEXT BG_RED));
		staticTiles[make_pair(0, 6)].SetTreasure(Object('@', HIDDEN_TEXT BG_YELLOW));
		staticTiles[make_pair(6, 0)].SetTreasure(Object('@', HIDDEN_TEXT BG_GREEN));
		staticTiles[make_pair(6, 6)].SetTreasure(Object('@', HIDDEN_TEXT BG_BLUE));
	}
}

void Game::InitGrid(const u_int& _gridSize)
{
	grid = Grid(_gridSize);
	vector<vector<Tile>> _tiles = grid.GetTiles();
	Tile _currentTile;
	for (u_int _rowIndex = 0; _rowIndex < _gridSize; _rowIndex++)
	{
		for (u_int _columnIndex = 0; _columnIndex < _gridSize; _columnIndex++)
		{
			if (_rowIndex % 2 == 0 && _columnIndex % 2 == 0)
				_currentTile = staticTiles[make_pair(_rowIndex, _columnIndex)];
			else
				_currentTile = Tile();
			_tiles[_rowIndex].push_back(_currentTile);
		}
	}
	grid.SetTiles(_tiles);
}

void Game::InitTreasures()
{
	treasures = vector<Object>();
	treasures =
	{
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
		Object('#',RED),
	};
}

void Game::InitCards()
{
	for (const Object& _currentTreasure : treasures)
	{
		cards.emplace_back(Card(_currentTreasure));
	}
}

vector<vector<Card>> Game::DistributeCards(const int _playerCount)
{
	vector<Card> _cardsToDistrib = cards;
	vector<vector<Card>> _playersCards = vector<vector<Card>>();
	for (int _index = 0; _index < _playerCount; _index++)
	{
		_playersCards.push_back(vector<Card>());
	}
	const int _cardSize = static_cast<int>(_cardsToDistrib.size());
	int _randomIndex;
	for (int _index = _cardSize - 1; _index > 0 ; _index--)
	{
		_randomIndex = RandomInt(0, _index);
		_playersCards[_index % _playerCount].push_back(_cardsToDistrib[_randomIndex]);
		_cardsToDistrib.erase(_cardsToDistrib.begin() + _randomIndex);
	}
	return _playersCards;
}

void Game::Display()
{
	cout << grid << endl;
}
