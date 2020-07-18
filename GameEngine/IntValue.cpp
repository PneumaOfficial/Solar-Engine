#include "IntValue.hpp"

namespace Solar
{
	void IntValue::Render(float dt, sf::RenderTexture* target){}
	void IntValue::Tick(float dt)
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

	void IntValue::HandleEvents()
	{
		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->HandleEvents();
		}
	}

}