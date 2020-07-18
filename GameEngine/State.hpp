#pragma once
#include "Folder.hpp"
#include "Frame.hpp"
namespace Solar {
	class State {
	public:
		State()
		{
			this->Scene = CreateFolder();

			//Game Objects
			auto Workspace = CreateFolder();
			Workspace->Name = "Workspace";
			Workspace->setParent(std::move(this->Scene));
			//Gui
			auto ScreenGUI = CreateFolder();
			ScreenGUI->Name = "ScreenGUI";
			ScreenGUI->setParent(std::move(this->Scene));
		}

		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Render(float dt, sf::RenderTexture* target) = 0;
		virtual void Tick(float dt) = 0;
		virtual void Resume() = 0;
		virtual void Pause() = 0;
		std::unique_ptr<Instance> Scene;
	};
}