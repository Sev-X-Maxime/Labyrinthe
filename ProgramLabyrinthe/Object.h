#pragma once
#include "Color.h"

struct Object
{
	char appearance;
	string color;

	inline string GetAppearance(const bool _withColor = true) const
	{
		if (_withColor)
		{
			return color + appearance;
		}
		else
		{
			return to_string(appearance);
		}
	}
};