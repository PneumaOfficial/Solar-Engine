#include "Vector2Value.hpp"

namespace Solar
{
	void Vector2Value::Render(float dt, sf::RenderTexture* target){}

	void Vector2Value::Tick(float dt)
	{

		if (this->Value != this->Properties.Value)
		{

			this->FireEvent("ValueChanged");
			this->Properties.Value = this->Value;
		}

		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->Tick(dt);
		}
	}

	void Vector2Value::HandleEvents()
	{
		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->HandleEvents();
		}
	}

}