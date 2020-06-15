#include <sstream>
#include "SplashState.hpp"
#include "MainMenu.hpp"
#include <iostream>

namespace Solar {
	extern struct Enums Enum;
	SplashState::SplashState() : State("Game")
	{
		this->Game.Name = "Game";
	}

	void SplashState::Init() {
		Enum.data.assets.LoadTexture("EngineLogo", "Resources/SplashScreen/ENGINE.png");
		_background.setTexture(Enum.data.assets.GetTexture("EngineLogo"));
		sf::Texture engine = Enum.data.assets.GetTexture("EngineLogo");
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
		this->Game.Tick(dt);
		if (this->_clock.getElapsedTime().asSeconds() > 10) {
			Enum.data.machine.AddState(StateRef(new MainMenuState()), true);
		}
	}

	void SplashState::Render(float dt) {
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(400,400));
		sf::Texture tex = Enum.data.assets.GetTexture("EngineLogo");
		tex.setSmooth(true);
		rect.setTexture(&tex);
		Enum.data.window.draw(rect);
		Enum.data.window.draw(this->_background);
	}
}