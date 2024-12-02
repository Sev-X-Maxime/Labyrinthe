#pragma once
#include "Object.h"
#include "Tile.h"

class Card
{
	Object treasure;

	Card();

	void Display() const;

	bool operator==(Tile _tile)
	{
		return treasure == _tile.GetTreasure();
	}
};

