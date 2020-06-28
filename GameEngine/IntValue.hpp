#pragma once
#include "Instance.hpp"
namespace Solar
{
	class IntValue : public Instance
	{
	private:
		struct propertyChecks
		{
			int Value;
		};
		propertyChecks Properties;
	public:
		int Value;

		IntValue() {};
		//Instance Requirements
		void Render(float dt, sf::RenderTexture* target);
		void Tick(float dt);

		void HandleEvents();
	};
}
