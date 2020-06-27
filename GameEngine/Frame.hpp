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
			float BackgroundTransparency;
			float Rotation;
			Color BackgroundColor;
			float BorderSize;
			Color BorderColor;
			float BorderTransparency;
			sf::Vector2f previousParentBounds;
			sf::Vector2f previousParentPosition;
		};
		Events EventChecks;
		Properties PropertyChecks;
	public:
		bool shouldDrag = false;
		Vector2 offset;
		bool& Hovered = this->EventChecks.Hovered;
		bool& Pressed = this->EventChecks.Pressed;
		sf::View CurrentView;

		Frame();
		void Tick(float dt);
		void Render(float dt, sf::RenderTexture* target);
		bool Visible = true;

		void HandleEvents();

		Udim2 Size = Udim2();
		Udim2 Position = Udim2();
		float BackgroundTransparency = 0;
		Color BackgroundColor = Color();
		float BorderSize = 0;
		Color BorderColor = Color(0,0,0);
		float BorderTransparency = 0;
		bool ClipsDescendants;
		bool Trapped;
		bool BlurBackground;
		bool Draggable;
		Vector2 BlurOffsets;
	};
}

