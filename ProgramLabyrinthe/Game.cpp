#include "Game.h"

Game::Game()
{
	InitTreasures();
	InitStaticTiles();
	InitCards();
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

	staticTiles[make_pair(0, 0)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, false),
										  make_pair(MDT_UP, false) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(0, 2)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, false) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(0, 4)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, false) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(0, 6)] = Tile({ make_pair(MDT_RIGHT, false), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, false) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(2, 0)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, false),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(2, 2)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, false),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(2, 4)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, false) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(2, 6)] = Tile({ make_pair(MDT_RIGHT, false), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(4, 0)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, false),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(4, 2)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, false) }, true);

	staticTiles[make_pair(4, 4)] = Tile({ make_pair(MDT_RIGHT, false), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(4, 6)] = Tile({ make_pair(MDT_RIGHT, false), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, true) }, true);

	staticTiles[make_pair(6, 0)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, false),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, false) }, true);

	staticTiles[make_pair(6, 2)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, false) }, true);

	staticTiles[make_pair(6, 4)] = Tile({ make_pair(MDT_RIGHT, true), make_pair(MDT_LEFT, true),
										  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, false) }, true);

	staticTiles[make_pair(6, 6)] = Tile({ make_pair(MDT_RIGHT, false), make_pair(MDT_LEFT, true),
									  make_pair(MDT_UP, true) , make_pair(MDT_DOWN, false) }, true);

	InitStaticTilesTreasure();
}

void Game::InitStaticTilesTreasure()
{
	u_int _currentTreasureIndex = 0;
	for (pair<pair<u_int, u_int>, Tile> _currentTiles : staticTiles)
	{
		if (!(_currentTiles.first.first % 6 == 0 && _currentTiles.first.second % 6 == 0))
			staticTiles[_currentTiles.first].SetTreasure(treasures[_currentTreasureIndex++]);
	}
	staticTiles[make_pair(0, 0)].SetTreasure(Object('@', HIDDEN_TEXT BG_RED));
	staticTiles[make_pair(0, 6)].SetTreasure(Object('@', HIDDEN_TEXT BG_YELLOW));
	staticTiles[make_pair(6, 0)].SetTreasure(Object('@', HIDDEN_TEXT BG_GREEN));
	staticTiles[make_pair(6, 6)].SetTreasure(Object('@', HIDDEN_TEXT BG_BLUE));
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
	u_int _indexTreasure = 13;
	int _randomIndexX, _randomIndexY;
	const u_int& _treasuresCount = static_cast<u_int>(treasures.size());
	pair<u_int, u_int> _currentRandomCoordinates;
	while (_indexTreasure < _treasuresCount)
	{
		_randomIndexX = RandomInt(0, _gridSize - 1);
		_randomIndexY = RandomInt(0, _gridSize - 1);
		_currentRandomCoordinates = 
			make_pair(static_cast<u_int>(_randomIndexX), 
				static_cast<u_int>(_randomIndexY));
		if (grid.GetTile(_currentRandomCoordinates).GetTreasure() == ' ')
			grid.SetTileTreasure(_currentRandomCoordinates,
				treasures[_indexTreasure++]);
	}
}

