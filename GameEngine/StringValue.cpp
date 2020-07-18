#include "StringValue.hpp"

namespace Solar
{
	void StringValue::Render(float dt, sf::RenderTexture* target){}
	void StringValue::Tick(float dt)
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

	void StringValue::HandleEvents()
	{
		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->HandleEvents();
		}
	}

}