#include "Grid.h"

Grid::Grid(const u_int& _size)
{
	for (u_int _index = 0; _index < _size; _index++)
	{
		tiles.push_back(vector<Tile>());
	}
	selector = { 0, 0 };
}

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

ostream& operator<<(ostream& _stream, Grid _grid)
{
	const u_int _size = static_cast<u_int>(_grid.tiles.size());
	for (u_int _row = 0; _row < _size; _row++)
	{
		for (u_int _rowCase = 0; _rowCase < 3; _rowCase++)
		{
			for (u_int _column = 0; _column < _size; _column++)
			{
				if (_column % 2 == 1 && _row % 2 == 1)
				{
					if (_grid.selector.first == 0)
					{
						_stream << "V" << endl << _grid.tiles[_row][_column].ToStringLine(_rowCase);
					}
					else if (_grid.selector.first > 0 && _grid.selector.second == 0)
					{
						_stream << _grid.tiles[_row][_column].ToStringLine(_rowCase) << ">" << endl;
					}
					else if (_grid.selector.first > 0 && _grid.selector.second == _size)
					{
						_stream << "<" << endl << _grid.tiles[_row][_column].ToStringLine(_rowCase);
					}
					else
					{
						_stream << _grid.tiles[_row][_column].ToStringLine(_rowCase) << endl << "^" << endl;
					}
				}
				_stream << _grid.tiles[_row][_column].ToStringLine(_rowCase);
			}
			_stream << '\n';
		}
	}
	return _stream;
}