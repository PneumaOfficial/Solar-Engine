#include "Sound.hpp"
#include "DEFINTIONS.hpp"
namespace Solar
{
	extern struct Enums Enum;
	SoundObject::SoundObject()
	{
	}
	void SoundObject::Pause()
	{
		this->_sound->pause();
	}
	void SoundObject::Resume()
	{
		std::cout << "Should be playing: " << this->handler->ActiveSounds.size() << " sounds playing." << std::endl;
		this->_sound->play();

	}

	void SoundObject::Stop()
	{
		if(this != nullptr)
			this->_sound->stop();
	}

	SoundHandler::SoundHandler() 
	{
		this->Type = "SoundEffect";
	}
	std::shared_ptr<SoundObject> SoundHandler::Play()
	{
		std::shared_ptr<SoundObject> returning = std::make_shared<SoundObject>(SoundObject());
		returning->handler = this;
		returning->ID = this->ActiveSounds.size() + 1;
		this->ActiveSounds[returning->ID] = returning;
		if (Enum.data.assets.LoadBuffer(this->FilePath))
		{
			returning->_sound->setBuffer(Enum.data.assets.GetBuffer(this->FilePath));
		}
		else
		{
			//TODO: ERROR LOGGING
		}
		returning->Resume();
		return returning;
	}


	//Instance Stuff
	void SoundHandler::HandleEvents()
	{
		for (auto& x : this->children) {
			x.second->HandleEvents();
		}
	}

	void SoundHandler::FireEvent(std::string Event){}
	void SoundHandler::HookEvent(std::string Event, std::function<void()> function){}
	void SoundHandler::Render(float dt, sf::RenderTexture* target){}

	void SoundHandler::Tick(float dt)
	{
		for (auto x = this->ActiveSounds.begin(); x != this->ActiveSounds.end(); ) {
			if (x->second->_sound->getStatus() == sf::SoundSource::Stopped)
			{
				delete x->second->_sound;
				x = this->ActiveSounds.erase(x);
			}
			else
				++x;
		}

		for (auto& x : this->children) {
			x.second->Tick(dt);
		}
	}
	void SoundHandler::AddChild(Instance* child)
	{
		if (child->Type != "Frame")
		{
			child->_body.setSize(this->_body.getSize());
			child->_body.setPosition(this->_body.getPosition());
		}
		this->children.emplace(this->children.size() + 1, child);
		child->Parent = this;
	};

}