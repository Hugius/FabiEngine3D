#include "image_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::seconds;

const shared_ptr<Image> ImageLoader::loadImage(const string & filePath)
{
	const auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		return cacheIterator->second;
	}

	auto loadedImage = _loadImage(filePath);

	if(loadedImage == nullptr)
	{
		Logger::throwWarning("Cannot load image: \"" + filePath + "\"");

		return nullptr;
	}

	_cache.insert({filePath, loadedImage});

	Logger::throwInfo("Loaded image: \"" + filePath + "\"");

	return loadedImage;
}

void ImageLoader::cacheImage(const string & filePath, bool isCrucial)
{
	const auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		return;
	}

	auto loadedImage = _loadImage(filePath);

	if(loadedImage == nullptr)
	{
		if(isCrucial)
		{
			Logger::throwError("Cannot load image: \"" + filePath + "\"");
		}
		else
		{
			Logger::throwWarning("Cannot load image: \"" + filePath + "\"");
		}

		return;
	}

	_cache.insert({filePath, loadedImage});

	Logger::throwInfo("Loaded image: \"" + filePath + "\"");
}

void ImageLoader::cacheImages(const vector<string> & filePaths, bool isCrucial)
{
	vector<future<shared_ptr<Image>>> threads = {};
	vector<string> threadFilePaths = {};
	vector<bool> threadStatuses = {};
	int finishedThreadCount = 0;

	const auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	const auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto & filePath : uniqueFilePaths)
	{
		if(_cache.find(filePath) == _cache.end())
		{
			threads.push_back(async(launch::async, &ImageLoader::_loadImage, this, filePath));
			threadFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	while(finishedThreadCount != threadStatuses.size())
	{
		for(int index = 0; index < static_cast<int>(threadStatuses.size()); index++)
		{
			if(!threadStatuses[index])
			{
				if(threads[index].wait_for(seconds(0)) == future_status::ready)
				{
					threadStatuses[index] = true;
					finishedThreadCount++;

					const auto loadedImage = threads[index].get();

					if(loadedImage == nullptr)
					{
						if(isCrucial)
						{
							Logger::throwError("Cannot load image: \"" + threadFilePaths[index] + "\"");
						}
						else
						{
							Logger::throwWarning("Cannot load image: \"" + threadFilePaths[index] + "\"");
						}

						continue;
					}

					_cache.insert({threadFilePaths[index], loadedImage});

					Logger::throwInfo("Loaded image: \"" + threadFilePaths[index] + "\"");
				}
			}
		}
	}
}

void ImageLoader::clearImageCache(const string & filePath)
{
	if(_cache.find(filePath) != _cache.end())
	{
		_cache.erase(filePath);
	}
}

void ImageLoader::clearImagesCache()
{
	_cache.clear();
}