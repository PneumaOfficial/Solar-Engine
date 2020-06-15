#pragma once
#include <SFML/Graphics.hpp>
namespace Solar {
	class CollisionCheck {
	public:
		CollisionCheck() {};
		~CollisionCheck() {};

		bool areRectsColliding(sf::RectangleShape object1, sf::RectangleShape object2, sf::RenderWindow& window);

	};
}