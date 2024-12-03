#pragma once
#include "Tile.h"

class Grid
{
	vector<vector<Tile>> tiles;
	pair<u_int, u_int> selector;

protected:

public:
	inline Tile GetTile(pair<u_int,u_int> _position) const
	{
		return tiles[_position.first][_position.second];
	}

public:
	Grid(const u_int& _size = 7);

public:
	Tile PlaceTile(Tile _tile, const pair<u_int, u_int>& _position, const DirectionType& _direction);
	Tile PlaceAtRight(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtLeft(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtTop(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtBotom(Tile _tile, const pair<u_int, u_int>& _position);
	void Display() const;
protected:

private:

public:
	friend ostream& operator<< (ostream& _stream, Grid _grid);
};

