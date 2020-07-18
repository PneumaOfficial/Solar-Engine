#include <sstream>
#include <iostream>
#include "MainMenu.hpp"
#include "DEFINTIONS.hpp"
namespace Solar {
	extern struct Enums Enum;
	MainMenuState::MainMenuState() : State() {}

	void MainMenuState::Init(){}
	void MainMenuState::HandleInput(){}
	void MainMenuState::Tick(float dt){}
	void MainMenuState::Render(float dt, sf::RenderTexture* target){}
}
