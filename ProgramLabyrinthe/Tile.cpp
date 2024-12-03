#include "Tile.h"

Tile::Tile(const map<DirectionType, bool>& _directionsOpen, const bool _isFixed, const u_int& _size)
{
	playersInCase = vector<Player>();
	directionsOpen = _directionsOpen;
	fixed = _isFixed;
	InitCases(_size);
}


void Tile::InitCases( const u_int& _size)
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
	map<DirectionType, pair<u_int, u_int>> _directionCoordinates =
	{
		make_pair(DT_RIGHT, make_pair(1,2)),
		make_pair(DT_LEFT, make_pair(1, 0)),
		make_pair(DT_DOWN, make_pair(2, 1)),
		make_pair(DT_UP, make_pair(0,1))
	};
	pair<u_int, u_int> _coordinatesDirection;
	for (const pair<DirectionType,bool>& _currentDirection : directionsOpen)
	{
		_coordinatesDirection =
			_directionCoordinates[_currentDirection.first];
		cases[_coordinatesDirection.first][_coordinatesDirection.second] =
			 _currentDirection.second ? Object(' ',"") : Object();
	}
}

void Tile::ChangeOpenDirections(const RotateType& _rotateType)
{
	bool _upIsOpen = directionsOpen[DT_UP];
	switch (_rotateType)
	{
	case RT_RIGHT:
		directionsOpen[DT_UP] = directionsOpen[DT_LEFT];
		directionsOpen[DT_LEFT] = directionsOpen[DT_DOWN];
		directionsOpen[DT_DOWN] = directionsOpen[DT_RIGHT];
		directionsOpen[DT_RIGHT] = _upIsOpen;
		break;
	case RT_LEFT:
		directionsOpen[DT_UP] = directionsOpen[DT_RIGHT];
		directionsOpen[DT_RIGHT] = directionsOpen[DT_DOWN];
		directionsOpen[DT_DOWN] = directionsOpen[DT_LEFT];
		directionsOpen[DT_LEFT] = _upIsOpen;
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

void Tile::AddPlayer(Player _player)
{
}

void Tile::RemovePlayer(Player _player)
{
}

inline ostream& operator<<(ostream& _stream, Tile _tile)
{
	_stream << _tile.ToString();
	return _stream;
}

inline bool Tile::operator==(const Card& _card) const
{
	return GetTreasure() == _card.treasure;
}