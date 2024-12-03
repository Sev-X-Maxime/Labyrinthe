#pragma once
#include "Tile.h"

class Grid
{
private:
	vector<vector<Tile>> tiles;

protected:

public:
	inline Tile GetTile(pair<u_int,u_int> _position) const
	{
		return tiles[_position.first][_position.second];
	}

public:
	

public:
	Tile PlaceTile(const Tile& _tile, const pair<u_int, u_int>& _position, const DirectionType& _direction);
	Tile PlaceAtRight(const Tile& _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtLeft(const Tile& _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtTop(const Tile& _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtBotom(const Tile& _tile, const pair<u_int, u_int>& _position);
protected:

private:

public:
		friend ostream& operator<< (ostream& _stream, Grid _grid);
};

