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

void Tile::RotateCases(const RotateType& _rotateType)
{
	const u_int& _size = static_cast<u_int>(cases.size());
	if (_size == 0) return;
	for (u_int _rowIndex = 0; _rowIndex < _size; _rowIndex++)
	{
		for (u_int _columnIndex = _rowIndex + 1; _columnIndex < _size; _columnIndex++)
		{
			swap(cases[_rowIndex][_columnIndex], cases[_columnIndex][_rowIndex]);
		}
	}
	if (_rotateType == RT_RIGHT)
	{
		for (u_int _index = 0; _index < _size; _index++)
		{
			reverse(cases[_index].begin(), cases[_index].end());
		}
	}
	else if (_rotateType == RT_LEFT)
	{
		for (u_int _columnIndex = 0; _columnIndex < _size; _columnIndex++)
		{
			for (u_int _rowIndex = 0; _rowIndex < _size / 2; _rowIndex++)
			{
				swap(cases[_rowIndex][_columnIndex], cases[_size - _rowIndex - 1][_columnIndex]);
			}
		}
	}
}

void Tile::Rotate(const RotateType& _rotateType)
{
	RotateCases(_rotateType);
	ChangeOpenDirection(_rotateType);
}

inline ostream& operator<<(ostream& _stream, const Tile& _tile)
{
	_stream << _tile.ToString();
	return _stream;
}
