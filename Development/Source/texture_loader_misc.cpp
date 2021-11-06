#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>

using std::future;
using std::launch;
using std::clamp;

TextureLoader::TextureLoader(RenderBus& renderBus)
	:
	_renderBus(renderBus)
{

}

TextureID TextureLoader::loadTexture2D(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
BEGIN:
	// Search cache
	auto cacheIterator = _textureCache2D.find(filePath);

	// Return from cache
	if(cacheIterator != _textureCache2D.end())
	{
		return cacheIterator->second;
	}

	// Load SDL surface
	auto loadedSurface = _loadSurface(filePath);

	// Check surface status
	if(loadedSurface == nullptr)
	{
		Logger::throwWarning("Cannot load image file: \"" + filePath + "\"!");
		return 0;
	}
	else
	{
		// Load OpenGL texture
		auto loadedTexture = _convertIntoTexture(loadedSurface, filePath, isMipmapped, isAnisotropic);

		// Memory management
		SDL_FreeSurface(loadedSurface);

		// Check texture status
		if(loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			// Cache texture
			_textureCache2D.insert(make_pair(filePath, loadedTexture));

			// Return cached texture
			goto BEGIN;
		}
	}
}

TextureID TextureLoader::loadTexture3D(const array<string, 6>& filePaths)
{
BEGIN:
	// Search cache
	auto cacheIterator = _textureCache3D.find(filePaths);

	// Return from cache
	if(cacheIterator != _textureCache3D.end())
	{
		return cacheIterator->second;
	}

	// Temporary values
	vector<future<SDL_Surface*>> threads;
	array<SDL_Surface*, 6> loadedSurfaces = {};

	// Start all loading threads
	for(size_t i = 0; i < filePaths.size(); i++)
	{
		threads.push_back(async(launch::async, &TextureLoader::_loadSurface, this, filePaths[i]));
	}

	// Wait for all threads to finish
	for(size_t i = 0; i < threads.size(); i++)
	{
		// Save loaded surface
		loadedSurfaces[i] = threads[i].get();

		// Error logging
		if((loadedSurfaces[i] == nullptr) && !filePaths[i].empty())
		{
			Logger::throwWarning("Cannot load image file: \"" + filePaths[i] + "\"!");
		}
	}

	// Load OpenGL texture
	TextureID loadedTexture = _convertIntoTexture(loadedSurfaces, filePaths);

	// Memory management
	for(const auto& surface : loadedSurfaces)
	{
		// Only if memory is present
		if(surface != nullptr)
		{
			SDL_FreeSurface(surface);
		}
	}

	// Check texture status
	if(loadedTexture == 0)
	{
		return 0;
	}
	else
	{
		// Cache texture
		_textureCache3D.insert(make_pair(filePaths, loadedTexture));

		// Return cached texture
		goto BEGIN;
	}
}

const vector<float>& TextureLoader::loadBitmap(const string& filePath)
{
BEGIN:
	// Search cache
	auto cacheIterator = _bitmapCache.find(filePath);

	// Return from cache
	if(cacheIterator != _bitmapCache.end())
	{
		return cacheIterator->second;
	}

	// Load bitmap
	auto loadedBitmap = _loadBitmap(filePath);

	// Check bitmap status
	if(loadedBitmap.empty())
	{
		Logger::throwWarning("Cannot load image file: \"" + filePath + "\"!");
		return {};
	}
	else
	{
		// Cache bitmap
		_bitmapCache.insert(make_pair(filePath, loadedBitmap));

		// Logging
		Logger::throwInfo("Loaded bitmap: \"" + filePath + "\"");

		// Return cached bitmap
		goto BEGIN;
	}
}

const unsigned int TextureLoader::getAnisotropicFilteringQuality()
{
	return _anisotropicFilteringQuality;
}

TextureID TextureLoader::loadTexture2D(const string& textContent, const string& fontPath)
{
BEGIN:
	// Temporary values
	TTF_Font* font = nullptr;

	// Search text cache
	auto textCacheIterator = _textCache.find(make_pair(textContent, fontPath));

	// Return from text cache
	if(textCacheIterator != _textCache.end())
	{
		return textCacheIterator->second;
	}

	// Search font cache
	auto fontCacheIterator = _fontCache.find(fontPath);

	// Check font status
	if(fontCacheIterator == _fontCache.end())
	{
		// Load font
		font = _loadFont(fontPath);

		// Check font status
		if(font == nullptr)
		{
			Logger::throwWarning("Cannot load font file: \"" + fontPath + "\"!");
			return 0;
		}
		else
		{
			// Cache font
			_fontCache.insert(make_pair(fontPath, font));

			// Logging
			Logger::throwInfo("Loaded font: \"" + fontPath + "\"");
		}
	}
	else
	{
		font = fontCacheIterator->second;
	}

	// Load OpenGL texture
	TextureID loadedTexture = _convertIntoTexture(font, textContent);

	// Check texture status
	if(loadedTexture == 0)
	{
		return 0;
	}
	else
	{
		// Cache texture
		_textCache.insert(make_pair(make_pair(textContent, fontPath), loadedTexture));

		// Return cached texture
		goto BEGIN;
	}
}

void TextureLoader::clearTextureCache2D(const string& filePath)
{
	if(_textureCache2D.find(filePath) != _textureCache2D.end())
	{
		glDeleteTextures(1, &_textureCache2D[filePath]);
		_textureCache2D.erase(filePath);
	}
}

void TextureLoader::clearTextureCache3D(const array<string, 6>& filePaths)
{
	if(_textureCache3D.find(filePaths) != _textureCache3D.end())
	{
		glDeleteTextures(1, &_textureCache3D[filePaths]);
		_textureCache3D.erase(filePaths);
	}
}

void TextureLoader::clearBitmapCache(const string& filePath)
{
	if(_bitmapCache.find(filePath) != _bitmapCache.end())
	{
		_bitmapCache.erase(filePath);
	}
}

void TextureLoader::clearFontCache(const string& filePath)
{
	// Clear font cache
	if(_fontCache.find(filePath) != _fontCache.end())
	{
		TTF_CloseFont(_fontCache[filePath]);
		_fontCache.erase(filePath);
	}

	// Clear text cache
	for(const auto& [key, textureID] : _textCache)
	{
		// Check if font corresponds
		if(key.second == filePath)
		{
			glDeleteTextures(1, &textureID);
			_textCache.erase(key);
		}
	}
}

void TextureLoader::setAnisotropicFilteringQuality(unsigned int value)
{
	_anisotropicFilteringQuality = clamp(value, Config::MIN_ANISOTROPIC_FILTERING_QUALITY, Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
	_reloadAnisotropicFiltering();
}

void TextureLoader::_reloadAnisotropicFiltering()
{
	for(const auto& [path, texture] : _textureCache2D)
	{
		// Bind
		glBindTexture(GL_TEXTURE_2D, texture);

		// Get current quality
		int currentQuality;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &currentQuality);

		// Check if texture must be anisotropically filtered
		if((currentQuality >= Config::MIN_ANISOTROPIC_FILTERING_QUALITY) && (currentQuality <= Config::MAX_ANISOTROPIC_FILTERING_QUALITY))
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_anisotropicFilteringQuality));
		}

		// Unbind
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}