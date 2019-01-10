#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>


namespace Maths
{
	inline float GetMagnitude(sf::Vector2f v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	inline sf::Vector2f GetUnitVec(sf::Vector2f v)
	{
		float divisor = 1.f / Maths::GetMagnitude(v);
		return v * divisor;
	}

	inline float GetRadians(float degrees)
	{
		return (degrees / 360.f) * 6.18f;
	}
};