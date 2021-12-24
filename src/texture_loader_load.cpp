#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>

using std::future;
using std::launch;

const TextureID TextureLoader::load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	BEGIN:
	// Search cache
	auto cacheIterator = _2dTextureCache.find(filePath);

	// Return from cache
	if(cacheIterator != _2dTextureCache.end())
	{
		return cacheIterator->second;
	}

	// Load SDL surface
	auto loadedSurface = _loadSurface(filePath);

	// Check surface status
	if(loadedSurface == nullptr)
	{
		Logger::throwWarning("Cannot load image: \"" + filePath + "\"!");
		return 0;
	}
	else
	{
		// Load OpenGL texture
		auto loadedTexture = _convertInto2dTexture(loadedSurface, filePath, isMipmapped, isAnisotropic);

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
			_2dTextureCache.insert(make_pair(filePath, loadedTexture));

			// Return cached texture
			goto BEGIN;
		}
	}
}

const TextureID TextureLoader::load3dTexture(const array<string, 6>& filePaths)
{
	BEGIN:
	// Search cache
	auto cacheIterator = _3dTextureCache.find(filePaths);

	// Return from cache
	if(cacheIterator != _3dTextureCache.end())
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
			Logger::throwWarning("Cannot load image: \"" + filePaths[i] + "\"!");
		}
	}

	// Load OpenGL texture
	TextureID loadedTexture = _convertInto3dTexture(loadedSurfaces, filePaths);

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
		_3dTextureCache.insert(make_pair(filePaths, loadedTexture));

		// Return cached texture
		goto BEGIN;
	}
}

const vector<float>* TextureLoader::loadBitmap(const string& filePath)
{
	BEGIN:
	// Search cache
	auto cacheIterator = _bitmapCache.find(filePath);

	// Return from cache
	if(cacheIterator != _bitmapCache.end())
	{
		return &cacheIterator->second;
	}

	// Load bitmap
	auto loadedBitmap = _loadBitmap(filePath);

	// Check bitmap status
	if(loadedBitmap.empty())
	{
		Logger::throwWarning("Cannot load bitmap: \"" + filePath + "\"!");
		return nullptr;
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

const TextureID TextureLoader::load2dTexture(const string& textContent, const string& fontPath)
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
			Logger::throwWarning("Cannot load font: \"" + fontPath + "\"!");
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
	TextureID loadedTexture = _convertInto2dTexture(font, textContent);

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