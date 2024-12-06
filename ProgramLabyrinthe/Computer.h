#pragma once
#include "Entity.h"

class Computer : public Entity
{
public:
	Computer() = default;
	Computer(const string& _name, const Object& _pawn, const vector<Card>& _cards);
};

