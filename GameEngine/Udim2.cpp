#include "Udim2.hpp"

Udim2::Udim2()
{
	this->x.scale = 0.0f;
	this->x.offset = 0.0f;
	this->y.scale = 0.0f;
	this->y.offset = 0.0f;
}

Udim2::Udim2(float x_scale, float x_offset, float y_scale, float y_offset)
{
	this->x.scale = x_scale;
	this->x.offset = x_offset;
	this->y.scale = y_scale;
	this->y.offset = y_offset;
}


//Operators

bool operator== (const Udim2& c1, const Udim2& c2)
{
	return ((	c1.x.scale && c2.x.scale	) &&
			(	c1.x.offset && c2.x.offset	)&&
			(	c1.y.scale && c2.y.scale	)	&&
			(	c1.y.offset && c2.y.offset	)
			);
}

bool operator!= (const Udim2& c1, const Udim2& c2)
{
	return !(c1 == c2);
}
