#include "StringValue.hpp"

namespace Solar
{
	void StringValue::Render(float dt, sf::RenderTexture* target)
	{
		for (auto& x : this->children) {
			x.second->Render(dt, target);
		}
	}
	void StringValue::Tick(float dt)
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

	void StringValue::HandleEvents()
	{
		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}

}