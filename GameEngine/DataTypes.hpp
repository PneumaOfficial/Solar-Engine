#pragma once
namespace Solar
{
	struct Vector2
	{
		float x = 0.0f;
		float y = 0.0f;
		friend bool operator== (const Vector2& c1, const Vector2& c2)
		{
			return 
			(
				c1.x == c2.x &&
				c1.y == c2.y
			);
		}
		friend bool operator!= (const Vector2& c1, const Vector2& c2)
		{
			return (c1 == c2);
		}
	};
}
#include "Udim2.hpp"
#include "Color.hpp"