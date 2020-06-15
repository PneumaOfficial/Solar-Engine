#pragma once
namespace Solar
{
	class Color
	{
	private:
		int Red = 255;
		int Green = 255;
		int Blue = 255;
	public:
		Color();
		Color(int Red, int Green, int Blue);
		int getRed();
		int getGreen();
		int getBlue();

		friend bool operator== (const Color& c1, const Color& c2);
		friend bool operator!= (const Color& c1, const Color& c2);
	};
}

