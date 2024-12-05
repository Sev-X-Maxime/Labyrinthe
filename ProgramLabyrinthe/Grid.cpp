#include "Grid.h"

Grid::Grid(const u_int& _size)
{
	for (u_int _index = 0; _index < _size; _index++)
	{
		tiles.push_back(vector<Tile>());
	}
	arrowSelector = 0;
	pushableCoordinates[0] = make_pair(1,1);
	pushableCoordinates[1] = make_pair(1,3);
	pushableCoordinates[2] = make_pair(1,5);
	pushableCoordinates[3] = make_pair(0,0);
	pushableCoordinates[4] = make_pair(0,6);
	pushableCoordinates[5] = make_pair(2,0);
	pushableCoordinates[6] = make_pair(2,6);
	pushableCoordinates[7] = make_pair(4,0);
	pushableCoordinates[8] = make_pair(4,6);
	pushableCoordinates[9] = make_pair(6,1);
	pushableCoordinates[10] = make_pair(6,3);
	pushableCoordinates[11] = make_pair(6,5);

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

	