#include "Game.h"

Game::Game()
{
	InitTreasures();
	InitStaticTiles();
	InitCards();
	options["Nombre d'IA"] = { 0,1,2,3,4 };
	options["Nombre de joueurs"] = { 2,3,4 };
	currentOptions["Nombre d'IA"] = 0;
	currentOptions["Nombre de joueurs"] = 0;
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
	map<u_int, bool> _isPawnIndexColorTaken;
	for (u_int _index = 0; _index < 4; _index++)
	{
		_isPawnIndexColorTaken[_index] = false;
	}
	DeletePlayers();
	const int _playerCount = options["Nombre de joueurs"][currentOptions["Nombre de joueurs"]];
	const vector<vector<Card>>& _cardsPlayer = DistributeCards(_playerCount);
	string _currentPlayerName;
	for (int _index = 0; _index < _playerCount; _index++)
	{
		_currentPlayerName =
			GetLine("Quel est le nom du joueur n°" + to_string(_index + 1) + "?");
		players.push_back(new Player(_currentPlayerName, ChoosePawn(_isPawnIndexColorTaken), _cardsPlayer[_index]));
		system("cls");
	}
}

Object Game::ChoosePawn(map<u_int, bool>& _isPawnIndexColorTaken)
{
	const vector<Object>& _pawns =
	{
		Object('&', RED),
		Object('&', YELLOW),
		Object('&', BLUE),
		Object('&', GREEN)
	};
	int _pawnsCount = static_cast<int>(_pawns.size());
	int _key;
	int _selector = 0;
	const vector<string>& _separator = { BLINK_TEXT, RESET };
	while (true)
	{
		SetCursorPosition(0, 2, false);
		cout << "Choisi ton pion : ";
		DisplayPawn(_pawns, _pawnsCount, _selector, _separator, _isPawnIndexColorTaken);
		_key = _getch();
		if (_key == 75 || _key == 113 || _key == 81)
		{
			_selector = _selector > 0 ? _selector - 1 : _pawnsCount - 1;
			PlaySound(TEXT("Sounds/TransitionMenu.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (_key == 77 || _key == 100 || _key == 68)
		{
			_selector = _selector < _pawnsCount - 1 ? _selector + 1 : 0;
			PlaySound(TEXT("Sounds/TransitionMenu.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (_key == 13)
		{
			PlaySound(TEXT("Sounds/Clic.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (!_isPawnIndexColorTaken[_selector])
			{
				_isPawnIndexColorTaken[_selector] = true;
				return _pawns[_selector];
			}
			else
			{
				SetCursorPosition(0, 5, false);
				cout << RED << "Ce pion est déjà pris !" << RESET;
				continue;
			}
		}
		RESET_SCREEN_LINE(5)
		/*system("cls");*/
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
	grid = Grid();
	vector<vector<Tile>> _tiles = vector<vector<Tile>>();
	Tile _currentTile;
	for (u_int _rowIndex = 0; _rowIndex < _gridSize; _rowIndex++)
	{
		_tiles.push_back(vector<Tile>());
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
	u_int _indexTreasure = 12;
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
		Object('S',LIME),
		Object('B',PINK),
		Object('M',PURPLE_BASE),
		Object('T',YELLOW_INTENSE_TEXT),
		Object('Z',MAGENTA_INTENSE_TEXT),
		Object('R',BLACK_INTENSE_TEXT),
		Object('I',LIGHT_BLUE),
		Object('P',ORANGE),
		Object('~',BLUE_INTENSE_TEXT),
		Object('?',GREEN),
		Object('%',CYAN),
		Object('+',LIME),
		Object('(',LIGHT_BLUE),
		Object('à',CYAN_BASE),
		Object('0',GREEN_INTENSE_TEXT),
		Object('6',CYAN_INTENSE_TEXT),
		Object('9',DARK_ORANGE),
		Object('µ',DARK_YELLOW),
		Object('$',MAGENTA),
		Object(']',CYAN),
		Object('c',PINK),
		Object('b',PURPLE_BASE),
		Object('d',BLUE_INTENSE_TEXT),
		Object('r',MAGENTA_INTENSE_TEXT),
	};
}

void Game::InitCards()
{
	for (const Object& _currentTreasure : treasures)
	{
		cards.emplace_back(Card(_currentTreasure));
	}
}

void Game::PlacePawnInSpawn()
{
	const u_int& _playersCount = static_cast<u_int>(players.size());
	Tile _currentTile;
	pair<u_int, u_int> _currentCoordinates;
	Player* _currentPlayer;
	for (u_int _row = 0; _row < 7; _row++)
	{
		for (u_int _column = 0; _column < 7; _column++)
		{
			_currentCoordinates = make_pair(_row, _column);
			_currentTile = grid.GetTile(_currentCoordinates);
			if (_currentTile.GetTreasure().appearance == '@')
			{
				for (u_int _index = 0; _index < _playersCount; _index++)
				{
					_currentPlayer = players[_index];
					if((_currentTile.GetTreasure().color == HIDDEN_TEXT BG_RED
						&& _currentPlayer->GetPawn().color == RED)
						||(_currentTile.GetTreasure().color == HIDDEN_TEXT BG_YELLOW
						&& _currentPlayer->GetPawn().color == YELLOW) 
						||(_currentTile.GetTreasure().color == HIDDEN_TEXT BG_GREEN
						&& _currentPlayer->GetPawn().color == GREEN) 
						|| (_currentTile.GetTreasure().color == HIDDEN_TEXT BG_BLUE
						&& _currentPlayer->GetPawn().color == BLUE))
					{
						grid.AddPlayerInTile(_currentCoordinates, _currentPlayer);
						_currentPlayer->SetPosition(_currentCoordinates);
						break;
					}
				}
			}
		}
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
	for (int _index = /*_cardSize - 1*/ 2; _index >= 0 ; _index--)
	{
		_randomIndex = RandomInt(0, _index);
		_playersCards[_index % _playerCount].push_back(_cardsToDistrib[_randomIndex]);
		_cardsToDistrib.erase(_cardsToDistrib.begin() + _randomIndex);
	}
	return _playersCards;
}




int Game::ChooseAction(const vector<string>& _options)
{
	int _sizeOption = static_cast<int>(_options.size());
	int _key;
	int _selector = 0;
	while (true)
	{
		SetCursorPosition(0, 0, false);
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
		if (_key == 72 || _key == 122 || _key == 90) // ↑
		{
			_selector = _selector > 0 ? _selector - 1 : _sizeOption - 1;
		}
		else if (_key == 80 || _key == 115 || _key == 83) // ↓
		{
			_selector = _selector < _sizeOption - 1 ? _selector + 1 : 0;
		}
		else if (_key == 13) // Enter
		{
			PlaySound(TEXT("Sounds/Clic.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return _selector;
		}
		RESET_SCREEN_LINE(5)
		//system("cls");
	}
}

void Game::DoAction(const u_int& _indexAction)
{
	switch (_indexAction)
	{
	case 0:
		system("cls");
		Play();
		break;

	case 1:
		system("cls");
		Option();
		break;

	case 2:
		return;
	default:
		break;
	}
}

pair<string, pair<u_int, u_int>> Game::OptionAction(const vector<pair<string, vector<u_int>>>& _options,
	const bool _hasQuitOptions, const pair<u_int,u_int>& _selector)
{
	int _sizeOptions = static_cast<int>(_options.size());
	pair<string, pair<u_int, u_int>> _returnValue =
		Selector(_selector, _options, _sizeOptions, _hasQuitOptions);
	return _returnValue;
}

void Game::DoOptionAction(const pair<string,pair<u_int, u_int>>& _actionIndex)
{
	currentOptions[_actionIndex.first] = _actionIndex.second.second;
}

void Game::Display()
{
	SetCursorPosition(0, 0, false);
	cout << grid << endl;

	u_int _currentTileIndex = 0;
	SetCursorPosition(47, 2);
	cout << WHITE_INTENSE_TEXT << "C'est à " << players[currentPlayerIndex]->GetName() << " (" << players[currentPlayerIndex]->GetPawn().GetAppearance() << ")" << " de jouer !" << endl;
	SetCursorPosition(47, 3);
	cout << "Et il te reste " << players[currentPlayerIndex]->GetCardLeft() << " objets à trouver !";
	SetCursorPosition(53, 24);
	for (u_int _index = 0; _index < 7; _index++)
	{
		cout << GRAY << "#";
	}
	for (u_int _index = 0; _index < 3; _index++)
	{
		SetCursorPosition(53, 25 + _index);
		cout << GRAY << "#" << currentTile.ToStringLine(_index) << GRAY << "#" << endl;
	}
	SetCursorPosition(53, 28);
	for (u_int _index = 0; _index < 7; _index++)
	{
		cout << GRAY << "#";
	}
	if (players[currentPlayerIndex]->HasCard())
	{
		const Card& _currentCard = players[currentPlayerIndex]->GetCurrentCard();
		for (u_int _index = 0; _index < 15; _index++)
		{
			SetCursorPosition(47, 8 + _index);
			cout << _currentCard.ToStringLine(_index) << endl;
		}
	}
}

void Game::Display(const vector<pair<string, vector<u_int>>>& _options,const u_int& _sizeOptions,
	const pair<u_int, u_int>& _selector, 
	const bool _hasQuitOptions)
{
	SetCursorPosition(0, 0, false);
	u_int _sizeCurrentOption;
	for (u_int _row = 0; _row < _sizeOptions + _hasQuitOptions; _row++)
	{
		if (_row == _sizeOptions)
		{
			if (_selector.first == _row)
			cout << WHITE_INTENSE_TEXT "[" RESET << "Quitter" << WHITE_INTENSE_TEXT "] " RESET;
			else
			cout << " " << "Quitter" << "  ";
			continue;
		}
		cout << _options[_row].first + " :" << endl;
		_sizeCurrentOption = static_cast<u_int>(_options[_row].second.size());
		for (u_int _column = 0; _column < _sizeCurrentOption; _column++)
		{
			if (_selector.first == _row && _selector.second == _column)
			{
				cout << WHITE_INTENSE_TEXT "[" RESET << _options[_row].second[_column] 
					 << WHITE_INTENSE_TEXT "] " RESET;
				continue;
			}
			else if (currentOptions[_options[_row].first] == _column)
			{
				cout << PINK "["  RESET << _options[_row].second[_column] 
					 << PINK "] " RESET;
				continue;
			}
			cout << " " << _options[_row].second[_column] << "  ";
		}
		cout << endl << endl;
	}
}

void Game::DisplayPawn(const vector<Object>& _pawns, int _pawnsCount, int _selector, const vector<string>& _separator, map<u_int, bool> _isPawnIndexColorTaken)
{
	SetCursorPosition(0, 3, false);
	for (int _index = 0; _index < _pawnsCount; _index++)
	{
		if (_selector == _index)
			cout << BLINK_TEXT;
		if (_isPawnIndexColorTaken[_index])
		{
			cout << GRAY << _pawns[_index].appearance << RESET " ";
			continue;
		}
		cout << _pawns[_index].GetAppearance() << RESET " ";
	}
}

pair<string, pair<u_int, u_int>> Game::Selector(pair<u_int, u_int> _selector, 
	const vector<pair<string,vector<u_int>>>& _options, const u_int& _sizeOptions, 
	const bool _hasQuitOptions)
{
	while (true)
	{
		Display(_options, _sizeOptions, _selector, _hasQuitOptions);
		int _key = _getch();
		if (_key == 72 || _key == 122 || _key == 90) // ↑
		{
			_selector.first = _selector.first == 0 ? _sizeOptions - 1 + _hasQuitOptions : _selector.first - 1;
			
			if (_selector.first == _sizeOptions)
				_selector.second = 0;
			else if (_selector.second >
				static_cast<u_int>(_options[_selector.first].second.size() - 1))
				_selector.first = _selector.first + 1;
		}
		else if (_key == 75 || _key == 113 || _key == 81) // gauche
		{
			if (_selector.first != _sizeOptions)
			_selector.second = 
				_selector.second == 0 ? static_cast<u_int>(_options[_selector.first].second.size() - 1) 
				: _selector.second - 1;
		}
		else if (_key == 77 || _key == 100 || _key == 68) // droite
		{
			if (_selector.first != _sizeOptions)
			_selector.second =
				_selector.second == static_cast<u_int>(_options[_selector.first].second.size() - 1) ? 0 
				: _selector.second + 1;
		}
		else if (_key == 80 || _key == 115 || _key == 83) // ↓
		{
			_selector.first = _selector.first == _sizeOptions - 1 + _hasQuitOptions ? 0 : _selector.first + 1;

			if (_selector.first == _sizeOptions)
				_selector.second = 0;
			else if (_selector.second >
				static_cast<u_int>(_options[_selector.first].second.size() - 1)) 
				_selector.first = _selector.first - 1;
		}
		else if (_key == 13) // Enter
		{
			PlaySound(TEXT("Sounds/Clic.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if(_selector.first == _sizeOptions) return make_pair("Quitter", make_pair(0,0));
			return make_pair(_options[_selector.first].first,_selector);
		}
	}
}






void Game::Option()
{
	vector<pair<string, vector<u_int>>> _options;
	for (const pair<string, vector<u_int>>& _currentOptions : options)
	{
		_options.push_back(_currentOptions);
	}
	pair<string, pair<u_int, u_int>> _actionIndex;
	do
	{
		_actionIndex = OptionAction(_options, true, _actionIndex.second);
		system("cls");
		if (_actionIndex.first == "Quitter")
		{
			PlaySound(TEXT("Sounds/Leave.wav"), NULL, SND_FILENAME | SND_ASYNC);
			break;
		}
		DoOptionAction(_actionIndex);
	} while (true);

}

void Game::Play()
{
	if (options["Nombre de joueurs"][currentOptions["Nombre de joueurs"]] <
		options["Nombre d'IA"][currentOptions["Nombre d'IA"]])
	{
		SetCursorPosition(0, 5, false);
		cout << RED << "Tu ne peux pas avoir plus d'IA que le nombre de joueur dans la partie !!" << RESET;
		return;
	}
	PlaySound(TEXT("Sounds/StartGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
	InitPlayers();
	InitGrid();
	PlacePawnInSpawn();
	bool _isFinish;
	while(true)
	{
		SetCursorPosition(47, 5);
		cout << GREEN << "Placement de la tuile..." << RESET;
		PlacementTile();
		SetCursorPosition(47, 5);
		cout << players[currentPlayerIndex]->GetPawn().color
			<<"Deplacement du pion...  " << RESET;
		MovementPlayer(players[currentPlayerIndex]);
		UpdateIfOnGoodCase();
		_isFinish = IsOver();
		if (IsOver()) break;
		++currentPlayerIndex %= static_cast<u_int>(players.size());
	}
	system("cls");
	PlaySound(TEXT("Sounds/Finish.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cout << players[currentPlayerIndex]->GetName() << "a gagner la partie !" << endl;
	system("pause");
	RESET_SCREEN_LINE(0);
	RESET_SCREEN_LINE(1);
}

bool Game::IsOver()
{
	Player* _currentPlayer = players[currentPlayerIndex];
	string _currentColor = grid.GetTile(_currentPlayer->GetPosition()).GetTreasure().color;
	return (!_currentPlayer->HasCard()
		&& ((_currentPlayer->GetPawn().color == RED
			&& _currentColor == HIDDEN_TEXT BG_RED)
			|| _currentPlayer->GetPawn().color == YELLOW
			&& _currentColor == HIDDEN_TEXT BG_YELLOW
			|| _currentPlayer->GetPawn().color == GREEN
			&& _currentColor == HIDDEN_TEXT BG_GREEN
			|| _currentPlayer->GetPawn().color == BLUE
			&& _currentColor == HIDDEN_TEXT BG_BLUE));
}

void Game::PlacementTile()
{
	while (true)
	{
		Display();
		int _key = _getch();
		if (_key == 72 || _key == 122 || _key == 90) // ↑
			grid.SelectorMove(MDT_UP);
		else if (_key == 75 || _key == 113 || _key == 81) // gauche
			grid.SelectorMove(MDT_LEFT);
		else if (_key == 77 || _key == 100 || _key == 68) // droite
			grid.SelectorMove(MDT_RIGHT);
		else if (_key == 80 /*|| _key == 115*/ || _key == 83) // ↓
			grid.SelectorMove(MDT_DOWN);
		else if (_key == 115 || _key == 17) // 
			currentTile.Rotate(RT_LEFT);
		else if (_key == 116 || _key == 4) // 
			currentTile.Rotate(RT_RIGHT);
		else if (_key == 13) // Enter
		{
			currentTile = grid.PlaceTile(currentTile);
			return;
		}
		//system("cls");
	}
}

void Game::UpdateIfOnGoodCase()
{
	Player* _currentPlayer = players[currentPlayerIndex];
	const pair<u_int,u_int>& _coordinates = _currentPlayer->GetPosition();
	if (_currentPlayer->HasCard() && grid.GetTile(_coordinates) == _currentPlayer->GetCurrentCard())
	{
		_currentPlayer->NextCard();
		PlaySound(TEXT("Sounds/FindTreasure.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void Game::MovementPlayer(Player* _currentPlayer)
{
	int _key;
	while (true)
	{
		Display();
		_key = _getch();
		const pair<u_int, u_int>& _position = _currentPlayer->GetPosition();
		pair<u_int, u_int> _newPosition = _position;
		pair<u_int, u_int> _tempPosition = _position;
		map<MyDirectionType, bool> _open = grid.GetTile(_position).GetDirectionsOpen();
		map<MyDirectionType, bool> _open1;
		if (_key == 72 || _key == 122 || _key == 90) // ↑
		{
			if (_tempPosition.first-- == 0)
				continue;
			_open1 = grid.GetTile(_tempPosition).GetDirectionsOpen();
			if (_open[MDT_UP] && _open1[MDT_DOWN])
				--_newPosition.first;
		}
		else if (_key == 75 || _key == 113 || _key == 81) // gauche
		{
			if (_tempPosition.second-- == 0)
				continue;
			_open1 = grid.GetTile(_tempPosition).GetDirectionsOpen();
			if (_open[MDT_LEFT] && _open1[MDT_RIGHT])
				--_newPosition.second;
		}
		else if (_key == 77 || _key == 100 || _key == 68) // droite
		{
			if (_tempPosition.second++ == grid.GetTiles().size() - 1)
				continue;
			_open1 = grid.GetTile(_tempPosition).GetDirectionsOpen();
			if (_open[MDT_RIGHT] && _open1[MDT_LEFT])
				++_newPosition.second;
		}
		else if (_key == 80 || _key == 115 || _key == 83) // ↓
		{
			if (_tempPosition.first++ == grid.GetTiles().size() - 1)
				continue;
			_open1 = grid.GetTile(_tempPosition).GetDirectionsOpen();
			if (_open[MDT_DOWN] && _open1[MDT_UP])
				++_newPosition.first;
		}
		else if (_key == 13) // Enter
		{
			return;
		}
		_currentPlayer->SetPosition(_newPosition);
		grid.RemovePlayerInTile(_position, _currentPlayer);
		grid.AddPlayerInTile(_newPosition, _currentPlayer);
		if (_newPosition != _position)
			PlaySound(TEXT("Sounds/PawnMove.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void Game::Launch()
{
	vector<string> _options = { "Jouer", "Option", "Quitter" };
	u_int _actionIndex;
	do
	{
		SetCursorPosition(0, 0, false);
		_actionIndex = ChooseAction(_options);
		//system("cls");
		DoAction(_actionIndex);
	} while (_actionIndex != 2);
	PlaySound(TEXT("Sounds/Leave.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(1000);
}