#include "Player.h"

Player::Player(const string& _name, const Object& _pawn, const vector<Card>& _card)
{
	name = _name;
	pawn = _pawn;
	card = _card;
}
