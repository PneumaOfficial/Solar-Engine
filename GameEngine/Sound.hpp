#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include "Instance.hpp"
namespace Solar
{
	class SoundObject;

	class SoundHandler : public Instance
	{
	private:
		std::string PrevFilePath;
	public:
		SoundHandler(); // Initializer
		std::vector<std::unique_ptr<SoundObject>> ActiveSounds;
		std::unique_ptr<SoundObject> Play(); //Will create a sound object and play it.

		std::string FilePath;

		//Instance stuff
		void HandleEvents();

		void Render(float dt, sf::RenderTexture* target);
		void Tick(float dt);
	};

	class SoundObject
	{
		friend SoundHandler;
	private:
		SoundHandler* handler;
		sf::Sound* _sound = new sf::Sound();
	public:
		SoundObject();
		int ID;
		void Pause(); //Pauses the sound, so it can be resumed without destroying it
		void Resume(); //Resumes the sound
		void Stop(); //Stops the sound, removes it from the handler, then destroys itself
	};
	auto CreateSound()
	{
		return std::make_unique<SoundHandler>();
	}
}