void Game::InitTreasures()
{
	treasures = vector<Object>();
	treasures =
	{
		Object('A',RED),
		Object('B',RED),
		Object('C',RED),
		Object('D',RED),
		Object('E',RED),
		Object('F',RED),
		Object('G',RED),
		Object('H',RED),
		Object('I',RED),
		Object('J',RED),
		Object('K',RED),
		Object('L',RED),
		Object('M',RED),
		Object('N',RED),
		Object('O',RED),
		Object('P',RED),
		Object('Q',RED),
		Object('R',RED),
		Object('S',RED),
		Object('T',RED),
		Object('U',RED),
		Object('V',RED),
		Object('W',RED),
		Object('X',RED),
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

void Game::Launch()
{
	vector<string> _options = { "Play", "Option", "Leave" };
	u_int _actionIndex;
	do
	{
		_actionIndex = ChooseAction(_options);
		system("cls");
		DoAction(_actionIndex);
	} while (_actionIndex != 2);
}

int Game::ChooseAction(vector<string> _options)
{
	int _sizeOption = static_cast<int>(_options.size());
	int _key;
	int _selector = 0;
	while (true)
	{
		int _index = 0;
		for (; _index < _sizeOption; _index++)
		{
			if (_selector == _index)
			{
				cout << BOLD_TEXT << BLINK_TEXT << WHITE_INTENSE_TEXT << _options[_index] << RESET << endl;
				continue;
			}
			cout << WHITE_INTENSE_TEXT << _options[_index] << RESET << endl;
		}
		cout << endl;
		_key = _getch();
		if (_key == 72) // ↑
		{
			_selector = _selector > 0 ? _selector - 1 : _sizeOption - 1;
		}
		else if (_key == 80) // ↓
		{
			_selector = _selector < _sizeOption - 1 ? _selector + 1 : 0;
		}
		else if (_key == 13) // Enter
		{
			return _selector;
		}
		system("cls");
	}
}

void Game::DoAction(u_int _indexAction)
{
	switch (_indexAction)
	{
	case 0:
		InitPlayers();
		InitGrid();
		Display();
		system("cls");
		for (u_int _index = 0; _index < cards.size(); _index++)
		{
			cards[_index].Display();
			cout << endl << endl;
		}
		break;

	case 1:
		Option();
		break;

	case 2:
	default:
		break;
	}
}
void Game::Option()
{
	vector<vector<string>> _options = { {"2", "3", "4"} ,{"0", "1", "2", "3", "4"} };
	vector<string> _texts = { "Combien de joueur joue au jeu ?","Combien de bot souhaites-tu ?" };
	pair<u_int, u_int> _actionIndex;
	do
	{
		_actionIndex = OptionAction(_options, _texts);
		system("cls");
		DoOptionAction(_actionIndex);
	} while (true);
}
pair<u_int, u_int> Game::OptionAction(vector<vector<string>> _options, vector<string> _texts)
{
	int _sizeOptions = static_cast<int>(_options.size());
	pair<int, int> _selector = { 0,0 };
	Selector(_selector, _texts, _options, _sizeOptions);
	return _selector;
}
void Game::DoOptionAction(pair<u_int, u_int> _actionIndex)
{
}

void Game::Display()
{
	SetCursorPosition(0, 0, false);
	cout << grid << endl;
}

void Game::Display(vector<vector<string>> _options, vector<string> _texts, int _sizeOptions, pair<int, int> _selector)
{
	int _sizeCurrentOption;
	for (int _row = 0; _row < _sizeOptions; _row++)
	{
		cout << _texts[_row] << endl;
		_sizeCurrentOption = static_cast<u_int>(_options[_row].size());
		for (int _column = 0; _column < _sizeCurrentOption; _column++)
		{
			if (_selector.first == _row && _selector.second == _column)
			{
				cout << "[" << _options[_row][_column] << "] ";
				continue;
			}
			cout << " " << _options[_row][_column] << "  ";
		}
		cout << endl << endl;
	}
}

pair<int, int> Game::Selector(pair<int, int> _selector, vector<string> _texts, vector<vector<string>> _options, int _sizeOptions)
{
	while (true)
	{
		Display(_options, _texts, _sizeOptions, _selector);
		int _key = _getch();
		if (_key == 72) // ↑
		{
			_selector.first = _selector.first - 1 < 0 ? _sizeOptions - 1 : _selector.first - 1;
			if (_selector.second > static_cast<int>(_options[_selector.first].size() - 1)) _selector.first = _selector.first + 1;
		}
		else if (_key == 75) // gauche
		{
			_selector.second = _selector.second == 0 ? static_cast<int>(_options[_selector.first].size() - 1) : _selector.second - 1;
		}
		else if (_key == 77) // droite
		{
			_selector.second = _selector.second == static_cast<int>(_options[_selector.first].size() - 1) ? 0 : _selector.second + 1;
		}
		else if (_key == 80) // ↓
		{
			_selector.first = (_selector.first + 1) % _sizeOptions;
			// toto check if the next exists at the same column
			if (_selector.second > static_cast<int>(_options[_selector.first].size() - 1)) _selector.first = _selector.first + 1;
		}
		else if (_key == 13) // Enter
		{
			return _selector;
		}
		system("cls");
	}
}