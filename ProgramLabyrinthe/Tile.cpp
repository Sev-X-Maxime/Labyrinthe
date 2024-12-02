#include "Tile.h"

Tile::Tile(const map<DirectionType, bool>& _directionsOpen, const bool _isFixed)
{
	cases = vector<vector<Object>>();
	//playersInCase = set<Player>();
	directionsOpen = _directionsOpen;
	fixed = _isFixed;
}

inline ostream& operator<<(ostream& _stream, const Tile& _tile)
{
	_stream << _tile.ToString();
	return _stream;
}
