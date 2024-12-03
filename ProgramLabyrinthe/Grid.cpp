#include "Grid.h"

Tile Grid::PlaceTile(Tile _tile, const pair<u_int, u_int>& _position, const DirectionType& _direction)
{
	switch (_direction)
	{
	case DT_RIGHT:
		return PlaceAtRight(_tile, _position);
	case DT_LEFT:
		return PlaceAtLeft(_tile, _position);
	case DT_UP:
		return PlaceAtTop(_tile, _position);
	case DT_DOWN:
		return PlaceAtBotom(_tile, _position);
	default:
		throw exception("Default PlaceTile() !");
	}
}

Tile Grid::PlaceAtRight(Tile _tile, const pair<u_int, u_int>& _position)
{
	Tile _firstTile = tiles[_position.first][0];
	tiles[_position.first].erase(tiles[_position.first].begin());
	tiles[_position.first].push_back(_tile);
	return _firstTile;
}

Tile Grid::PlaceAtLeft(Tile _tile, const pair<u_int, u_int>& _position)
{
	u_int _size = static_cast<u_int>(tiles.size() - 1);
	Tile _lastTile = tiles[_position.first][_size];
	tiles[_position.first].pop_back();
	tiles[_position.first].emplace(tiles[_position.first].begin(), _tile);
	return _lastTile;
}

Tile Grid::PlaceAtTop(Tile _tile, const pair<u_int, u_int>& _position)
{
	u_int _size = static_cast<u_int>(tiles.size());
	Tile _lastTile = tiles[_size - 1][_position.second];
	for (u_int _index = 1; _index < _size; _index++)
	{
		tiles[_index][_position.second] = tiles[_index - 1][_position.second];
	}
	tiles[0][_position.second] = _tile;
	return _lastTile;
}

Tile Grid::PlaceAtBotom(Tile _tile, const pair<u_int, u_int>& _position)
{
	u_int _size = static_cast<u_int>(tiles.size());
	Tile _lastTile = tiles[0][_position.second];
	for (u_int _index = 0; _index < _size - 1; _index++)
	{
		tiles[_index][_position.second] = tiles[_index + 1][_position.second];
	}
	tiles[0][_position.second] = _tile;
	return _lastTile;
}

	