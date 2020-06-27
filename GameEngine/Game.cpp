#include "Game.hpp"
#include "SplashState.hpp"
#include "MainMenu.hpp"
#include "DEBUG.hpp"
#include "Frame.hpp"
#include "SFMLEventHandler.hpp"
namespace Solar {
	extern struct Enums Enum;
	Game::Game(int width, int height, std::string title)
	{
		//Scenes
		Frame* Scenes = new Frame();
		Scenes->_body.setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
		Scenes->Visible = false;
		Scenes->Name = "Scenes";
		Enum.Game.emplace(1, Scenes);
		//Debug
		Frame* x_Debug = new Frame();
		x_Debug->_body.setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
		x_Debug->Visible = false;
		x_Debug->Name = "Debug";
		Enum.Game.emplace(2, x_Debug);
		Enum.Debug.Init();

		Enum.data.window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen);
		Enum.data.window.setFramerateLimit(60);
		Enum.data.DefaultView.setSize((sf::Vector2f)Enum.data.window.getSize());
		Enum.data.window.setView(Enum.data.DefaultView);
		Enum.data.window.setVerticalSyncEnabled(true);
		Enum.data.machine.AddState(StateRef(new SplashState()));

		this->Run();
	}

	void Game::Run() {
		float newTime, frameTime, interpolation;
		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;
		sf::RenderTexture* target = new sf::RenderTexture();
		target->create(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

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
				Enum.SFMLEVENTS.HandleEvents();
				Enum.data.input.HandleEvents();
				Enum.Debug.HandleEvents();
				Enum.data.machine.GetActiveState()->Game.HandleEvents();
				Enum.data.machine.GetActiveState()->Tick(dt);
				Enum.data.machine.GetActiveState()->Game.Tick(dt);
				Enum.Debug.Tick(dt);
				accumulator -= dt;
			}
			interpolation = accumulator / dt;
			Enum.data.window.clear();
			target->clear();

			//Rendering
			Enum.data.machine.GetActiveState()->Render(interpolation, target);
			Enum.data.window.setView(Enum.data.window.getDefaultView());
			Enum.data.machine.GetActiveState()->Game.Render(interpolation, target);
			Enum.data.window.setView(Enum.data.window.getDefaultView());
			Enum.Debug.Render(interpolation, target);
			Enum.data.window.setView(Enum.data.window.getDefaultView());
			target->display();
			Enum.data.window.draw(sf::Sprite(target->getTexture()));
			Enum.data.window.display();

		}
	}
}