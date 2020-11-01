#include "texture_loader.hpp"
#include "logger.hpp"

GLuint TextureLoader::getText(const string& textContent, const string& fontPath)
{
	begin: auto it = _textMaps.find(make_pair(textContent, fontPath));
	if (it == _textMaps.end()) // Not in map (yet)
	{
		GLuint tempTxt = _loadText(textContent, fontPath);
		_textMaps.insert(make_pair(make_pair(textContent, fontPath), tempTxt));
		goto begin;
	}

	return it->second; // Cache texture
}

GLuint TextureLoader::getTexture(const string& filePath, bool mipmap, bool aniso, bool repeat)
{
	begin: auto it = _textures.find(filePath);
	if (it == _textures.end()) // Not in map (yet)
	{ 
		GLuint tempTxt = _loadTexture(filePath, mipmap, aniso, repeat);
		_textures.insert(std::make_pair(filePath, tempTxt));
		goto begin;
	}
	
	return it->second; // Cache texture
}

GLuint TextureLoader::getCubeMap(const array<string, 6>& filePaths)
{
	begin: auto it = _cubeMaps.find(filePaths);
	if (it == _cubeMaps.end()) // Not in map (yet)
	{
		GLuint tempTxt = _loadCubeMap(filePaths);
		_cubeMaps.insert(std::make_pair(filePaths, tempTxt));
		goto begin;
	}

	return it->second; // Cache texture
}

vector<float>& TextureLoader::getHeightMap(const string& filePath)
{
	begin: auto it = _heightMaps.find(filePath);
	if (it == _heightMaps.end()) // Not in map (yet)
	{
		auto tempPixels = _loadHeightMap(filePath);
		_heightMaps.insert(std::make_pair(filePath, tempPixels));
		goto begin;
	}

	return it->second; // Cache texture
}

void TextureLoader::clearTextCache(const string& textContent, const string& fontPath)
{
	if (_textMaps.find(make_pair(textContent, fontPath)) != _textMaps.end())
	{
		glDeleteTextures(1, &_textMaps[make_pair(textContent, fontPath)]);
		_textMaps.erase(make_pair(textContent, fontPath));
	}
}

void TextureLoader::clearFontCache(const string& filePath)
{
	if (_fonts.find(filePath) != _fonts.end())
	{
		TTF_CloseFont(_fonts[filePath]);
		_fonts.erase(filePath);
	}
}

void TextureLoader::clearTextureCache(const string& filePath)
{
	if (_textures.find(filePath) != _textures.end())
	{
		glDeleteTextures(1, &_textures[filePath]);
		_textures.erase(filePath);
	}
}

void TextureLoader::clearCubeMapCache(const array<string, 6>& filePaths)
{
	if (_cubeMaps.find(filePaths) != _cubeMaps.end())
	{
		glDeleteTextures(1, &_cubeMaps[filePaths]);
		_cubeMaps.erase(filePaths);
	}
}

void TextureLoader::clearHeightMapCache(const string& filePath)
{
	if (_heightMaps.find(filePath) != _heightMaps.end())
	{
		_heightMaps.erase(filePath);
	}
}