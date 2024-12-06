#include "Tile.h"

Tile::Tile()
{
	bool _currentBool;
	do
	{
		for (u_int _index = 0; _index < MDT_COUNT; _index++)
		{
			_currentBool = RandomInt(0, 1);
			directionsOpen[static_cast<MyDirectionType>(_index)] = _currentBool;
		}
	} while (!GoodCountDirectionsOpen());

	playersInCase = vector<Entity*>();
	fixed = false;
	InitCases();
}

Tile::Tile(const map<MyDirectionType, bool>& _directionsOpen, const bool _isFixed, const u_int& _size)
{
	playersInCase = vector<Entity*>();
	directionsOpen = _directionsOpen;
	fixed = _isFixed;
	InitCases(_size);
}


void Tile::InitCases(const u_int& _size)
{
	cases = vector<vector<Object>>();
	for (u_int _rowIndex = 0; _rowIndex < _size; _rowIndex++)
	{
		cases.push_back(vector<Object>());
		for (u_int _columnIndex = 0; _columnIndex < _size; _columnIndex++)
		{
			cases[_rowIndex].push_back(Object());
		}
	}
	cases[1][1] = Object(' ',"");
	UpdateVectorWithDirections();
}

void Tile::UpdateVectorWithDirections()
{
	map<MyDirectionType, pair<u_int, u_int>> _directionCoordinates =
	{
		make_pair(MDT_RIGHT, make_pair(1,2)),
		make_pair(MDT_LEFT, make_pair(1, 0)),
		make_pair(MDT_DOWN, make_pair(2, 1)),
		make_pair(MDT_UP, make_pair(0,1))
	};
	pair<u_int, u_int> _coordinatesDirection;
	for (const pair<MyDirectionType,bool>& _currentDirection : directionsOpen)
	{
		_coordinatesDirection =
			_directionCoordinates[_currentDirection.first];
		cases[_coordinatesDirection.first][_coordinatesDirection.second] =
			 _currentDirection.second ? Object(' ',"") : Object();
	}
}

void Tile::ChangeOpenDirections(const RotateType& _rotateType)
{
	bool _upIsOpen = directionsOpen[MDT_UP];
	switch (_rotateType)
	{
	case RT_RIGHT:
		directionsOpen[MDT_UP] = directionsOpen[MDT_LEFT];
		directionsOpen[MDT_LEFT] = directionsOpen[MDT_DOWN];
		directionsOpen[MDT_DOWN] = directionsOpen[MDT_RIGHT];
		directionsOpen[MDT_RIGHT] = _upIsOpen;
		break;
	case RT_LEFT:
		directionsOpen[MDT_UP] = directionsOpen[MDT_RIGHT];
		directionsOpen[MDT_RIGHT] = directionsOpen[MDT_DOWN];
		directionsOpen[MDT_DOWN] = directionsOpen[MDT_LEFT];
		directionsOpen[MDT_LEFT] = _upIsOpen;
		break;
	default:
		break;
	}
}

void Tile::Rotate(const RotateType& _rotateType)
{
	ChangeOpenDirections(_rotateType);
	UpdateVectorWithDirections();
}

void Tile::AddPlayer(Entity* _player)
{
	playersInCase.push_back(_player);
}

void Tile::RemovePlayer(Entity* _player)
{
	u_int _indexPlayer = 0;
	const u_int& _nbPlayersInCase = static_cast<u_int>(playersInCase.size());
	for (u_int _index = 0; _index < _nbPlayersInCase; _index++)
	{
		if (playersInCase[_index]->GetName() == _player->GetName())
		{
			_indexPlayer = _index;
		}
	}
	playersInCase.erase(playersInCase.begin() + _indexPlayer);
}