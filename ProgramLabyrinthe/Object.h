#pragma once
#include "Color.h"
struct Object
{
	string appearance;
	string color;

	Object(const string& _appearance = "\xF0\x9F\xA7\xB1", const string& _color = BROWN)
	{
		appearance = _appearance;
		color = _color;
	}
	inline string GetAppearance(const bool _withColor = true) const
	{
		if (_withColor) return color + appearance + RESET;
		return appearance;
	}

	inline bool operator == (const Object& _other) const
	{
		return GetAppearance() == _other.GetAppearance();
	}
	inline bool operator == (const string& _appearance) const
	{
		return appearance == _appearance;
	}
};
