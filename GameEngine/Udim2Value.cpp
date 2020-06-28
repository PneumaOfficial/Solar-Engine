#include "Udim2Value.hpp"

namespace Solar
{
	void Udim2Value::Render(float dt, sf::RenderTexture* target)
	{
		for (auto& x : this->children) {
			x.second->Render(dt, target);
		}
	}
	void Udim2Value::Tick(float dt)
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

	void Udim2Value::HandleEvents()
	{
		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}

}