#pragma once
#include "Macro.h"
template <typename Type>
Type GetInput(const string& _question = "Que souhaitez-vous ?", const string& _answerAsker = "Réponse : ")
{
	Type _answer;
	bool _isValid;

	DISPLAY(_question, true);
	do
	{
		DISPLAY(_answerAsker, false);
		cin >> _answer;
		_isValid = cin.good();
		CLEAR_CIN;
		CLEAR_SCREEN;

	} while (!_isValid);

	return _answer;
}
string GetLine(const string& _question);
void DisplayRanbow(const string& _text)
{
	const vector<string>& _everyColor =
	{
		WHITE,
		DARK_RED,
		RED ,
		DARK_ORANGE ,
		ORANGE,
		DARK_YELLOW,
		YELLOW,
		LIME,
		GREEN,
		BLUE,
		LIGHT_BLUE,
		CYAN,
		PINK,
		MAGENTA,
		PURPLE,
		BROWN,
	};
	u_int _colorCount = static_cast<u_int>(_everyColor.size() - 1);
	u_int _indexColor = 0;
	while (!_kbhit())
	{
		for (char _currentChar : _text)
		{
			cout << _everyColor[_indexColor] << _currentChar;
			_indexColor = _indexColor > _colorCount ? 0 : _indexColor++;
		}

	}
}