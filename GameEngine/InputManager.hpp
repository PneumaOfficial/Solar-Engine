#pragma once
#include <SFML/Graphics.hpp>

namespace Solar {
	struct InputManager {

		bool IsSpriteClick(sf::Sprite object, sf::Mouse::Button button);
		bool IsTextClicked(sf::Text object, sf::Mouse::Button button);
		bool IsRectHovered(sf::RectangleShape);
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);

	};
}