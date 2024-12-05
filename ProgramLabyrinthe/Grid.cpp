#include "Grid.h"

Grid::Grid(const u_int& _size)
{
	arrowSelector = 0;
	InitArrowsSelector();
}

void Grid::InitArrowsSelector()
{
	pushableCoordinates[0] = make_pair(0, 1);
	pushableCoordinates[1] = make_pair(0, 3);
	pushableCoordinates[2] = make_pair(0, 5);
	pushableCoordinates[3] = make_pair(1, 0);
	pushableCoordinates[4] = make_pair(1, 6);
	pushableCoordinates[5] = make_pair(3, 0);
	pushableCoordinates[6] = make_pair(3, 6);
	pushableCoordinates[7] = make_pair(5, 0);
	pushableCoordinates[8] = make_pair(5, 6);
	pushableCoordinates[9] = make_pair(6, 1);
	pushableCoordinates[10] = make_pair(6, 3);
	pushableCoordinates[11] = make_pair(6, 5);
}

Tile Grid::PlaceTile(Tile _tile)
{
	const pair<u_int, u_int>& _currentPlaceCoordinates = GetPushCoordinates();
	if (_currentPlaceCoordinates.second == 0)
		return PlaceTile(_tile, _currentPlaceCoordinates.first, MDT_LEFT);
	else if (_currentPlaceCoordinates.second == 6)
		return PlaceTile(_tile, _currentPlaceCoordinates.first, MDT_RIGHT);
	else if (_currentPlaceCoordinates.first == 0)
		return PlaceTile(_tile, _currentPlaceCoordinates.second, MDT_UP);
	else if (_currentPlaceCoordinates.first == 6)
		return PlaceTile(_tile, _currentPlaceCoordinates.second, MDT_DOWN);
	throw exception("Invalid Coordinates to placement");
}

Tile Grid::PlaceTile(Tile _tile, const u_int& _position, const MyDirectionType& _direction)
{
	switch (_direction)
	{
	case MDT_RIGHT:
		return PlaceAtRight(_tile, _position);
	case MDT_LEFT:
		return PlaceAtLeft(_tile, _position);
	case MDT_UP:
		return PlaceAtTop(_tile, _position);
	case MDT_DOWN:
		return PlaceAtBotom(_tile, _position);
	default:
		throw exception("Default PlaceTile() !");
	}
}

Tile Grid::PlaceAtRight(Tile _tile, const u_int& _position)
{
	Tile _firstTile = tiles[_position][0];
	tiles[_position].erase(tiles[_position].begin());
	tiles[_position].push_back(_tile);
	return _firstTile;
}

Tile Grid::PlaceAtLeft(Tile _tile, const u_int& _position)
{
	u_int _size = static_cast<u_int>(tiles.size() - 1);
	Tile _lastTile = tiles[_position][_size];
	tiles[_position].pop_back();
	tiles[_position].emplace(tiles[_position].begin(), _tile);
	return _lastTile;
}

Tile Grid::PlaceAtTop(Tile _tile, const u_int& _position)
{
	u_int _size = static_cast<u_int>(tiles.size());
	Tile _lastTile = tiles[_size - 1][_position];
	for (u_int _index = _size - 1; _index > 0; _index--)
	{
		tiles[_index][_position] = tiles[_index - 1][_position];
	}
	tiles[0][_position] = _tile;
	return _lastTile;
}

Tile Grid::PlaceAtBotom(Tile _tile, const u_int& _position)
{
	u_int _size = static_cast<u_int>(tiles.size());
	Tile _lastTile = tiles[_size - 1][_position];
	for (u_int _index = 0; _index < _size - 1; _index++)
	{
		tiles[_index][_position] = tiles[_index + 1][_position];
	}
	tiles[_size - 1][_position] = _tile;
	return _lastTile;
}



void Grid::SelectorMove(const MyDirectionType& _direction)
{
	int _changerValue = 0;
	if (_direction == MDT_RIGHT || _direction == MDT_LEFT)
	{
		if (arrowSelector >= 3 && arrowSelector <= 8)
			if (arrowSelector % 2 == 1)
				_changerValue = 1;
			else
				_changerValue = -1;
		else
			if (_direction == MDT_RIGHT)
				if (arrowSelector == 2)
					_changerValue = 2;
				else if (arrowSelector == 11)
					_changerValue = -3;
				else
					_changerValue = 1;
			else if (_direction == MDT_LEFT)
				if (arrowSelector == 0)
					_changerValue = 3;
				else if (arrowSelector == 9)
					_changerValue = -2;
				else
					_changerValue = -1;
	}
	else if (_direction == MDT_UP || _direction == MDT_DOWN)
	{
		if (arrowSelector >= 0 && arrowSelector <= 2)
			_changerValue = 9;
		else if (arrowSelector >= 9 && arrowSelector <= 11)
			_changerValue = -9;
		else
			if (_direction == MDT_UP)
				if (arrowSelector == 3)
					_changerValue = -3;
				else if (arrowSelector == 4 || 
					(arrowSelector >= 3 && arrowSelector <= 8))
					_changerValue = -2;
				else
					_changerValue = 1;
			else if (_direction == MDT_DOWN)
				if (arrowSelector == 8)
					_changerValue = 3;
				else
					_changerValue = 2;
	}
	arrowSelector += _changerValue;
}

	