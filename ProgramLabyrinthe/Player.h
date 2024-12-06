#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player() = default;
	Player(const string& _name, const Object& _pawn, const vector<Card>& _cards);
};

