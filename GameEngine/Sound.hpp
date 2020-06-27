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
		std::unordered_map<int, std::shared_ptr<SoundObject>> ActiveSounds;
		SoundHandler(); // Initializer
		std::shared_ptr<SoundObject> Play(); //Will create a sound object and play it.
		
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
		int ID;
		SoundObject();
		void Pause(); //Pauses the sound, so it can be resumed without destroying it
		void Resume(); //Resumes the sound
		void Stop(); //Stops the sound, removes it from the handler, then destroys itself
	};
}

