#include "InputManager.hpp"
#include "DEFINTIONS.hpp"
namespace Solar {
	//Sprite Click
	extern struct Enums Enum;
	bool Solar::InputManager::IsSpriteClick(sf::Sprite object, sf::Mouse::Button button)
	{
		if (sf::Mouse::isButtonPressed(button)) {
			sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
			if (tempRect.contains(sf::Mouse::getPosition(Enum.data.window))) {
				return true;
			}
		}
		return false;
	}
	//Text Clicked
	bool InputManager::IsTextClicked(sf::Text object, sf::Mouse::Button button)
	{
		if (sf::Mouse::isButtonPressed(button)) {
			sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
			if (tempRect.contains(sf::Mouse::getPosition(Enum.data.window))) {
				return true;
			}
		}
		return false;
	}

	bool InputManager::IsRectHovered(sf::RectangleShape object)
	{
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (tempRect.contains(sf::Mouse::getPosition(Enum.data.window))) {
			return true;
		}
		return false;
	}

	//GetPosition
	sf::Vector2i Solar::InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
}