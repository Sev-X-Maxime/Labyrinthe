#include "Card.h"

void Card::Display() const
{
	cout << treasure.color << treasure.appearance << RESET;
}
