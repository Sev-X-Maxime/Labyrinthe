#pragma once
#include "Tile.h"
#include <DisplaySystem.h>
using namespace Console;
#define SEPARATOR BLACK_INTENSE_TEXT "#" RESET
#define SEPARATOR_IN_STREAM _stream << SEPARATOR
#define SEPARATOR_LINE for (u_int _index = 0; _index < _size * 3 * 2; _index++) \
				{\
					SEPARATOR_IN_STREAM;\
				}

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
	inline void SetTileTreasure(pair<u_int, u_int> _position, const Object& _treasure)
	{
		tiles[_position.first][_position.second].SetTreasure(_treasure);
	}
	inline Tile GetTile(pair<u_int,u_int> _position) const
	{
		return tiles[_position.first][_position.second];
	}
public:
	Grid(const u_int& _size = 7);

public:
	Tile PlaceTile(Tile _tile, const pair<u_int, u_int>& _position, const MyDirectionType& _direction);
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
		for (u_int _index = 0; _index < _size * 3 * 2; _index++)
		{
			if (_index > 9 && (_index) / 9 == 0)
				_stream << YELLOW_BASE "V" RESET;
			else
				SEPARATOR_IN_STREAM;
		}
		SEPARATOR_IN_STREAM;
		_stream << endl;
		for (u_int _row = 0; _row < _size * 3; _row++)
		{
			if (_row > 0 && _row % 3 == 0)
			{
				for (u_int _index = 0; _index < _size * 3 * 2; _index++) \
				{
					SEPARATOR_IN_STREAM;
				}
				SEPARATOR_IN_STREAM;
				_stream << endl;
			}
			if ((_row / 3) % 2 == 1 
				&& _row % 3 == 1)
				_stream << YELLOW_BASE ">" RESET;
			else
				SEPARATOR_IN_STREAM;
			for (u_int _column = 0; _column < _size; _column++)
			{
				_stream << _grid.tiles[_row/3][_column].ToStringLine(_row %3);
				
				if (_column == (_size - 1) 
					&& (_row / 3) % 2 == 1 
					&& _row % 3 == 1)
				{
					_stream << YELLOW_BASE "<" RESET;
					continue;
				}
				SEPARATOR_IN_STREAM;
			}
			_stream <<endl;
		}

		for (u_int _index = 0; _index < _size * 3 * 2; _index++) \
		{
			if ((_index / 3) % 2 == 0)
				SEPARATOR_IN_STREAM;
			else
				_stream << YELLOW_BASE "A" RESET;
		}
		SEPARATOR_IN_STREAM;
		return _stream;
	}
};

