#include "texture_loader.hpp"
#include "logger.hpp"

GLuint TextureLoader::getText(const string & text, const string& filePath)
{
	begin: auto it = _textMap.find(text);
	if (it == _textMap.end()) // Not in map (yet)
	{
		GLuint tempTxt = _loadText(text, filePath);
		_textMap.insert(std::make_pair(text, tempTxt));
		goto begin;
	}

	return it->second; // Cache texture
}

GLuint TextureLoader::getTexture(const string &filePath, bool mipmap, bool aniso, bool repeat)
{
	begin: auto it = _textureMap.find(filePath);
	if (it == _textureMap.end()) // Not in map (yet)
	{ 
		GLuint tempTxt = _loadTexture(filePath, mipmap, aniso, repeat);
		_textureMap.insert(std::make_pair(filePath, tempTxt));
		goto begin;
	}

	return it->second; // Cache texture
}

GLuint TextureLoader::getCubeMap(const vector<string> filePaths)
{
	begin: auto it = _cubemapMap.find(filePaths);
	if (it == _cubemapMap.end()) // Not in map (yet)
	{
		GLuint tempTxt = _loadCubemap(filePaths);
		_cubemapMap.insert(std::make_pair(filePaths, tempTxt));
		goto begin;
	}

	return it->second; // Cache texture
}

vector<float>& TextureLoader::getHeightMap(const string &filePath)
{
	begin: auto it = _pixelMap.find(filePath);
	if (it == _pixelMap.end()) // Not in map (yet)
	{
		auto tempPixels = _loadHeightmap(filePath);
		_pixelMap.insert(std::make_pair(filePath, tempPixels));
		goto begin;
	}

	return it->second; // Cache texture
}

void TextureLoader::clearTextureCache(const string& filePath)
{
	if (_textureMap.find(filePath) == _textureMap.end())
	{
		_textureMap.erase(filePath);
	}
}