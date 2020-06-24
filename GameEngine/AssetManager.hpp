#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Solar {
	class AssetManager {
	public:
		AssetManager() {};
		~AssetManager() {};
		//Texture
		void LoadTexture(std::string name, std::string filePath);
		sf::Texture& GetTexture(std::string name);
		//Shader
		void LoadShader(std::string name, std::string VertextPath, std::string FragPath);
		void LoadShaderFrag(std::string name, std::string FragPath);
		void LoadShaderVertex(std::string name, std::string VertextPath);
		sf::Shader* GetShader(std::string name);
		//Font
		void LoadFont(std::string name, std::string filePath);
		sf::Font& GetFont(std::string name);
		//Audio
		void LoadAudio(std::string name, std::string filePath);
		sf::SoundBuffer GetAudio(std::string name);
	private:
		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;
		std::map<std::string, sf::SoundBuffer> _audio;
		std::map<std::string, sf::Shader*> _shaders;
	};
}