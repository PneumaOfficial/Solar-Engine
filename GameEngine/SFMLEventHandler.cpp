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
			{
				Enum.data.window.close();
				break;
			}
			
			case event.MouseWheelScrolled:
			{
				if (event.mouseWheelScroll.delta > 0)
				{
					Enum.Mouse.FireEvent("ScrollUp");
				}
				else
				{
					Enum.Mouse.FireEvent("ScrollDown");
				}
				break;
			}

			case event.MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					Enum.Mouse._buttons.Left = true;
					Enum.Mouse.FireEvent("LeftDown");
					break;

				case sf::Mouse::Button::Right:
					Enum.Mouse._buttons.Right = true;
					Enum.Mouse.FireEvent("RightDown");
					break;

				case sf::Mouse::Button::Middle:
					Enum.Mouse._buttons.Middle = true;
					Enum.Mouse.FireEvent("MiddleDown");
					break;

				default:
					break;
				}
				break;
			}
				
			case event.MouseButtonReleased:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					Enum.Mouse._buttons.Left = false;
					Enum.Mouse.FireEvent("LeftUp");
					break;

				case sf::Mouse::Button::Right:
					Enum.Mouse._buttons.Right = false;
					Enum.Mouse.FireEvent("RightUp");
					break;

				case sf::Mouse::Button::Middle:
					Enum.Mouse._buttons.Middle = false;
					Enum.Mouse.FireEvent("MiddleUp");
					break;

				default:
					break;
				}
				break;
			}

			case event.MouseMoved:
			{
				sf::Vector2i xPos = sf::Mouse::getPosition(Enum.data.window);
				Vector2 Position;
				Position.x = xPos.x;
				Position.y = xPos.y;
				Enum.Mouse._position = Position;
				Enum.Mouse.FireEvent("MouseMoved");
				break;
			}

			default:
				break;
			}
		}
	}

}