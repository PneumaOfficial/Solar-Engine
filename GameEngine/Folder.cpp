
#include "Folder.hpp"
#include <iostream>
namespace Solar {
	extern struct Enums Enum;

	void Folder::Tick(float dt){
		//TODO: Parents
		/*if (this->Parent != this->PreviousParent)
		{
			std::cout << "PARENT CHANGE!" << std::endl;
			this->Parent->AddChild(this);
			this->PreviousParent = this->Parent;
		}*/
		if (this->Parent == nil)
		{
			return;
		}
		if (this->Enabled) {
			if (this->_body.getSize() != this->Parent->_body.getSize() || this->_body.getPosition() != this->Parent->_body.getPosition())
			{
				this->_body.setPosition(this->Parent->_body.getPosition());
				this->_body.setSize(this->Parent->_body.getSize());
			}
			for (auto& x : this->children) {
				x.second->Tick(dt);
			}
		}
	}
	void Folder::Render(float dt, sf::RenderTexture* target) {
		if (this->Enabled) {
			for (auto& x : this->children) {
				x.second->Render(dt, target);
			}
		}
	}

	void Folder::HandleEvents()
	{
		//Events
		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}
}