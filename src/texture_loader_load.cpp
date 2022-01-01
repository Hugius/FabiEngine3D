#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>

using std::future;
using std::launch;

const TextureID TextureLoader::load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	BEGIN:;

	auto cacheIterator = _2dTextureCache.find(filePath);

	if(cacheIterator != _2dTextureCache.end())
	{
		return cacheIterator->second;
	}

	auto loadedImage = _loadImage(filePath, false);

	if(loadedImage == nullptr)
	{
		Logger::throwWarning("Cannot load image: \"" + filePath + "\"!");
		return 0;
	}
	else
	{
		auto loadedTexture = _create2dTexture(loadedImage, filePath, isMipmapped, isAnisotropic);

		delete[] loadedImage->getPixels();

		if(loadedTexture == 0)
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

	if(cacheIterator != _3dTextureCache.end())
	{
		return cacheIterator->second;
	}

	array<shared_ptr<Image>, 6> loadedImages = {};

	for(size_t i = 0; i < filePaths.size(); i++)
	{
		loadedImages[i] = _loadImage(filePaths[i], true);

		if((loadedImages[i] == nullptr) && !filePaths[i].empty())
		{
			Logger::throwWarning("Cannot load image: \"" + filePaths[i] + "\"!");
		}
	}

	TextureID loadedTexture = _create3dTexture(loadedImages, filePaths);

	for(const auto& image : loadedImages)
	{
		if(image != nullptr)
		{
			delete[] image->getPixels();
		}
	}

	if(loadedTexture == 0)
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

	if(cacheIterator != _bitmapCache.end())
	{
		return &cacheIterator->second;
	}

	auto loadedBitmap = _loadBitmap(filePath);

	if(loadedBitmap.empty())
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