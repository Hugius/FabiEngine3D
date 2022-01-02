#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>

using std::future;
using std::launch;

const shared_ptr<Image> TextureLoader::loadImage(const string& filePath)
{
	BEGIN:;

	auto cacheIterator = _imageCache.find(filePath);

	if(cacheIterator != _imageCache.end())
	{
		return cacheIterator->second;
	}

	auto loadedImage = _loadImage(filePath, false);

	if(loadedImage == nullptr)
	{
		Logger::throwWarning("Cannot load image: \"" + filePath + "\"!");
		return {};
	}

	_imageCache.insert(make_pair(filePath, loadedImage));
	Logger::throwInfo("Loaded image: \"" + filePath + "\"");
	goto BEGIN;
}

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

	auto loadedTexture = _create2dTexture(loadedImage, filePath, isMipmapped, isAnisotropic);

	if(loadedTexture == 0)
	{
		return 0;
	}

	_imageCache.insert(make_pair(filePath, loadedImage));
	_2dTextureCache.insert(make_pair(filePath, loadedTexture));
	Logger::throwInfo("Loaded image: \"" + filePath + "\"");
	goto BEGIN;
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
		if(!filePaths[i].empty())
		{
			loadedImages[i] = _loadImage(filePaths[i], true);

			if(loadedImages[i] == nullptr)
			{
				Logger::throwWarning("Cannot load image: \"" + filePaths[i] + "\"!");
				continue;
			}

			_imageCache.insert(make_pair(filePaths[i], loadedImages[i]));
			Logger::throwInfo("Loaded image: \"" + filePaths[i] + "\"");
		}
	}

	TextureID loadedTexture = _create3dTexture(loadedImages, filePaths);

	if(loadedTexture == 0)
	{
		return 0;
	}

	_3dTextureCache.insert(make_pair(filePaths, loadedTexture));
	goto BEGIN;
}