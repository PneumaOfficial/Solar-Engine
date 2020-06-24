#pragma once
#include "Folder.hpp"
namespace Solar {
	class State {
	public:
		State(std::string Name) 
		{
			this->Game = Folder();
			this->Game.Name = Name;
		};
		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Render(float dt, sf::RenderTexture* target) = 0;
		virtual void Tick(float dt) = 0;
		virtual void Resume() = 0;
		virtual void Pause() = 0;
		Folder Game;
	};
}