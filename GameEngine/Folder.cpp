
#include "Folder.hpp"
#include <iostream>
namespace Solar {
	extern struct Enums Enum;

	void Folder::Tick(float dt){
		if (this->Parent.get() == nullptr)
		{
			return;
		}
		if (this->Enabled) {
			if (this->_body.getSize() != this->Parent->_body.getSize() || this->_body.getPosition() != this->Parent->_body.getPosition())
			{
				this->_body.setPosition(this->Parent->_body.getPosition());
				this->_body.setSize(this->Parent->_body.getSize());
			}
			/*for (auto& x : this->children) {
				x.second->Tick(dt);
			}*/
			for (int i = 0; i != this->children.size(); i++) {
				this->children[i]->HandleEvents();
			}
		}
	}
	void Folder::Render(float dt, sf::RenderTexture* target) {
		if (this->Enabled) {
			/*for (auto& x : this->children) {
				x.second->Render(dt, target);
			}*/
			for (int i = 0; i != this->children.size(); i++) {
				auto& Selected = this->children[i];
				if (Selected->Type == "Folder")
				{
					Selected->_body.setPosition(this->_body.getPosition());
					Selected->_body.setSize(this->_body.getSize());
				}
				Selected->Render(dt, target);
			}
		}
	}
	void Folder::HandleEvents()
	{
		//Events
		/*for (auto& x : this->children) {
			x.second->HandleEvents();
		}*/
		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->HandleEvents();
		}
	}
}