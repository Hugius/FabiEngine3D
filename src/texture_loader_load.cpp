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
	else
	{
		_imageCache.insert(make_pair(filePath, loadedImage));
		Logger::throwInfo("Loaded image: \"" + filePath + "\"");
		goto BEGIN;
	}
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
	else
	{
		auto loadedTexture = _create2dTexture(loadedImage, filePath, isMipmapped, isAnisotropic);

		if(loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			_imageCache.insert(make_pair(filePath, loadedImage));
			_2dTextureCache.insert(make_pair(filePath, loadedTexture));
			Logger::throwInfo("Loaded image: \"" + filePath + "\"");
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
		else
		{
			//unsigned int imageSize = 0;
			//for(size_t i = 0; i < images.size(); i++)
			//{
			//	if(images[i] != nullptr)
			//	{
			//		if(images[i]->getWidth() != images[i]->getHeight())
			//		{
			//			return 0;
			//		}

			//		if(imageSize == 0)
			//		{
			//			imageSize = images[i]->getWidth();
			//		}
			//		else
			//		{
			//			if(imageSize != images[i]->getWidth())
			//			{
			//				return 0;
			//			}
			//		}
			//	}
			//}

			_imageCache.insert(make_pair(filePaths[i], loadedImages[i]));
			Logger::throwInfo("Loaded image: \"" + filePaths[i] + "\"");
		}
	}

	TextureID loadedTexture = _create3dTexture(loadedImages, filePaths);

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