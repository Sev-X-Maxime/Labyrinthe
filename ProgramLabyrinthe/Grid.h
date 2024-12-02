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
	void PlaceTile(const vector<Tile>& _tile, const pair<u_int, u_int>& _position, const DirectionType& _direction);
	void GridChange(const pair<u_int, u_int>& _position);
protected:

private:

public:
		friend ostream& operator<< (ostream& _stream, Grid _grid);
};

