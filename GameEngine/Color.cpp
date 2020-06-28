#include "Color.hpp"

namespace Solar
{
	Color::Color(){}

	Color::Color(int Red, int Green, int Blue)
	{
		this->Red = Red;
		this->Green = Green;
		this->Blue = Blue;
	}

	int Color::getRed()
	{
		return this->Red;
	}
	int Color::getGreen()
	{
		return this->Green;
	}
	int Color::getBlue()
	{
		return this->Blue;
	}

	//Operators
	bool operator== (const Color& c1, const Color& c2)
	{
		return	(
				(c1.Red == c2.Red) &&
				(c1.Blue == c2.Blue) &&
				(c1.Green == c2.Green)
				);
	}

	bool operator!= (const Color& c1, const Color& c2)
	{
		return (c1 == c2);
	}

}
