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
		void AddChild(Instance* child);
		void Tick(float dt);
		void Render(float dt);

		void HandleEvents();
		void HookEvent(std::string Event, std::function<void()> function);
		void FireEvent(std::string Event);
	};
};