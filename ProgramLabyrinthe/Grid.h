#pragma once
#include "Tile.h"

class Grid
{
	vector<vector<Tile>> tiles;
	pair<u_int, u_int> selector;

protected:

public:
	inline vector<vector<Tile>> GetTiles() const
	{
		return tiles;
	}
	inline void SetTiles(vector<vector<Tile>> _grid)
	{
		tiles = _grid;
	}
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

	friend inline ostream& operator<< (ostream& _stream, Grid _grid)
	{
		const u_int _size = static_cast<u_int>(_grid.tiles.size());
		for (u_int _row = 0; _row < _size; _row++)
		{
			_stream << BLACK_INTENSE_TEXT "#" RESET;
			for (u_int _index = 0; _index < _size * 3 * 2; _index++)
			{
				_stream << BLACK_INTENSE_TEXT "#" RESET;
			}
			_stream << endl;

			for (u_int _rowCase = 0; _rowCase < 3; _rowCase++)
			{
				_stream << BLACK_INTENSE_TEXT "#" RESET;
				for (u_int _column = 0; _column < _size; _column++)
				{
					_stream << _grid.tiles[_row][_column].ToStringLine(_rowCase);
					_stream << BLACK_INTENSE_TEXT "#" RESET;

				}
				_stream <<endl;
			}
		}
		for (u_int _index = 0; _index < _size * 3 * 2; _index++)
		{
			_stream << BLACK_INTENSE_TEXT "#" RESET;
		}
		_stream << BLACK_INTENSE_TEXT "#" RESET;
		return _stream;
	}
};

