#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::system_clock;

void TextureLoader::cache2dTextures(const vector<string>& filePaths, bool isMipmapped, bool isAnisotropic)
{
	vector<future<SDL_Surface*>> threads;
	vector<string> finalFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for (const auto& filePath : uniqueFilePaths)
	{
		if (_2dTextureCache.find(filePath) == _2dTextureCache.end())
		{
			threads.push_back(async(launch::async, &TextureLoader::_loadSurface, this, filePath));
			finalFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	while (finishedThreadCount != threadStatuses.size())
	{
		for (size_t i = 0; i < threadStatuses.size(); i++)
		{
			if (!threadStatuses[i])
			{
				if (threads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
				{
					auto loadedImage = threads[i].get();

					threadStatuses[i] = true;
					finishedThreadCount++;

					if (loadedImage == nullptr)
					{
						Logger::throwWarning("Cannot load image: \"" + finalFilePaths[i] + "\"!");
					}
					else
					{
						auto loadedTexture = _convertInto2dTexture(loadedImage, finalFilePaths[i], isMipmapped, isAnisotropic);

						SDL_FreeSurface(loadedImage);

						if (loadedTexture != 0)
						{
							_2dTextureCache[finalFilePaths[i]] = loadedTexture;
						}
					}
				}
			}
		}
	}
}

void TextureLoader::cache3dTextures(const vector<array<string, 6>>& filePathsList)
{
	vector<vector<future<SDL_Surface*>>> threads;
	vector<array<string, 6>> finalFilePathsList;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	for (const auto& filePaths : filePathsList)
	{
		if (_3dTextureCache.find(filePaths) == _3dTextureCache.end())
		{
			threads.push_back({});
			for (const auto& filePath : filePaths)
			{
				threads.back().push_back(async(launch::async, &TextureLoader::_loadSurface, this, filePath));
			}
			finalFilePathsList.push_back(filePaths);
			threadStatuses.push_back(false);
		}
	}

	while (finishedThreadCount != threadStatuses.size())
	{
		for (size_t i = 0; i < threadStatuses.size(); i++)
		{
			if (!threadStatuses[i])
			{
				bool threadsAreFinished = true;
				for (size_t j = 0; j < threads[i].size(); j++)
				{
					if (threads[i][i].wait_until(system_clock::time_point::min()) != future_status::ready)
					{
						threadsAreFinished = false;
					}
				}

				array<SDL_Surface*, 6> loadedImages;
				if (threadsAreFinished)
				{
					threadStatuses[i] = true;
					finishedThreadCount++;

					for (size_t j = 0; j < threads[i].size(); j++)
					{
						loadedImages[j] = threads[i][j].get();

						if ((loadedImages[j] == nullptr) && !finalFilePathsList[i][j].empty())
						{
							Logger::throwWarning("Cannot load image: \"" + finalFilePathsList[i][j] + "\"!");
						}
					}

					TextureID loadedTexture = _convertInto3dTexture(loadedImages, finalFilePathsList[i]);

					for (const auto& image : loadedImages)
					{
						if (image != nullptr)
						{
							SDL_FreeSurface(image);
						}
					}

					if (loadedTexture != 0)
					{
						_3dTextureCache[finalFilePathsList[i]] = loadedTexture;
					}
				}
			}
		}
	}
}

void TextureLoader::cacheBitmaps(const vector<string>& filePaths)
{
	vector<future<vector<float>>> threads;
	vector<string> finalFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for (const auto& filePath : uniqueFilePaths)
	{
		if (_bitmapCache.find(filePath) == _bitmapCache.end())
		{
			threads.push_back(async(launch::async, &TextureLoader::_loadBitmap, this, filePath));
			finalFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	while (finishedThreadCount != threadStatuses.size())
	{
		for (size_t i = 0; i < threadStatuses.size(); i++)
		{
			if (!threadStatuses[i])
			{
				if (threads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
				{
					auto loadedBitmap = threads[i].get();

					threadStatuses[i] = true;
					finishedThreadCount++;

					if (loadedBitmap.empty())
					{
						Logger::throwWarning("Cannot load bitmap: \"" + finalFilePaths[i] + "\"!");
					}
					else
					{
						_bitmapCache[finalFilePaths[i]] = loadedBitmap;

						Logger::throwInfo("Loaded bitmap: \"" + finalFilePaths[i] + "\"");
					}
				}
			}
		}
	}
}

void TextureLoader::clear2dTextureCache(const string& filePath)
{
	if (_2dTextureCache.find(filePath) != _2dTextureCache.end())
	{
		glDeleteTextures(1, &_2dTextureCache[filePath]);
		_2dTextureCache.erase(filePath);
	}
}

void TextureLoader::clear3dTextureCache(const array<string, 6>& filePaths)
{
	if (_3dTextureCache.find(filePaths) != _3dTextureCache.end())
	{
		glDeleteTextures(1, &_3dTextureCache[filePaths]);
		_3dTextureCache.erase(filePaths);
	}
}

void TextureLoader::clearBitmapCache(const string& filePath)
{
	if (_bitmapCache.find(filePath) != _bitmapCache.end())
	{
		_bitmapCache.erase(filePath);
	}
}

void TextureLoader::clear2dTexturesCache()
{
	_2dTextureCache.clear();
}

void TextureLoader::clear3dTexturesCache()
{
	_3dTextureCache.clear();
}

void TextureLoader::clearBitmapsCache()
{
	_bitmapCache.clear();
}