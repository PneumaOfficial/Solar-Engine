#include "Color3Value.hpp"

namespace Solar
{
	void Color3Value::Render(float dt, sf::RenderTexture* target)
	{
		for (auto& x : this->children) {
			x.second->Render(dt, target);
		}
	}
	void Color3Value::Tick(float dt)
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

	void Color3Value::HandleEvents()
	{
		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}

}