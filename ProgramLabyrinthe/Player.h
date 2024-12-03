#pragma once
#include "Card.h"

class Player
{
	string name;
	Object pawn;
	vector<Card> cards;
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
		return cards.size() > 0;
	}
	inline Card GetCurrentCard() const
	{
		if (!HasCard()) throw exception("No card left !");
		return cards[0];
	}
	inline void NextCard()
	{
		if (!HasCard()) throw exception("No card left !");
		cards.erase(cards.begin());
	}

public:
	Player() = default;
	Player(const string& _name, const Object& _pawn, const vector<Card>& _cards);
};

