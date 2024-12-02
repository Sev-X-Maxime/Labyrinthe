#pragma once
#include "Object.h"
#include "DirectionType.h"
#include <set>
#include <map>

class Tile
{
	vector<vector<Object>> cases;
	//set<Player> playersInCase;
	map<DirectionType, bool> directionsOpen;
	bool fixed;

public:
	inline string ToString() const
	{
		string _text;
		const u_int& _size = static_cast<u_int>(cases.size());
		for (u_int _rowIndex = 0; _rowIndex < _size; _rowIndex++)
		{
			for (u_int _columnIndex = 0; _columnIndex < _size; _columnIndex++)
			{
				_text += cases[_rowIndex][_columnIndex].GetAppearance() + " ";
			}
			_text += "\n";
		}
		return _text;
	}
	inline string ToStringLine(const u_int& _lineIndex) const
	{
		string _text;
		const u_int& _size = static_cast<u_int>(cases[_lineIndex].size());
		for (u_int _index = 0; _index < _size; _index++)
		{
			_text += cases[_lineIndex][_index].GetAppearance();
			if (_index < _size - 1)
				_text += " ";
		}
		return _text;
	}
	inline Object GetTreasure() const
	{
		return cases[1][1];
	}
	void SetTreasure(const Object& _treasure)
	{
		cases[1][1] = _treasure;
	}
	inline bool IsFixed() const
	{
		return fixed;
	}

public:
	Tile(const map<DirectionType, bool>& _directionsOpen, 
		const bool _isFixed = false, const u_int& _size = 3);

private:
	void InitVector(vector<vector<Object>>& _vector, const u_int& _size = 3);
	void ChangeOpenDirection(const RotateType& _rotateType);
	void ChangeCases(const RotateType& _rotateType);
public:
	void Rotate(const RotateType& _rotateType);

public:
	inline friend ostream& operator<< (ostream& _stream, const Tile& _tile);

};

