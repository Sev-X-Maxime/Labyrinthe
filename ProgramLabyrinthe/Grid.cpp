#include "Grid.h"

ostream& operator<<(ostream& _stream, Grid _grid)
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

void Grid::PlaceTile(const vector<Tile>& _tile, const pair<u_int, u_int>& _position, const DirectionType& _direction)
{
	switch (_direction)
	{
	case DT_RIGHT:
		GridChange(_position);
		break;
	case DT_LEFT:
		break;
	case DT_UP:
		break;
	case DT_DOWN:
		break;
	default:
		break;
	}
}

void Grid::GridChange(const pair<u_int, u_int>& _position)
{
	u_int _size = tiles.size();
	for (u_int _index = 0; _index < _size; _index++)
	{
		tiles[_position.first][_size - _index] = tiles[_position.first][_size - _index - 1];
	}
}

