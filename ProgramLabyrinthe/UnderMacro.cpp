#include "UnderMacro.h"

string GetLine(const string& _question)
{
	DISPLAY(_question, _question.empty() ? false : true)
		string _line = string();
	bool _wantToQuit;
	do
	{
		const int _charASCII = getchar();
		_wantToQuit = _charASCII == EOF || _charASCII == '\n';

		if (!_wantToQuit)
		{
			_line += char(_charASCII);
		}

	} while (!_wantToQuit);

	return _line;
}

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
