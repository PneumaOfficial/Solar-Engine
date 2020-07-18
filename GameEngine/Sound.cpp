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
	std::unique_ptr<SoundObject> SoundHandler::Play()
	{
		auto returning = std::make_unique<SoundObject>(SoundObject());
		returning->handler = this;
		returning->ID = this->ActiveSounds.size() + 1;
		this->ActiveSounds.push_back(returning);
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
		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->HandleEvents();
		}
	}

	void SoundHandler::Render(float dt, sf::RenderTexture* target) {};

	void SoundHandler::Tick(float dt)
	{
		for (unsigned pos = 0; pos < this->ActiveSounds.size(); ++pos)
		{
			auto& i = this->ActiveSounds[pos];
			if (i->_sound->getStatus() == sf::SoundSource::Stopped)
			{
				delete i->_sound;
				this->ActiveSounds.erase(this->ActiveSounds.begin() + (pos - 1));
			}
		}

		for (std::size_t i = 0; i < this->children.size(); ++i) {
			this->children[i]->Tick(dt);
		}
	}

}