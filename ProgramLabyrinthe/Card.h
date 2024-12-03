#pragma once
#include "Object.h"

struct Card
{
	Object treasure;

	Card()
	{

	}

	void Display() const
	{
		cout << treasure.GetAppearance() << RESET;
	}

};

