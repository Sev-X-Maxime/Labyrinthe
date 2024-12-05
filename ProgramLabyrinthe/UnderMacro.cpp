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