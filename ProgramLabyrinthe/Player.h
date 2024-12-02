#pragma once
#include "Card.h"

class Player
{
	string name;
	Object pawn;
	vector<Card> card;

	Player(const string& _name, const Object& _pawn, const vector<Card>& _card);
};

