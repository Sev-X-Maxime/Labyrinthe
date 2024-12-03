#pragma once
#include "Color.h"
struct Object
{
	char appearance;
	string color;

	Object(const char _appearance = '#', const string& _color = BROWN)
	{
		appearance = _appearance;
		color = _color;
	}
	inline string GetAppearance(const bool _withColor = true) const
	{
		if (_withColor) return color + appearance;
		return to_string(appearance);
	}

	inline bool operator == (const Object& _other) const
	{
		return GetAppearance() == _other.GetAppearance();
	}
	inline void operator = (const Object& _other)
	{
		appearance = _other.appearance;
		color = _other.color;
	}
};
