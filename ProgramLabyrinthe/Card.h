#pragma once
#include "Object.h"

struct Card
{
	Object treasure;

	Card(const Object& _treasure)
	{
		treasure = _treasure;
	}

	void Display() const
	{
		cout << treasure.GetAppearance() << RESET;
	}

};

