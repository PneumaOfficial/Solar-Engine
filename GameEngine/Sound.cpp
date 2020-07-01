#include "Sound.hpp"
#include "DEFINTIONS.hpp"
namespace Solar
{
	extern struct Enums Enum;
	SoundObject::SoundObject() {};
	void SoundObject::Pause()
	{
		this->_sound->pause();
	}
	void SoundObject::Resume()
	{
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

	void SoundHandler::Render(float dt, sf::RenderTexture* target) {};

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

}