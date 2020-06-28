#pragma once
#include "DataTypes.hpp"
#include "Instance.hpp"
namespace Solar
{
	class Vector2Value : public Instance
	{
	private:
		struct propertyChecks
		{
			Vector2 Value;
		};
		propertyChecks Properties;
	public:
		Vector2 Value;

		Vector2Value() {};
		//Instance Requirements
		void Render(float dt, sf::RenderTexture* target);
		void Tick(float dt);

		void HandleEvents();
	};
}
