#include "TextureLoader.hpp"
#include "Logger.hpp"

GLuint TextureLoader::getText(const string & text, const string & fontPath)
{
	auto it = _textMap.find(text);
	if (it == _textMap.end()) // Not in map (yet)
	{
		GLuint tempTxt = _loadText(text, fontPath);
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

GLuint TextureLoader::getCubeMap(const string & filePath)
{
	auto it = _textureMap.find(filePath);
	if (it == _textureMap.end()) // Not in map (yet)
	{
		GLuint tempTxt = _loadCubemap(filePath);
		_textureMap.insert(std::make_pair(filePath, tempTxt));
		return tempTxt; // Use new texture
	}

	return it->second; // Cache texture
}

vector<float> & TextureLoader::getHeightMap(const string &filePath, int size)
{
	cuzRef : auto it = _pixelMap.find(filePath);
	if (it == _pixelMap.end()) // Not in map (yet)
	{
		auto tempPixels = _loadHeightmap(filePath, size);
		_pixelMap.insert(std::make_pair(filePath, tempPixels));
		goto cuzRef;
	}

	return it->second; // Cache texture
}