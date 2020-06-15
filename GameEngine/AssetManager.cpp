#include "AssetManager.hpp"

namespace Solar {
	//Textures
	void AssetManager::LoadTexture(std::string name, std::string filePath){
		sf::Texture tex;

		if (tex.loadFromFile(filePath)) {
			this->_textures[name] = tex;
		}
	}
	sf::Texture& AssetManager::GetTexture(std::string name){
		return this->_textures.at(name);
	}


	//Fonts
	void AssetManager::LoadFont(std::string name, std::string filePath) {
		sf::Font font;

		if (font.loadFromFile(filePath)) {
			this->_fonts[name] = font;
		}
	}
	sf::Font& AssetManager::GetFont(std::string name) {
		return this->_fonts.at(name);
	}

	//Audio
	void AssetManager::LoadAudio(std::string name, std::string filePath)
	{
		sf::SoundBuffer audio;

		if (audio.loadFromFile(filePath)) {
			this->_audio[name] = audio;
		}
	}

	sf::SoundBuffer AssetManager::GetAudio(std::string name)
	{
		return this->_audio.at(name);
	}
}