#include "Game.hpp"
#include "SplashState.hpp"
#include "MainMenu.hpp"
#include "DEBUG.hpp"
#include "Frame.hpp"
namespace Solar {
	extern struct Enums Enum;
	Game::Game(int width, int height, std::string title)
	{
		//Scenes
		Frame* Scenes = new Frame();
		Scenes->_body.setSize(sf::Vector2f(Enum.Window.SCREEN_WIDTH, Enum.Window.SCREEN_HEIGHT));
		Scenes->Visible = false;
		Scenes->Name = "Scenes";
		Enum.Game.emplace(1, Scenes);
		//Debug
		Frame* x_Debug = new Frame();
		x_Debug->_body.setSize(sf::Vector2f(Enum.Window.SCREEN_WIDTH, Enum.Window.SCREEN_HEIGHT));
		x_Debug->Visible = false;
		x_Debug->Name = "Debug";
		Enum.Game.emplace(2, x_Debug);
		Enum.Debug.Init();

		Enum.data.window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		Enum.data.machine.AddState(StateRef(new SplashState()));
		this->Run();
	}

	void Game::Run() {
		float newTime, frameTime, interpolation;
		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (Enum.data.window.isOpen()) {
			Enum.data.machine.ProcessStateChanges();
			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;
			
			if (frameTime > 0.25f) {
				frameTime = 0.25f;
			}
			currentTime = newTime;
			accumulator += frameTime;
			
			while (accumulator >= dt) {
				Enum.data.machine.GetActiveState()->HandleInput();

				sf::Event Event;
				while (Enum.data.window.pollEvent(Event))
				{
					//Process SFML Events
					switch (Event.type)
					{
						case sf::Event::Resized:
						{
							/*sf::Vector2f newSize = (sf::Vector2f) Enum.data.window.getSize();
							Enum.Game.find(1)->second->_body.setSize(sf::Vector2f(Enum.data.window.getSize().x, Enum.data.window.getSize().y));
							Enum.Game.find(2)->second->_body.setSize(sf::Vector2f(Enum.data.window.getSize().x, Enum.data.window.getSize().y));*/
						}
					}
				}
				Enum.Debug.HandleEvents();
				Enum.data.machine.GetActiveState()->Game.HandleEvents();
				Enum.data.machine.GetActiveState()->Tick(dt);
				Enum.data.machine.GetActiveState()->Game.Tick(dt);
				Enum.Debug.Tick(dt);
				accumulator -= dt;
			}
			interpolation = accumulator / dt;
			Enum.data.window.clear();

			//Rendering
			Enum.data.machine.GetActiveState()->Render(interpolation);
			Enum.data.machine.GetActiveState()->Game.Render(interpolation);
			Enum.Debug.Render(interpolation);
			Enum.data.window.display();
		}
	}
}