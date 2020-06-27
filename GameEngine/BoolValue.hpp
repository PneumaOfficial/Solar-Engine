#pragma once

#include "Instance.hpp"
namespace Solar
{
	class BoolValue : public Instance
	{
	private:
		struct propertyChecks
		{
			bool Value;
		};
		propertyChecks Properties;
	public:
		bool Value;

		//Instance Requirements
		void Render(float dt, sf::RenderTexture* target);
		void Tick(float dt);

		void HandleEvents();
	};
}
