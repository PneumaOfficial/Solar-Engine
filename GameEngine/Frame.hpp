#pragma once
#include "Instance.hpp"

namespace Solar {
	class Frame : public Instance
	{
		struct Events
		{
			bool Hovered;
			bool Pressed;
		};
		struct Properties
		{
			Udim2 Position;
			Udim2 Size;
			int BackgroundTransparency;
			float Rotation;
			Color BackgroundColor;
			int BorderSize;
			Color BorderColor;
			int BorderTransparency;
			sf::Vector2f previousParentBounds;
			sf::Vector2f previousParentPosition;
		};
		Events EventChecks;
		Properties PropertyChecks;
	public:
		Frame()
		{
			this->Type = "Frame";
			this->Size = Udim2(0.0f, 50.0f, 0.0f, 50.0f);
			this->Position = Udim2();
		};
		void AddChild(Instance* child);
		void Tick(float dt);
		void Render(float dt);
		bool Visible = true;

		void HandleEvents();
		void HookEvent(std::string Event, std::function<void(Instance * frame)> function);
		void FireEvent(std::string Event);

		Udim2 Size = Udim2();
		Udim2 Position = Udim2();
		int Transparency = 0;
		Color BackgroundColor = Color();
		float BorderSize = 10;
	};
}

