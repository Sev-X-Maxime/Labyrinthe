#pragma once
#include "DirectionType.h"
#include "Player.h"
#include <set>
#include <map>

class Tile
{
	vector<vector<Object>> cases;
	vector<Player> playersInCase;
	map<DirectionType, bool> directionsOpen;
	bool fixed;

public:
	inline string ToString()
	{
		string _text;
		const u_int& _size = static_cast<u_int>(cases.size());
		for (u_int _rowIndex = 0; _rowIndex < _size; _rowIndex++)
		{
			for (u_int _columnIndex = 0; _columnIndex < _size; _columnIndex++)
			{
				if (!playersInCase.empty() && (_rowIndex == 1 && _columnIndex == 1))
				{
					_text += playersInCase[0].GetPawn().GetAppearance();
					rotate(playersInCase.begin(), playersInCase.begin() + 1, playersInCase.end());
				}
				else
					_text += cases[_rowIndex][_columnIndex].GetAppearance();
				if (_columnIndex < _size - 1)
					_text += " ";
			}
			_text += "\n";
		}
		return _text + RESET;
	}
	inline string ToStringLine(const u_int& _lineIndex)
	{
		string _text;
		const u_int& _size = static_cast<u_int>(cases[_lineIndex].size());
		for (u_int _index = 0; _index < _size; _index++)
		{
			if (!playersInCase.empty() && (_lineIndex == 1 && _index == 1))
			{
				_text += playersInCase[0].GetPawn().GetAppearance();
				rotate(playersInCase.begin(), playersInCase.begin() + 1, playersInCase.end());
			}
			else
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
	Tile() = default;
	Tile(const map<DirectionType, bool>& _directionsOpen, 
		const bool _isFixed = false, const u_int& _size = 3);
private:
	void InitCases(const u_int& _size = 3);
	void UpdateVectorWithDirections();
	void ChangeOpenDirections(const RotateType& _rotateType);

public:
	void Rotate(const RotateType& _rotateType);
	void AddPlayer(Player _player);
	void RemovePlayer(Player _player);

public:
	friend ostream& operator<< (ostream& _stream, Tile _tile);
	inline bool operator == (const Card& _card) const;
};

