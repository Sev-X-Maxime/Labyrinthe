#pragma once
#include "Tile.h"
#include <DisplaySystem.h>
using namespace Console;
#define SEPARATOR BLUE "#" RESET
#define SEPARATOR_IN_STREAM _stream << SEPARATOR
class Grid
{
	vector<vector<Tile>> tiles;
	pair<u_int, u_int> selector;
	map < u_int, pair<u_int, u_int>> pushableCoordinates;
	u_int arrowSelector;
	vector<MyDirectionType> directionArrowPlacement;
protected:

public:
	inline u_int GetArrowSelector() const
	{
		return arrowSelector;
	}
	inline pair<u_int, u_int> GetPushCoordinates()
	{
		return pushableCoordinates[arrowSelector];
	}
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
	inline Tile GetTile(pair<u_int, u_int> _position) const
	{
		return tiles[_position.first][_position.second];
	}
	inline void AddPlayerInTile(pair<u_int, u_int> _position, Player _player)
	{
		tiles[_position.first][_position.second].AddPlayer(_player);
	}
	inline void RemovePlayerInTile(pair<u_int, u_int> _position, Player _player)
	{
		tiles[_position.first][_position.second].RemovePlayer(_player);
	}
public:
	Grid();
private:
	void InitArrowsSelector();
public:
	Tile PlaceTile(Tile _tile);
	Tile PlaceTile(Tile _tile, const u_int& _position, const MyDirectionType& _direction);
	Tile PlaceAtRight(Tile _tile, const u_int& _position);
	Tile PlaceAtLeft(Tile _tile, const u_int& _position);
	Tile PlaceAtTop(Tile _tile, const u_int& _position);
	Tile PlaceAtBotom(Tile _tile, const u_int& _position);

	void SelectorMove(const MyDirectionType& _direction);
protected:

private:

public:

	friend inline ostream& operator<< (ostream& _stream, Grid _grid)
	{
		const u_int _size = static_cast<u_int>(_grid.tiles.size());
		u_int _curentArrow = 0;
		for (u_int _index = 0; _index < _size * 2 * 3; _index++)
		{
			if (_index % 12 == 9)
			{
				if (_grid.arrowSelector == _curentArrow)
					_stream << BG_WHITE BLACK_INTENSE_TEXT BLINK_TEXT "V" RESET;
				else
					_stream << YELLOW "V" RESET;
				++_curentArrow;
			}
			else
				SEPARATOR_IN_STREAM;
		}
		SEPARATOR_IN_STREAM;
		_stream << endl;
		for (u_int _row = 0; _row < _size * 3; _row++)
		{
			if (_row > 0 && _row % 3 == 0)
			{
				for (u_int _index = 0; _index < _size * 3 * 2; _index++)
				{
					SEPARATOR_IN_STREAM;
				}
				SEPARATOR_IN_STREAM;
				_stream << endl;
			}
			if ((_row / 3) % 2 == 1
				&& _row % 3 == 1)
			{
				if (_grid.arrowSelector == _curentArrow)
					_stream << BG_WHITE BLACK_INTENSE_TEXT BLINK_TEXT ">" RESET;
				else
					_stream << YELLOW ">" RESET;
				++_curentArrow;
			}
			else
				SEPARATOR_IN_STREAM;
			for (u_int _column = 0; _column < _size; _column++)
			{
				_stream << _grid.tiles[_row / 3][_column].ToStringLine(_row % 3);

				if (_column == (_size - 1)
					&& (_row / 3) % 2 == 1
					&& _row % 3 == 1)
				{
					if (_grid.arrowSelector == _curentArrow)
						_stream << BG_WHITE BLACK_INTENSE_TEXT BLINK_TEXT "<" RESET;
					else
						_stream << YELLOW "<" RESET;
					++_curentArrow;
					continue;
				}
				SEPARATOR_IN_STREAM;
			}
			_stream << endl;
		}

		for (u_int _index = 0; _index < _size * 3 * 2; _index++)
		{
			if (_index % 12 == 9)
			{
				if (_grid.arrowSelector == _curentArrow)
					_stream << BG_WHITE BLACK_INTENSE_TEXT BLINK_TEXT "A" RESET;
				else
					_stream << YELLOW "A" RESET;
				++_curentArrow;
			}
			else
				SEPARATOR_IN_STREAM;
		}
		SEPARATOR_IN_STREAM;
		return _stream;
	}
};