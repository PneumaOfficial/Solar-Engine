#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace Solar {
	struct InputManager {
	private:
		struct Events
		{
			bool Hovered;
			bool Pressed;
		};
		struct EventStruct
		{
			std::string EventName;
			std::function<void()> StoredFunction;
		};

	public:
		bool IsSpriteClick(sf::Sprite object, sf::Mouse::Button button);
		bool IsTextClicked(sf::Text object, sf::Mouse::Button button);
		bool IsRectHovered(sf::RectangleShape);
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);

		std::map<int, EventStruct> EventQueue;
		void HandleEvents();
		void FireEvent(std::string Event);
		void HookEvent(std::string Event, std::function<void()> function);

	};
}