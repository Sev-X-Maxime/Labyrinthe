#include "Player.h"

Player::Player(const string& _name, const Object& _pawn, const vector<Card>& _cards)
{
	name = _name;
	pawn = _pawn;
	cards = _cards;
}
