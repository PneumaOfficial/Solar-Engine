#include <sstream>
#include "SplashState.hpp"
#include "MainMenu.hpp"
#include <iostream>

namespace Solar {
	extern struct Enums Enum;
	SplashState::SplashState() : State() {};

	void SplashState::Init() {
		
	}

	void SplashState::HandleInput() {
		sf::Event event;

		while (Enum.data.window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				Enum.data.window.close();
			}
		}
	}

	void SplashState::Tick(float dt) {
		//this->Game.Tick(dt);
		/*if (this->_clock.getElapsedTime().asSeconds() > 10) {
			Enum.data.machine.AddState(StateRef(new MainMenuState()), true);
		}*/
		Enum.data.machine.AddState(StateRef(new MainMenuState()), true);
	}

	void SplashState::Render(float dt, sf::RenderTexture* target) {
		
	}
}