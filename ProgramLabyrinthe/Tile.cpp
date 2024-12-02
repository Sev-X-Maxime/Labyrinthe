#include "Tile.h"

Tile::Tile(const map<DirectionType, bool>& _directionsOpen, const bool _isFixed, const u_int& _size)
{
	//playersInCase = set<Player>();
	directionsOpen = _directionsOpen;
	fixed = _isFixed;
	InitVector(cases, _size);
}

void Tile::InitVector(vector<vector<Object>>& _vector, const u_int& _size)
{
	_vector = vector<vector<Object>>();
	for (u_int _index = 0; _index < _size; _index++)
	{
		_vector.push_back(vector<Object>());
	}
}

void Tile::ChangeOpenDirection(const RotateType& _rotateType)
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

void Tile::ChangeCases(const RotateType& _rotateType)
{
	vector<vector<Object>> _newVector;
	const u_int& _size = static_cast<u_int>(cases.size());
	InitVector(_newVector, _size);
	Object _objectRightAngle = _newVector[0][2];
	switch (_rotateType)
	{
	case RT_RIGHT:
		break;
	case RT_LEFT:

		break;
	default:
		break;
	}
}

void Tile::Rotate(const RotateType& _rotateType)
{
	
	
}

inline ostream& operator<<(ostream& _stream, const Tile& _tile)
{
	_stream << _tile.ToString();
	return _stream;
}
