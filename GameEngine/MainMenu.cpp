#include <sstream>
#include <iostream>
#include "MainMenu.hpp"
#include "DEFINTIONS.hpp"
namespace Solar {
	extern struct Enums Enum;
	MainMenuState::MainMenuState() : State("Game") {
		this->Game.Name = "Workspace";

		//Game Objects
		Folder* Workspace = new Folder();
		Workspace->Name = "Workspace";
		this->Game.AddChild(Workspace);

		//Gui
		Folder* ScreenGUI = new Folder();
		ScreenGUI->Name = "ScreenGUI";
		this->Game.AddChild(ScreenGUI);
		
		//Editor
		Folder* Editor = new Folder();
		Editor->Name = "Workspace";
		this->Game.AddChild(Editor);

	}
	void MainMenuState::Init()
	{

		//this->_data->assets.LoadTexture("Background", "Resources/MainMenu/background.png");
		Enum.data.assets.LoadFont("arial", Enum.FontDir.Arial);
		this->_play = sf::Text("Play", Enum.data.assets.GetFont("arial"));
		this->_play.setPosition((Enum.Window.SCREEN_WIDTH / 2) - this->_play.getGlobalBounds().width / 2, (Enum.Window.SCREEN_HEIGHT / 2) - this->_play.getGlobalBounds().height / 2);


	}
	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (Enum.data.window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				Enum.data.window.close();
			}

			if (Enum.data.input.IsTextClicked(this->_play, sf::Mouse::Left)) {
				
			}
		}
	}
	void MainMenuState::Tick(float dt)
	{

	}
	void MainMenuState::Render(float dt, sf::RenderTexture* target)
	{
		target->draw(this->_play);
	}
}