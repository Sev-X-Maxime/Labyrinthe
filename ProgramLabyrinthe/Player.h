#pragma once
#include "Card.h"

class Player
{
	string name;
	Object pawn;
	vector<Card> card;
public:
	inline Object GetPawn() const
	{
		return pawn;
	}
	inline string GetName() const
	{
		return name;
	}
	inline bool HasCard() const
	{
		return card.empty();
	}
	inline Card GetCurrentCard() const
	{
		if (!HasCard()) throw exception("No card left !");
		return card[0];
	}
	inline void NextCard()
	{
		if (!HasCard()) throw exception("No card left !");
		card.erase(card.begin());
	}

public:
	Player(const string& _name, const Object& _pawn, const vector<Card>& _card);

};

