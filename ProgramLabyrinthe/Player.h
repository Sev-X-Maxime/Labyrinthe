#pragma once
#include "Card.h"

class Player
{
	string name;
	Object pawn;
	vector<Card> cards;
	pair<u_int, u_int> position;

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
	inline u_int GetCardLeft() const
	{
		return static_cast<u_int>(cards.size());
	}
	inline pair<u_int, u_int> GetPosition() const
	{
		return position;
	}
	inline void SetPosition(const pair<u_int, u_int>& _position)
	{
		position = _position;
	}
public:
	Player() = default;
	Player(const string& _name, const Object& _pawn, const vector<Card>& _cards);
};

