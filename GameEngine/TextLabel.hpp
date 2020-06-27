#pragma once
#include "Instance.hpp"
namespace Solar
{
	class TextLabel : public Instance
	{
	private:
		struct Properties
		{
			std::string Font;
			std::string Text;
			Udim2 Position;
			Udim2 Size;
			int TextSize;
			Color TextColor;
			float TextTransparency;
			Color StrokeColor;
			sf::Vector2f previousParentBounds;
			sf::Vector2f previousParentPosition;
		};
		struct EventBools 
		{
			bool Hovered = false;
			bool Pressed = false;
		};
		EventBools EventChecks;
		Properties Properties;
		bool _ValidFont;
	public:
		sf::Text _text;
		TextLabel()
		{
			this->Type = "TextLabel";
		}

		void Tick(float dt);
		void Render(float dt, sf::RenderTexture* target);
		bool Visible = true;

		void HandleEvents();

		Udim2 Position;
		Udim2 Size;
		Color TextColor = Color(0, 0, 0);
		float TextTransparency = 0;
		int TextSize = 20;
		Color StrokeColor = Color(0, 0, 0);
		std::string Font = "Roboto/Regular";
		std::string Text = "TextLabel";
		bool Trapped;
	};
}