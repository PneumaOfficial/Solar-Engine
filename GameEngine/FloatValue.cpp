#include "FloatValue.hpp"

namespace Solar
{
	void FloatValue::Render(float dt, sf::RenderTexture* target)
	{
		for (auto& x : this->children) {
			x.second->Render(dt, target);
		}
	}
	void FloatValue::Tick(float dt)
	{

		if (this->Value != this->Properties.Value)
		{

			this->FireEvent("ValueChanged");
			this->Properties.Value = this->Value;
		}

		for (auto& x : this->children) {
			x.second->Tick(dt);
		}
	}

	void FloatValue::HandleEvents()
	{
		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}

}