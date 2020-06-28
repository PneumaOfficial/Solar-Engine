#pragma once
#include "Color.hpp"
#include "Instance.hpp"
namespace Solar
{
	class Color3Value : public Instance
	{
	private:
		struct propertyChecks
		{
			Color Value;
		};
		propertyChecks Properties;
	public:
		Color Value;

		Color3Value() {};
		//Instance Requirements
		void Render(float dt, sf::RenderTexture* target);
		void Tick(float dt);

		void HandleEvents();
	};
}
