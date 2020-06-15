#pragma once
#include <SFML/Graphics.hpp>
#include "Folder.hpp"
#include "State.hpp"
#include "Game.hpp"

namespace Solar {
	class SplashState : public State {
	public:
		SplashState();
		void Init();
		void HandleInput();
		void Tick(float dt);
		void Render(float dt);
		void Resume() {};
		void Pause() {};
	private:
		sf::Clock _clock;
		sf::Sprite _background;
	};
}

