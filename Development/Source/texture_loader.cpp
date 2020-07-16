#include "texture_loader.hpp"
#include "logger.hpp"

GLuint TextureLoader::getText(const string & text, const string& filePath)
{
	auto it = _textMap.find(text);
	if (it == _textMap.end()) // Not in map (yet)
	{
		GLuint tempTxt = _loadText(text, filePath);
		_textMap.insert(std::make_pair(text, tempTxt));
		return tempTxt; // Use new texture
	}

	return it->second; // Cache texture
}

GLuint TextureLoader::getTexture(const string &filePath, bool mipmap, bool aniso, bool repeat)
{
	auto it = _textureMap.find(filePath);
	if (it == _textureMap.end()) // Not in map (yet)
	{ 
		GLuint tempTxt = _loadTexture(filePath, mipmap, aniso, repeat);
		_textureMap.insert(std::make_pair(filePath, tempTxt));
		return tempTxt; // Use new texture
	}

	return it->second; // Cache texture
}

GLuint TextureLoader::getCubeMap(const vector<string> filePaths)
{
	auto it = _cubemapMap.find(filePaths);
	if (it == _cubemapMap.end()) // Not in map (yet)
	{
		GLuint tempTxt = _loadCubemap(filePaths);
		_cubemapMap.insert(std::make_pair(filePaths, tempTxt));
		return tempTxt; // Use new texture
	}

	return it->second; // Cache texture
}

vector<float>& TextureLoader::getHeightMap(const string &filePath)
{
	cuzRef : auto it = _pixelMap.find(filePath);
	if (it == _pixelMap.end()) // Not in map (yet)
	{
		auto tempPixels = _loadHeightmap(filePath);
		_pixelMap.insert(std::make_pair(filePath, tempPixels));
		goto cuzRef;
	}

	return it->second; // Cache texture
}