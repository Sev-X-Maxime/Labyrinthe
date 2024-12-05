#pragma once
#include "Object.h"
#include "FileStream.h"
using namespace Tools;

struct Card
{
	Object treasure;

	Card(const Object& _treasure)
	{
		treasure = _treasure;
	}
	inline u_int GetSize() const
	{
		FileStream _file = FileStream("CardAspect.txt");
		return static_cast<u_int>(_file.ComputeLineOfFile());
	}
	string ToStringLine(const u_int& _lineIndex, const bool _returnLineDisplayable = true) const
	{
		FileStream _file = FileStream("CardAspect.txt");
		string _line, _lineToDisplay;
		_line = _file.ReadLine(_lineIndex);
		if (!_returnLineDisplayable) return _line;
		const u_int& _lineSize = static_cast<u_int>(_line.size());
		char _currentChar;
		for (u_int _index = 0; _index < _lineSize; _index++)
		{
			_currentChar = _line[_index];
			switch (_currentChar)
			{
			case '@':
				_lineToDisplay += BLUE + 
					string(SWAP) + HIDDEN_TEXT;
				break;
			case '.':
				_lineToDisplay += YELLOW_BASE + 
					string(SWAP) + HIDDEN_TEXT;
				break;
				break;
			case '0':
				_lineToDisplay += WHITE_INTENSE_BG 
					+ treasure.GetAppearance() + RESET;
				continue;
			case '_':
				_lineToDisplay += WHITE_INTENSE_TEXT + 
					string(SWAP) + HIDDEN_TEXT;
			default:
				break;
			}
			_lineToDisplay += _currentChar;
			_lineToDisplay += RESET;

		}
		return _lineToDisplay;

	}
	string ToString(const bool _returnLineDisplayable = true) const
	{
		string _textToReturn;
		FileStream _file = FileStream("CardAspect.txt");
		const u_int& _lineCount = static_cast<u_int>(_file.ComputeLineOfFile());
		for (u_int _index = 0; _index < _lineCount; _index++)
		{
			_textToReturn +=
				ToStringLine(_index, _returnLineDisplayable);
			_textToReturn += "\n";
		}
		return _textToReturn;
	}

	void Display() const
	{
		cout << ToString();
	}
};

