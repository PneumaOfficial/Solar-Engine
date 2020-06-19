#include "SFMLEventHandler.h"
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
					Enum.data.input.FireEvent("ScrollUp");
				}
				else
				{
					Enum.data.input.FireEvent("ScrollDown");
				}

			default:
				break;
			}
		}
	}

}