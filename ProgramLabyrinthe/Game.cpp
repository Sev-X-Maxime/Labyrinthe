#include "Game.h"
#define RESET_TO_WHITE RESET WHITE_INTENSE_TEXT
#define KEY_COLOR RED_INTENSE_TEXT

#define ARROW_UP "\xE2\xAC\x86"
#define ARROW_DOWN "\xE2\xAC\x87"
#define ARROW_LEFT "\xE2\xAC\x85"
#define ARROW_RIGHT "\xE2\x9E\x99"
#define ENTER_KEY "\xE2\x8F\x8E"

Game::Game()
{
	InitTreasures();
	InitStaticTiles();
	InitCards();
	options["Nombre d'IA"] = { 0,1,2,3,4 };
	options["Nombre de joueurs"] = { 2,3,4 };
	options["Sounds"] = { 1,0 };
	currentOptions["Nombre d'IA"] = 0;
	currentOptions["Sounds"] = 0;
	currentOptions["Nombre de joueurs"] = 0;
	selectors =
	{
		make_pair( BOLD_TEXT BLINK_TEXT WHITE_INTENSE_TEXT, RESET),
		make_pair(WHITE_INTENSE_TEXT "[" RESET, WHITE_INTENSE_TEXT "]" RESET),
		make_pair(WHITE_INTENSE_TEXT "<" RESET, WHITE_INTENSE_TEXT ">" RESET),

	};
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
			GetLine("Quel est le nom du joueur n" + to_string(_index + 1) + "?");
		players.push_back(new Player(_currentPlayerName, ChoosePawn(_isPawnIndexColorTaken), _cardsPlayer[_index]));
		system("cls");
	}
}

