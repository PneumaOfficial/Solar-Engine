#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "State.hpp"

namespace Solar {
	class MainMenuState : public State {
	public:
		MainMenuState();
		void Init();
		void HandleInput();
		void Tick(float dt);
		void Render(float dt);
		void Resume() {};
		void Pause() {};
	private:
		sf::Sprite _background;
		sf::Text _play;
		sf::Sprite _options;
		sf::Sprite _about;
		sf::Sprite _quit;
	};
}