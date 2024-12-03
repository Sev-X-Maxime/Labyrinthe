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
	Grid(const u_int& _size = 7);

public:
	Tile PlaceTile(Tile _tile, const pair<u_int, u_int>& _position, const DirectionType& _direction);
	Tile PlaceAtRight(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtLeft(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtTop(Tile _tile, const pair<u_int, u_int>& _position);
	Tile PlaceAtBotom(Tile _tile, const pair<u_int, u_int>& _position);
protected:

private:

public:
	friend inline ostream& operator<< (ostream& _stream, Grid _grid)
	{
		const u_int _size = static_cast<u_int>(_grid.tiles.size());
		for (u_int _row = 0; _row < _size; _row++)
		{
			for (u_int _rowCase = 0; _rowCase < 3; _rowCase++)
			{
				for (u_int _column = 0; _column < _size; _column++)
				{
					_stream << _grid.tiles[_row][_column].ToStringLine(_rowCase);
				}
				_stream << '\n';
			}
		}
		return _stream;
	}
};