Object Game::ChoosePawn(map<u_int, bool>& _isPawnIndexColorTaken)
{
	const vector<Object>& _pawns =
	{
		Object("\xF0\x9F\x92\x99", CYAN),
		Object("\xF0\x9F\x92\x9B", YELLOW),
		Object("\xF0\x9F\x92\x9C", PURPLE),
		Object("\xF0\x9F\x92\x9A", GREEN)
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
			if (options["Sounds"][currentOptions["Sounds"]])
			PlaySound(TEXT("Sounds/TransitionMenu.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (_key == 77 || _key == 100 || _key == 68)
		{
			_selector = _selector < _pawnsCount - 1 ? _selector + 1 : 0;
			if (options["Sounds"][currentOptions["Sounds"]])
			PlaySound(TEXT("Sounds/TransitionMenu.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (_key == 27)
			++currentOptions["Selector"] %= selectors.size();
		else if (_key == 24)
			++currentOptions["Sounds"] %= options["Sounds"].size();
		else if (_key == 13)
		{
			if (options["Sounds"][currentOptions["Sounds"]])
			PlaySound(TEXT("Sounds/Clic.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (!_isPawnIndexColorTaken[_selector])
			{
				_isPawnIndexColorTaken[_selector] = true;
				return _pawns[_selector];
			}
			else
			{
				SetCursorPosition(0, 5, false);
				cout << RED << "Ce pion est deja pris !" << RESET;
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
	staticTiles[make_pair(0, 0)].SetTreasure(Object("\xF0\x9F\x94\xB5", CYAN));
	staticTiles[make_pair(0, 6)].SetTreasure(Object("\xF0\x9F\x9F\xA1",YELLOW));
	staticTiles[make_pair(6, 0)].SetTreasure(Object("\xF0\x9F\x9F\xA3", PURPLE));
	staticTiles[make_pair(6, 6)].SetTreasure(Object("\xF0\x9F\x9F\xA2", GREEN));
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
		if (grid.GetTile(_currentRandomCoordinates).GetTreasure() == "  ")
			grid.SetTileTreasure(_currentRandomCoordinates,
				treasures[_indexTreasure++]);
	}
}

void Game::InitTreasures()
{
	treasures = vector<Object>();
	treasures =
	{
		Object("\xF0\x9F\x90\x8D",BLACK),
		Object("\xF0\x9F\x8D\x94",BLACK),
		Object("\xF0\x9F\x92\xA3",BLACK),
		Object("\xF0\x9F\x91\x91",BLACK),
		Object("\xF0\x9F\x8E\xAE",BLACK),
		Object("\xF0\x9F\x92\xBB",BLACK),
		Object("\xF0\x9F\x9A\x9C",BLACK),
		Object("\xF0\x9F\x8D\x91",BLACK),
		Object("\xE2\x99\xBF",BLACK),
		Object("\xF0\x9F\x8D\x80",BLACK),
		Object("\xE2\x9B\x84",BLACK),
		Object("\xF0\x9F\x90\x89",BLACK),
		Object("\xF0\x9F\x8F\xA6",BLACK),
		Object("\xF0\x9F\x94\x91",BLACK),
		Object("\xF0\x9F\x8E\xBE",BLACK),
		Object("\xF0\x9F\x8E\x93",BLACK),
		Object("\xE2\x8F\xB0",BLACK),
		Object("\xF0\x9F\x97\xBC",BLACK),
		Object("\xF0\x9F\x92\xB0",BLACK),
		Object("\xF0\x9F\x90\xA7",BLACK),
		Object("\xF0\x9F\x91\xBB",BLACK),
		Object("\xF0\x9F\x8E\xA7",BLACK),
		Object("\xF0\x9F\x9B\x81",BLACK),
		Object("\xF0\x9F\x8D\xA5",BLACK),
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
	string _currentTileTreasureColor;
	pair<u_int, u_int> _currentCoordinates;
	Player* _currentPlayer;
	for (u_int _row = 0; _row < 7; _row++)
	{
		for (u_int _column = 0; _column < 7; _column++)
		{
			_currentCoordinates = make_pair(_row, _column);
			_currentTile = grid.GetTile(_currentCoordinates);
			_currentTileTreasureColor = _currentTile.GetTreasure().color;
			if (_currentTileTreasureColor == CYAN ||
				_currentTileTreasureColor == YELLOW ||
				_currentTileTreasureColor == PURPLE ||
				_currentTileTreasureColor == GREEN)
			{
				for (u_int _index = 0; _index < _playersCount; _index++)
				{
					_currentPlayer = players[_index];
					if(_currentTileTreasureColor == _currentPlayer->GetPawn().color)
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
	for (int _index =/* _cardSize - 1*/2; _index >= 0 ; _index--)
	{
		_randomIndex = RandomInt(0, _index);
		_playersCards[_index % _playerCount].push_back(_cardsToDistrib[_randomIndex]);
		_cardsToDistrib.erase(_cardsToDistrib.begin() + _randomIndex);
	}
	return _playersCards;
}



int Game::ChooseAction(const vector<string>& _options, const int _selectorBase)
{
	int _sizeOption = static_cast<int>(_options.size());
	int _key;
	int _selector = _selectorBase;
	const pair<string, string>& _currentSelector = selectors[currentOptions["Selector"]];
	while (true)
	{
		SetCursorPosition(0, 0, false);
		for (int _index = 0; _index < _sizeOption; _index++)
		{
			if (_selector == _index)
			{
				cout << " " << BOLD_TEXT BLINK_TEXT WHITE_INTENSE_TEXT << _options[_index] << RESET << endl;
				continue;
			}
			cout << WHITE_INTENSE_TEXT << _options[_index] << " " << RESET << endl;
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
		else if (_key == 27)
			++currentOptions["Selector"] %= selectors.size();
		else if (_key == 24)
			++currentOptions["Sounds"] %= options["Sounds"].size();
		else if (_key == 13) // Enter
		{
			if (options["Sounds"][currentOptions["Sounds"]])
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

void Game::DoOptionMenuAction(const int _actionIndex)
{
	switch (_actionIndex)
	{
	case 0:
		system("cls");
		DisplayRules();
		system("cls");
		break;
	case 1:
		system("cls");
		DisplayControls();
		system("cls");
		break;
	case 2:
		++currentOptions["Sounds"] %= options["Sounds"].size();
		break;

	case 3:
		system("cls");
		OptionsPlayer();
		break;

	case 4:
		return;
	default:
		break;
	}
}

void Game::Display()
{
	SetCursorPosition(0, 0, false);
	cout << grid << endl;

	u_int _currentTileIndex = 0;
	SetCursorPosition(64, 2);
	cout << WHITE_INTENSE_TEXT << "C'est a " << players[currentPlayerIndex]->GetName() << " (" << players[currentPlayerIndex]->GetPawn().GetAppearance() << WHITE_INTENSE_TEXT << ")" << " de jouer !";
	SetCursorPosition(64, 3);
	cout << "Et il te reste " << players[currentPlayerIndex]->GetCardLeft() << " objets a trouver !";
	SetCursorPosition(70, 24);
	for (u_int _index = 0; _index < 5; _index++)
	{
		cout << GRAY << "\xF0\x9F\x9F\xA5";
	}
	for (u_int _index = 0; _index < 3; _index++)
	{
		SetCursorPosition(70, 25 + _index);
		cout << GRAY << "\xF0\x9F\x9F\xA5" << currentTile.ToStringLine(_index) << GRAY << "\xF0\x9F\x9F\xA5" << endl;
	}
	SetCursorPosition(70, 28);
	for (u_int _index = 0; _index < 5; _index++)
	{
		cout << GRAY << "\xF0\x9F\x9F\xA5";
	}
	if (players[currentPlayerIndex]->HasCard())
	{
		const Card& _currentCard = players[currentPlayerIndex]->GetCurrentCard();
		for (u_int _index = 0; _index < 15; _index++)
		{
			SetCursorPosition(64, 8 + _index);
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
			cout << WHITE_INTENSE_TEXT "[" RESET << "Quitter" << WHITE_INTENSE_TEXT "]" RESET << RESET;
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
					<< WHITE_INTENSE_TEXT "] " RESET << RESET;
				continue;
			}
			else if (currentOptions[_options[_row].first] == _column)
			{
				cout << PINK << "[" << RESET << _options[_row].second[_column]
					 << PINK << "] " << RESET;
				continue;
			}
			cout << " " << _options[_row].second[_column] << "  ";
		}
		cout << endl << endl;
	}
}

void Game::DisplayPawn(const vector<Object>& _pawns, int _pawnsCount, int _selector, const vector<string>& _separator, map<u_int, bool> _isPawnIndexColorTaken)
{
	
	for (int _index = 0; _index < _pawnsCount; _index++)
	{
		SetCursorPosition(_index * 3, 4, false);
		cout << "                    ";
		SetCursorPosition(_index * 3, 4, false);
		if (_selector == _index)
			cout << "\xF0\x9F\x96\x95";
		SetCursorPosition(0 + _index * 3, 3, false);
		if (_isPawnIndexColorTaken[_index])
		{
			cout << GRAY << "\xF0\x9F\x92\x94" << RESET;
			continue;
		}
		cout << _pawns[_index].GetAppearance() << RESET;
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
		else if (_key == 27)
			++currentOptions["Selector"] %= selectors.size();
		else if (_key == 24)
			++currentOptions["Sounds"] %= options["Sounds"].size();
		else if (_key == 13) // Enter
		{
			if (options["Sounds"][currentOptions["Sounds"]])
			PlaySound(TEXT("Sounds/Clic.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if(_selector.first == _sizeOptions) return make_pair("Quitter", make_pair(0,0));
			return make_pair(_options[_selector.first].first,_selector);
		}
		//system("cls");
	}
}




void Game::DisplayRules()
{
	SetCursorPosition(0, 0, false);
	cout << BOLD_TEXT << YELLOW << "********** BIENVENUE DANS LE JEU : LE LABYRINTHE **********" << RESET << endl
			<< endl
			<< CYAN << ITALIC_TEXT << "Objectif du jeu :" << RESET << endl
			<< WHITE_INTENSE_TEXT << "- Deplacez-vous dans le labyrinthe et collectez les tresors avant vos adversaires." << RESET << endl
			<< endl
			<< GREEN << ITALIC_TEXT << "Règles principales :" << RESET << endl
			<< WHITE_INTENSE_TEXT << "1. A chaque tour, insérez une tuile pour modifier le labyrinthe." << RESET << endl
			<< WHITE_INTENSE_TEXT << "2. Deplacez votre pion sur le plateau pour atteindre vos objectifs." << RESET << endl
			<< WHITE_INTENSE_TEXT << "3. Le joueur qui récupère tous ses tresors en premier et retourne à sa case de depart remporte la partie." << RESET << endl
			<< endl
			<< PURPLE << ITALIC_TEXT << "Conseils :" << RESET << endl
			<< WHITE_INTENSE_TEXT << "- Utilisez le labyrinthe a votre avantage pour bloquer vos adversaires." << RESET << endl
			<< WHITE_INTENSE_TEXT << "- Planifiez vos deplacements pour maximiser vos chances de victoire." << RESET << endl
			<< endl
			<< BOLD_TEXT << RED << "********** AMUSEZ-VOUS BIEN ! **********"
			<< RESET << endl << endl;
	system("pause");
}

void Game::DisplayControls()
{
	SetCursorPosition(0, 0, false);
	cout << DIM_TEXT WHITE_INTENSE_TEXT << "Dans les menus : " << endl
			<< RESET_TO_WHITE << "Aller en haut : " << KEY_COLOR ARROW_UP << RESET_TO_WHITE " ou " KEY_COLOR"z" << RESET_TO_WHITE" ou " KEY_COLOR"Z" << endl
			<< RESET_TO_WHITE << "Aller a gauche : " << KEY_COLOR ARROW_LEFT << RESET_TO_WHITE " ou " KEY_COLOR"q" << RESET_TO_WHITE" ou " KEY_COLOR"Q" << endl
			<< RESET_TO_WHITE << "Aller en bas : " << KEY_COLOR ARROW_DOWN << RESET_TO_WHITE " ou " KEY_COLOR"s" << RESET_TO_WHITE" ou " KEY_COLOR"S" << endl
			<< RESET_TO_WHITE << "Aller a droite : " << KEY_COLOR ARROW_RIGHT << RESET_TO_WHITE " ou " KEY_COLOR"d" << RESET_TO_WHITE " ou " KEY_COLOR"D" << endl
			<< RESET_TO_WHITE << "Valider : " << KEY_COLOR ENTER_KEY << endl
			<< endl
		 << DIM_TEXT WHITE_INTENSE_TEXT << "Placement de la tuile dans la grille : " << endl
			<< RESET_TO_WHITE UNDERLINE_TEXT << "Sur les selecteurs du verticaux : " << endl
			 << RESET_TO_WHITE << "Aller au selecteur opposer : " << KEY_COLOR ARROW_UP << RESET_TO_WHITE " ou " KEY_COLOR ARROW_DOWN << RESET_TO_WHITE " ou " KEY_COLOR "Z" << RESET_TO_WHITE " ou " KEY_COLOR "S" << endl
			 << RESET_TO_WHITE << "Aller aux selecteurs du horizontaux : " << KEY_COLOR ARROW_LEFT << RESET_TO_WHITE " ou " KEY_COLOR ARROW_RIGHT << RESET_TO_WHITE " ou " KEY_COLOR"Q" << RESET_TO_WHITE " ou " KEY_COLOR"D" << RESET_TO_WHITE " selon l'extremite " << endl
			<< RESET_TO_WHITE UNDERLINE_TEXT << "Sur les selecteurs du horizontaux : " << endl
			 << RESET_TO_WHITE << "Aller au selecteur opposer : " << KEY_COLOR ARROW_LEFT RESET_TO_WHITE " ou " KEY_COLOR ARROW_RIGHT << RESET_TO_WHITE " ou " KEY_COLOR "Q" << RESET_TO_WHITE " ou " KEY_COLOR "D" << endl
			 << RESET_TO_WHITE << "Aller aux selecteurs du verticaux : " << KEY_COLOR ARROW_UP << RESET_TO_WHITE " ou " KEY_COLOR ARROW_DOWN << RESET_TO_WHITE " ou " KEY_COLOR"Z" << RESET_TO_WHITE " ou " KEY_COLOR"S" << RESET_TO_WHITE " selon l'extremite " << endl
		<< RESET_TO_WHITE UNDERLINE_TEXT << "Action de la tuile dans la main : " << endl
			 << RESET_TO_WHITE << "Tourner vers la gaucher : " << KEY_COLOR "Ctrl" RESET_TO_WHITE" + " KEY_COLOR ARROW_LEFT << RESET_TO_WHITE " ou " KEY_COLOR "Ctrl" RESET_TO_WHITE" + " KEY_COLOR "s" << RESET_TO_WHITE << " ou " KEY_COLOR "Ctrl" RESET_TO_WHITE" + " KEY_COLOR"S" << endl
			 << RESET_TO_WHITE << "Tourner vers la droite : " << KEY_COLOR "Ctrl" RESET_TO_WHITE" + " KEY_COLOR ARROW_RIGHT << RESET_TO_WHITE " ou " KEY_COLOR "Ctrl" RESET_TO_WHITE" + " KEY_COLOR "s" << RESET_TO_WHITE << " ou " KEY_COLOR "Ctrl" RESET_TO_WHITE" + "  KEY_COLOR"S" << endl
			 << RESET_TO_WHITE << "Placer la tuile : " << KEY_COLOR ENTER_KEY << endl
			 << endl
		<< DIM_TEXT WHITE_INTENSE_TEXT << "Deplacement du pion dans la grille : " << endl
			<< RESET_TO_WHITE << "Aller en haut : " << KEY_COLOR ARROW_UP << RESET_TO_WHITE " ou " KEY_COLOR"z" << RESET_TO_WHITE" ou " KEY_COLOR"Z" << endl
			<< RESET_TO_WHITE << "Aller a gauche : " << KEY_COLOR ARROW_LEFT << RESET_TO_WHITE " ou " KEY_COLOR"q" << RESET_TO_WHITE" ou " KEY_COLOR"Q" << endl
			<< RESET_TO_WHITE << "Aller en bas : " << KEY_COLOR ARROW_DOWN << RESET_TO_WHITE " ou " KEY_COLOR"s" << RESET_TO_WHITE" ou " KEY_COLOR"S" << endl
			<< RESET_TO_WHITE << "Aller a droite : " << KEY_COLOR  ARROW_RIGHT << RESET_TO_WHITE " ou " KEY_COLOR"d" << RESET_TO_WHITE " ou " KEY_COLOR"D" << endl
			<< RESET_TO_WHITE << "Valider le placement : " << KEY_COLOR ENTER_KEY << endl
			<< endl
		<< DIM_TEXT WHITE_INTENSE_TEXT << "Autres : " << endl
		 << RESET_TO_WHITE << "Couper le song : " << KEY_COLOR "Ctrl" RESET_TO_WHITE" + " KEY_COLOR "x" << RESET_TO_WHITE " ou " KEY_COLOR "Ctrl" RESET_TO_WHITE" + " KEY_COLOR "X" << endl
	<< endl << RESET;
	system("pause");
}


void Game::Option()
{
	vector<string> _options;
	_options.push_back("Les regles");
	_options.push_back("Les commandes");
	_options.push_back("Les option de Joueurs");
	_options.push_back("Quitter");
	int _actionIndex = 0;
	do
	{
		_options.emplace(_options.begin() + 2, options["Sounds"][currentOptions["Sounds"]] ? "\xF0\x9F\x94\x8A" : "\xF0\x9F\x94\x87");
		_actionIndex = ChooseAction(_options, _actionIndex);
		_options.erase(_options.begin() + 2);
		if (_actionIndex == 4)
		{
			if (options["Sounds"][currentOptions["Sounds"]])
				PlaySound(TEXT("Sounds/Leave.wav"), NULL, SND_FILENAME | SND_ASYNC);
			break;
		}
		DoOptionMenuAction(_actionIndex);
	} while (true);
	system("cls");
}

void Game::OptionsPlayer()
{
	vector<pair<string, vector<u_int>>> _options;
	for (const pair<string, vector<u_int>>& _currentOptions : options)
	{
		if (_currentOptions.first == "Sounds") continue;
		_options.push_back(_currentOptions);
	}
	pair<string, pair<u_int, u_int>> _actionIndex;
	do
	{
		_actionIndex = OptionAction(_options, true, _actionIndex.second);
		/*system("cls");*/
		if (_actionIndex.first == "Quitter")
		{
			if (options["Sounds"][currentOptions["Sounds"]])
				PlaySound(TEXT("Sounds/Leave.wav"), NULL, SND_FILENAME | SND_ASYNC);
			break;
		}
		DoOptionAction(_actionIndex);
	} while (true);
	system("cls");
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
	//TODO REMOVE QUAND IA
	if (options["Nombre d'IA"][currentOptions["Nombre d'IA"]] > 0)
	{
		SetCursorPosition(0, 5, false);
		cout << RED << "Fonctionalite d'IA pas encore implementer (en cours de dev) !!" << RESET;
		return;
	}
	if (options["Sounds"][currentOptions["Sounds"]])
	PlaySound(TEXT("Sounds/StartGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
	InitPlayers();
	InitGrid();
	PlacePawnInSpawn();
	while(true)
	{
		SetCursorPosition(64, 5);
		cout << GREEN << "Placement de la tuile..." << RESET;
		PlacementTile();
		SetCursorPosition(64, 5);
		cout << players[currentPlayerIndex]->GetPawn().color
			<<"Deplacement du pion...  " << RESET;
		MovementPlayer(players[currentPlayerIndex]);
		UpdateIfOnGoodCase();
		if (IsOver()) break;
		++currentPlayerIndex %= static_cast<u_int>(players.size());
	}
	system("cls");
	if (options["Sounds"][currentOptions["Sounds"]])
		PlaySound(TEXT("Sounds/Finish.wav"), NULL, SND_FILENAME | SND_SYNC);
	cout << players[currentPlayerIndex]->GetName() << " (" << players[currentPlayerIndex]->GetPawn().GetAppearance() << WHITE_INTENSE_TEXT << ")" << " a gagner la partie !" << endl;
	system("pause");
	system("cls");
}

bool Game::IsOver()
{
	Player* _currentPlayer = players[currentPlayerIndex];
	string _currentColor = grid.GetTile(_currentPlayer->GetPosition()).GetTreasure().color;
	return (!_currentPlayer->HasCard() && _currentPlayer->GetPawn().color == _currentColor);
}

void Game::PlacementTile()
{
	while (true)
	{
		Display();
		int _key = _getch();
		if (_key == 72 /*|| _key == 122*/ || _key == 90) // ↑
			grid.SelectorMove(MDT_UP);
		else if (_key == 75 /*|| _key == 113*/ || _key == 81) // gauche
			grid.SelectorMove(MDT_LEFT);
		else if (_key == 77 /*|| _key == 100*/ || _key == 68) // droite
			grid.SelectorMove(MDT_RIGHT);
		else if (_key == 80 /*|| _key == 115*/ || _key == 83) // ↓
			grid.SelectorMove(MDT_DOWN);
		else if (_key == 115 || _key == 17) // 
			currentTile.Rotate(RT_LEFT);
		else if (_key == 116 || _key == 4) // 
			currentTile.Rotate(RT_RIGHT);
		else if (_key == 24)
			++currentOptions["Sounds"] %= options["Sounds"].size();
		else if (_key == 13) // Enter
		{
			currentTile = grid.PlaceTile(currentTile);
			if (options["Sounds"][currentOptions["Sounds"]])
				PlaySound(TEXT("Sounds/WallMove.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
		if (options["Sounds"][currentOptions["Sounds"]])
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
		else if (_key == 24)
			++currentOptions["Sounds"] %= options["Sounds"].size();
		else if (_key == 13) // Enter
		{
			return;
		}
		_currentPlayer->SetPosition(_newPosition);
		grid.RemovePlayerInTile(_position, _currentPlayer);
		grid.AddPlayerInTile(_newPosition, _currentPlayer);
		if (_newPosition != _position && options["Sounds"][currentOptions["Sounds"]])
			PlaySound(TEXT("Sounds/PawnMove.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void Game::Launch()
{
	vector<string> _options = { "Jouer", "Option", "Quitter" };
	int _actionIndex = 0;
	do
	{
		SetCursorPosition(0, 0, false);
		_actionIndex = ChooseAction(_options, _actionIndex);
		//system("cls");
		DoAction(_actionIndex);
	} while (_actionIndex != 2);
	if (options["Sounds"][currentOptions["Sounds"]])
	PlaySound(TEXT("Sounds/Leave.wav"), NULL, SND_FILENAME | SND_SYNC);
}