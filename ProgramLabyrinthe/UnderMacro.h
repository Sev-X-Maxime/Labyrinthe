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
