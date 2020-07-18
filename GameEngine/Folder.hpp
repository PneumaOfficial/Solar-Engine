#pragma once
#include "Instance.hpp"

namespace Solar {

	class Folder : public Instance {
		struct EventBools {};
		EventBools EventChecks;
	public:
		void Tick(float dt);
		void Render(float dt, sf::RenderTexture* target);
		Folder()
		{
			this->Type = "Folder";
		};
		void HandleEvents();
	};
	auto CreateFolder()
	{
		return std::make_unique<Folder>();
	}
};