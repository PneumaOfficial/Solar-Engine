#include "AssetManager.hpp"

namespace Solar {

	void AssetManager::loadFonts()
	{
		namespace fs = std::filesystem;
		//TODO: Load items
	}
	AssetManager::AssetManager()
	{
		
	}
	//Textures
	void AssetManager::LoadTexture(std::string name, std::string filePath){
		sf::Texture tex;

		if (tex.loadFromFile(filePath)) {
			this->_textures[name] = tex;
		}
		else
		{
			//TODO: ERROR LOGGING
		}
	}
	sf::Texture& AssetManager::GetTexture(std::string name){
		return this->_textures.at(name);
	}

	//Fonts
	int AssetManager::LoadFont(std::string name, std::string filePath) {
		sf::Font font;
		if (this->_fonts.find(name) != this->_fonts.end())
		{
			return 1;
		}
		if (font.loadFromFile(filePath)) 
		{
			this->_fonts[name] = font;
			return 1;
		}
		else
		{
			//TODO: ERROR LOGGING
			return 0;
		}
	}
	sf::Font& AssetManager::GetFont(std::string name) {
		return this->_fonts.at(name);
	}

	//Audio
	int AssetManager::LoadMusic(std::string filePath)
	{
		if (this->_music.find(filePath) != this->_music.end())
		{
			return 1;
		}
		sf::Music* audio = new sf::Music();
		if (audio->openFromFile(filePath)) {
			this->_music[filePath] = audio;
			return 1;
		}
		else
		{
			//TODO: ERROR LOGGING
			return 0;
		}
	}

	sf::Music* AssetManager::GetMusic(std::string name)
	{
		return this->_music.at(name);
	}


	int AssetManager::LoadBuffer(std::string filePath)
	{
		if (this->_buffer.find(filePath) != this->_buffer.end())
		{
			return 1;
		}
		sf::SoundBuffer audio;
		if (audio.loadFromFile(filePath)) {
			this->_buffer[filePath] = audio;
			return 1;
		}
		else
		{
			//TODO: ERROR LOGGING
			return 0;
		}
	}

	const sf::SoundBuffer& AssetManager::GetBuffer(std::string name)
	{
		if (this->_buffer.find(name) != this->_buffer.end())
		{
			return this->_buffer.at(name);
		}
		else
		{
			//TODO: ERROR LOGGING
		}
	}
}