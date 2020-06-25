#include "AssetManager.hpp"

namespace Solar {
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

	//Shaders

	void AssetManager::LoadShader(std::string name, std::string VertexPath, std::string FragPath) {
		sf::Shader shader;

		if (shader.loadFromFile(VertexPath, FragPath))
		{
			this->_shaders[name] = &shader;
		}
		else
		{
			//TODO: ERROR LOGGING
		}
	}
	void AssetManager::LoadShaderFrag(std::string name, std::string FragPath)
	{
		sf::Shader shader;
		if (shader.loadFromFile(FragPath, sf::Shader::Fragment))
		{
			this->_shaders[name] = &shader;
		}
		else
		{
			//TODO: ERROR LOGGING
		}
	}
	void AssetManager::LoadShaderVertex(std::string name, std::string VertexPath)
	{
		sf::Shader shader;
		if (shader.loadFromFile(VertexPath, sf::Shader::Vertex))
		{
			this->_shaders[name] = &shader;
		}
		else
		{
			//TODO: ERROR LOGGING
		}
	}
	sf::Shader* AssetManager::GetShader(std::string name) {
		return this->_shaders.at(name);
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
	void AssetManager::LoadAudio(std::string name, std::string filePath)
	{
		sf::SoundBuffer audio;

		if (audio.loadFromFile(filePath)) {
			this->_audio[name] = audio;
		}
		else
		{
			//TODO: ERROR LOGGING
		}
	}

	sf::SoundBuffer AssetManager::GetAudio(std::string name)
	{
		return this->_audio.at(name);
	}
}