#pragma once
#include "Card.h"
class Entity
{
protected:
	string name;
	Object pawn;
	vector<Card> cards;
	pair<u_int, u_int> position;

public:
	virtual inline Object GetPawn() const
	{
		return pawn;
	}
	virtual inline string GetName() const
	{
		return name;
	}
	virtual inline bool HasCard() const
	{
		return cards.size() > 0;
	}
	virtual inline Card GetCurrentCard() const
	{
		if (!HasCard()) throw exception("No card left !");
		return cards[0];
	}
	virtual inline void NextCard()
	{
		if (!HasCard()) throw exception("No card left !");
		cards.erase(cards.begin());
	}
	virtual inline u_int GetCardLeft() const
	{
		return static_cast<u_int>(cards.size());
	}
	virtual inline pair<u_int, u_int> GetPosition() const
	{
		return position;
	}
	virtual inline void SetPosition(const pair<u_int, u_int>& _position)
	{
		position = _position;
	}

public:
	Entity(string _name, Object _pawn, vector<Card> _cards);
};

