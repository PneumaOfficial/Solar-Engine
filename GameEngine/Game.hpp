#pragma once


#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "DEFINTIONS.hpp"

namespace Solar {

	class Game {
	public:
		Game(int width, int height, std::string title);
	
	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		void Run();

	};

}