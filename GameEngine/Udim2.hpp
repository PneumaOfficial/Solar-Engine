#pragma once
#include <SFML/Graphics.hpp>

//Class
class Udim2
{
private:
	struct _x {
		float scale;
		float offset;
	};
	struct _y {
		float scale;
		float offset;
	};
public:
	struct _x x;
	struct _y y;
	Udim2();
	Udim2(float x_scale, float x_offset, float y_scale, float y_offset);
	Udim2(int param[]);

	//Operators
	friend bool operator== (const Udim2& c1, const Udim2& c2);
	friend bool operator!= (const Udim2& c1, const Udim2& c2);
};

