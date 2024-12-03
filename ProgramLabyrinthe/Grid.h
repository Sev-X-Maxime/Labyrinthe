#pragma once
#include "Tile.h"

class Grid
{
	vector<vector<Tile>> tiles;

protected:

public:
	inline Tile GetTile(pair<u_int,u_int> _position) const
	{
		return tiles[_position.first][_position.second];
	}

public:
	Grid() = default;

public:
	Tile PlaceTile(Tile _tile, const pair<u_int, u_int>& _position, const DirectionType& _direction);
	Tile PlaceAtRight(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtLeft(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtTop(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtBotom(Tile _tile, const pair<u_int, u_int>& _position);
protected:

private:

public:
	friend ostream& operator<< (ostream& _stream, Grid _grid);
};

