#include "BoolValue.hpp"

namespace Solar
{
	void BoolValue::Render(float dt, sf::RenderTexture* target)
	{
		for (auto& x : this->children) {
			x.second->Render(dt, target);
		}
	}
	void BoolValue::Tick(float dt)
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

	void BoolValue::HandleEvents()
	{
		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}

}