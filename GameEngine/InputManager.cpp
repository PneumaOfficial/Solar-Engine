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
	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}

	void InputManager::HandleEvents()
	{
		
	}

	void InputManager::HookEvent(std::string Event, std::function<void()> function)
	{
		EventStruct fun;
		fun.StoredFunction = function;
		fun.EventName = Event;
		this->EventQueue.emplace(this->EventQueue.size() + 1, fun);
	}
	void InputManager::FireEvent(std::string Event)
	{
		for (auto& x : this->EventQueue)
			if (x.second.EventName == Event)
				x.second.StoredFunction();
	}
}