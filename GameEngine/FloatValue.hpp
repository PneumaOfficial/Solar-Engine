#pragma once
#include "Color.hpp"
#include "Instance.hpp"
namespace Solar
{
	class FloatValue : public Instance
	{
	private:
		struct propertyChecks
		{
			float Value;
		};
		propertyChecks Properties;
	public:
		float Value;

		FloatValue() {};
		//Instance Requirements
		void Render(float dt, sf::RenderTexture* target);
		void Tick(float dt);

		void HandleEvents();
	};
}
