#pragma once
#include "Instance.hpp"
namespace Solar
{
	class StringValue : public Instance
	{
	private:
		struct propertyChecks
		{
			std::string Value;
		};
		propertyChecks Properties;
	public:
		std::string Value;

		StringValue() {};
		//Instance Requirements
		void Render(float dt, sf::RenderTexture* target);
		void Tick(float dt);

		void HandleEvents();
	};
}
