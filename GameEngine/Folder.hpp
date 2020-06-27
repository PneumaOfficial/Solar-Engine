#pragma once
#include "Instance.hpp"

namespace Solar {

	class Folder : public Instance {
		struct EventBools {};
		EventBools EventChecks;
	public:
		Folder()
		{
			this->Type = "Folder";
		};
		void Tick(float dt);
		void Render(float dt, sf::RenderTexture* target);

		void HandleEvents();
	};
};