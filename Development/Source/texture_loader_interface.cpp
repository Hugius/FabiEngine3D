#include "texture_loader.hpp"
#include "logger.hpp"

GLuint TextureLoader::getText(const string& textContent, const string& fontPath)
{
	begin: auto it = _textCache.find(make_pair(textContent, fontPath));
	if (it == _textCache.end()) // Not in map (yet)
	{
		GLuint loadedTexture = _loadText(textContent, fontPath);

		// Determine if needs to be cached
		if (loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			_textCache.insert(make_pair(make_pair(textContent, fontPath), loadedTexture));
			goto begin;
		}
	}

	return it->second; // Cache texture
}

GLuint TextureLoader::getTexture(const string& filePath, bool mipmap, bool aniso, bool repeat)
{
	begin: auto it = _textureCache.find(filePath);
	if (it == _textureCache.end()) // Not in map (yet)
	{ 
		GLuint loadedTexture = _loadTexture(filePath, mipmap, aniso, repeat);

		// Determine if needs to be cached
		if (loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			_textureCache.insert(std::make_pair(filePath, loadedTexture));
			goto begin;
		}
	}
	
	return it->second; // Cache texture
}

GLuint TextureLoader::getCubeMap(const array<string, 6>& filePaths)
{
	begin: auto it = _cubeMapCache.find(filePaths);
	if (it == _cubeMapCache.end()) // Not in map (yet)
	{
		GLuint loadedTexture = _loadCubeMap(filePaths);

		// Determine if needs to be cached
		if (loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			_cubeMapCache.insert(std::make_pair(filePaths, loadedTexture));
			goto begin;
		}
	}

	return it->second; // Cache texture
}

const vector<float>& TextureLoader::getHeightMap(const string& filePath)
{
	begin: auto it = _heightMapCache.find(filePath);
	if (it == _heightMapCache.end()) // Not in map (yet)
	{
		auto loadedPixels = _loadHeightMap(filePath);

		// Determine if needs to be cached
		if (loadedPixels.empty())
		{
			return {};
		}
		else
		{
			_heightMapCache.insert(std::make_pair(filePath, loadedPixels));
			goto begin;
		}
	}

	return it->second; // Cache texture
}

void TextureLoader::clearTextCache(const string& textContent, const string& fontPath)
{
	if (_textCache.find(make_pair(textContent, fontPath)) != _textCache.end())
	{
		glDeleteTextures(1, &_textCache[make_pair(textContent, fontPath)]);
		_textCache.erase(make_pair(textContent, fontPath));
	}
}

void TextureLoader::clearFontCache(const string& filePath)
{
	if (_fontCache.find(filePath) != _fontCache.end())
	{
		TTF_CloseFont(_fontCache[filePath]);
		_fontCache.erase(filePath);
	}
}

void TextureLoader::clearTextureCache(const string& filePath)
{
	if (_textureCache.find(filePath) != _textureCache.end())
	{
		glDeleteTextures(1, &_textureCache[filePath]);
		_textureCache.erase(filePath);
	}
}

void TextureLoader::clearCubeMapCache(const array<string, 6>& filePaths)
{
	if (_cubeMapCache.find(filePaths) != _cubeMapCache.end())
	{
		glDeleteTextures(1, &_cubeMapCache[filePaths]);
		_cubeMapCache.erase(filePaths);
	}
}

void TextureLoader::clearHeightMapCache(const string& filePath)
{
	if (_heightMapCache.find(filePath) != _heightMapCache.end())
	{
		_heightMapCache.erase(filePath);
	}
}