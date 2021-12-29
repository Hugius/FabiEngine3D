#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>

using std::future;
using std::launch;

const TextureID TextureLoader::load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
BEGIN:;
	auto cacheIterator = _2dTextureCache.find(filePath);

	if (cacheIterator != _2dTextureCache.end())
	{
		return cacheIterator->second;
	}

	auto loadedSurface = _loadSurface(filePath);

	if (loadedSurface == nullptr)
	{
		Logger::throwWarning("Cannot load image: \"" + filePath + "\"!");
		return 0;
	}
	else
	{
		auto loadedTexture = _convertInto2dTexture(loadedSurface, filePath, isMipmapped, isAnisotropic);

		SDL_FreeSurface(loadedSurface);

		if (loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			_2dTextureCache.insert(make_pair(filePath, loadedTexture));

			goto BEGIN;
		}
	}
}

const TextureID TextureLoader::load3dTexture(const array<string, 6>& filePaths)
{
BEGIN:;
	auto cacheIterator = _3dTextureCache.find(filePaths);

	if (cacheIterator != _3dTextureCache.end())
	{
		return cacheIterator->second;
	}

	vector<future<SDL_Surface*>> threads;
	array<SDL_Surface*, 6> loadedSurfaces = {};

	for (size_t i = 0; i < filePaths.size(); i++)
	{
		threads.push_back(async(launch::async, &TextureLoader::_loadSurface, this, filePaths[i]));
	}

	for (size_t i = 0; i < threads.size(); i++)
	{
		loadedSurfaces[i] = threads[i].get();

		if ((loadedSurfaces[i] == nullptr) && !filePaths[i].empty())
		{
			Logger::throwWarning("Cannot load image: \"" + filePaths[i] + "\"!");
		}
	}

	TextureID loadedTexture = _convertInto3dTexture(loadedSurfaces, filePaths);

	for (const auto& surface : loadedSurfaces)
	{
		if (surface != nullptr)
		{
			SDL_FreeSurface(surface);
		}
	}

	if (loadedTexture == 0)
	{
		return 0;
	}
	else
	{
		_3dTextureCache.insert(make_pair(filePaths, loadedTexture));

		goto BEGIN;
	}
}

const vector<float>* TextureLoader::loadBitmap(const string& filePath)
{
BEGIN:;
	auto cacheIterator = _bitmapCache.find(filePath);

	if (cacheIterator != _bitmapCache.end())
	{
		return &cacheIterator->second;
	}

	auto loadedBitmap = _loadBitmap(filePath);

	if (loadedBitmap.empty())
	{
		Logger::throwWarning("Cannot load bitmap: \"" + filePath + "\"!");
		return nullptr;
	}
	else
	{
		_bitmapCache.insert(make_pair(filePath, loadedBitmap));

		Logger::throwInfo("Loaded bitmap: \"" + filePath + "\"");

		goto BEGIN;
	}
}