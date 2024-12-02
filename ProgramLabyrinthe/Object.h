#pragma once
#include "Color.h"
struct Object
{
	char appearance;
	string color;

<<<<<<< Updated upstream
	Object(const char _appearance = '#', const string& _color = BROWN)
=======
	Object(const char _appearance, const string& _color)
>>>>>>> Stashed changes
	{
		appearance = _appearance;
		color = _color;
	}
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
	inline string GetAppearance(const bool _withColor = true) const
	{
		if (_withColor) return color + appearance;
		return to_string(appearance);
	}
};
