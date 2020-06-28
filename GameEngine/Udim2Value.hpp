#pragma once
#include "Udim2.hpp"
#include "Instance.hpp"
namespace Solar
{
	class Udim2Value : public Instance
	{
	private:
		struct propertyChecks
		{
			Udim2 Value;
		};
		propertyChecks Properties;
	public:
		Udim2 Value;

		Udim2Value() {};
		//Instance Requirements
		void Render(float dt, sf::RenderTexture* target);
		void Tick(float dt);

		void HandleEvents();
	};
}
