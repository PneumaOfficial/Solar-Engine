#include "SFMLEventHandler.hpp"
#include "DEFINTIONS.hpp"

namespace Solar
{
	extern struct Enums Enum;

	void SFMLEventHandler::HandleEvents()
	{
		sf::Event event;
		while (Enum.data.window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				Enum.data.window.close();

			case event.MouseWheelScrolled:
				if (event.mouseWheelScroll.delta > 0)
				{
					Enum.Mouse.FireEvent("ScrollUp");
				}
				else
				{
					Enum.Mouse.FireEvent("ScrollDown");
				}

			case event.MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					Enum.Mouse._Buttons.Left = true;
					Enum.Mouse.FireEvent("LeftDown");

				case sf::Mouse::Button::Right:
					Enum.Mouse._Buttons.Right = true;
					Enum.Mouse.FireEvent("RightDown");

				case sf::Mouse::Button::Middle:
					Enum.Mouse._Buttons.Middle = true;
					Enum.Mouse.FireEvent("MiddleDown");

				default:
					break;
				}
				
			case event.MouseButtonReleased:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					Enum.Mouse._Buttons.Left = false;
					Enum.Mouse.FireEvent("LeftReleased");

				case sf::Mouse::Button::Right:
					Enum.Mouse._Buttons.Right = false;
					Enum.Mouse.FireEvent("RightReleased");

				case sf::Mouse::Button::Middle:
					Enum.Mouse._Buttons.Middle = false;
					Enum.Mouse.FireEvent("MiddleReleased");

				default:
					break;
				}

			case event.MouseMoved:
				sf::Vector2i xPos = sf::Mouse::getPosition();
				Vector2 Position;
				Position.x = xPos.x;
				Position.y = xPos.y;
				Enum.Mouse._Position = Position;
				Enum.data.input.FireEvent("MouseMoved");

			default:
				break;
			}
		}
	}

}