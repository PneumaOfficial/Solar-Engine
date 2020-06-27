#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <filesystem>
namespace Solar {
	class AssetManager {
	public:
		AssetManager();
		~AssetManager() {};
		//Texture
		void LoadTexture(std::string name, std::string filePath);
		sf::Texture& GetTexture(std::string name);

		//Font
		int LoadFont(std::string name, std::string filePath);
		sf::Font& GetFont(std::string name);
		//Audio
		int LoadMusic(std::string filePath);
		sf::Music* GetMusic(std::string name);

		int LoadBuffer(std::string filePath);
		const sf::SoundBuffer& GetBuffer(std::string name);
	private:
		void loadFonts();

		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;
		std::map<std::string, sf::Music*> _music;
		std::map<std::string, sf::SoundBuffer> _buffer;
	};
}