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
	vector<future<shared_ptr<Image>>> threads;
	vector<string> finalFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto& filePath : uniqueFilePaths)
	{
		if(_2dTextureCache.find(filePath) == _2dTextureCache.end())
		{
			threads.push_back(async(launch::async, &TextureLoader::_loadImage, this, filePath, false));
			finalFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	while(finishedThreadCount != threadStatuses.size())
	{
		for(size_t i = 0; i < threadStatuses.size(); i++)
		{
			if(!threadStatuses[i])
			{
				if(threads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
				{
					auto loadedImage = threads[i].get();

					threadStatuses[i] = true;
					finishedThreadCount++;

					if(loadedImage == nullptr)
					{
						Logger::throwWarning("Cannot load image: \"" + finalFilePaths[i] + "\"!");
					}
					else
					{
						auto createdTexture = _create2dTexture(loadedImage, finalFilePaths[i], isMipmapped, isAnisotropic);

						if(createdTexture != 0)
						{
							_imageCache[finalFilePaths[i]] = loadedImage;
							_2dTextureCache[finalFilePaths[i]] = createdTexture;
						}
					}
				}
			}
		}
	}
}

void TextureLoader::cache3dTextures(const vector<array<string, 6>>& filePathsList)
{
	vector<vector<future<shared_ptr<Image>>>> threads;
	vector<array<string, 6>> finalFilePathsList;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	for(const auto& filePaths : filePathsList)
	{
		if(_3dTextureCache.find(filePaths) == _3dTextureCache.end())
		{
			threads.push_back({});
			for(const auto& filePath : filePaths)
			{
				threads.back().push_back(async(launch::async, &TextureLoader::_loadImage, this, filePath, true));
			}
			finalFilePathsList.push_back(filePaths);
			threadStatuses.push_back(false);
		}
	}

	while(finishedThreadCount != threadStatuses.size())
	{
		for(size_t i = 0; i < threadStatuses.size(); i++)
		{
			if(!threadStatuses[i])
			{
				bool threadsAreFinished = true;
				for(size_t j = 0; j < threads[i].size(); j++)
				{
					if(threads[i][i].wait_until(system_clock::time_point::min()) != future_status::ready)
					{
						threadsAreFinished = false;
					}
				}

				array<shared_ptr<Image>, 6> loadedImages;
				if(threadsAreFinished)
				{
					threadStatuses[i] = true;
					finishedThreadCount++;

					for(size_t j = 0; j < threads[i].size(); j++)
					{
						loadedImages[j] = threads[i][j].get();

						if((loadedImages[j] == nullptr) && !finalFilePathsList[i][j].empty())
						{
							Logger::throwWarning("Cannot load image: \"" + finalFilePathsList[i][j] + "\"!");
						}
						else
						{
							_imageCache[finalFilePathsList[i][j]] = loadedImages[j];
						}
					}

					TextureID createdTexture = _create3dTexture(loadedImages, finalFilePathsList[i]);

					if(createdTexture != 0)
					{
						_3dTextureCache[finalFilePathsList[i]] = createdTexture;
					}
				}
			}
		}
	}
}

void TextureLoader::cacheImages(const vector<string>& filePaths)
{
	vector<future<shared_ptr<Image>>> threads;
	vector<string> finalFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto& filePath : uniqueFilePaths)
	{
		if(_imageCache.find(filePath) == _imageCache.end())
		{
			threads.push_back(async(launch::async, &TextureLoader::_loadImage, this, filePath, false));
			finalFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	while(finishedThreadCount != threadStatuses.size())
	{
		for(size_t i = 0; i < threadStatuses.size(); i++)
		{
			if(!threadStatuses[i])
			{
				if(threads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
				{
					auto loadedImage = threads[i].get();

					threadStatuses[i] = true;
					finishedThreadCount++;

					if(loadedImage == nullptr)
					{
						Logger::throwWarning("Cannot load image: \"" + finalFilePaths[i] + "\"!");
					}
					else
					{
						_imageCache[finalFilePaths[i]] = loadedImage;
						Logger::throwInfo("Loaded image: \"" + finalFilePaths[i] + "\"");
					}
				}
			}
		}
	}
}

void TextureLoader::clear2dTextureCache(const string& filePath)
{
	if(_2dTextureCache.find(filePath) != _2dTextureCache.end())
	{
		glDeleteTextures(1, &_2dTextureCache[filePath]);
		_2dTextureCache.erase(filePath);
	}
}

void TextureLoader::clear3dTextureCache(const array<string, 6>& filePaths)
{
	if(_3dTextureCache.find(filePaths) != _3dTextureCache.end())
	{
		glDeleteTextures(1, &_3dTextureCache[filePaths]);
		_3dTextureCache.erase(filePaths);
	}
}

void TextureLoader::clearImageCache(const string& filePath)
{
	if(_imageCache.find(filePath) != _imageCache.end())
	{
		_imageCache.erase(filePath);
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

void TextureLoader::clearImagesCache()
{
	_imageCache.clear();
}