#include "image_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::system_clock;

const shared_ptr<Image> ImageLoader::loadImage(const string& filePath)
{
	BEGIN:;

	auto cacheIterator = _imageCache.find(filePath);

	if(cacheIterator != _imageCache.end())
	{
		return cacheIterator->second;
	}

	auto loadedImage = _loadImage(filePath);

	if(loadedImage == nullptr)
	{
		Logger::throwWarning("Cannot load image: \"" + filePath + "\"!");
		return {};
	}

	_imageCache.insert(make_pair(filePath, loadedImage));
	Logger::throwInfo("Loaded image: \"" + filePath + "\"");
	goto BEGIN;
}

void ImageLoader::cacheImage(const string& filePath)
{
	loadImage(filePath);
}

void ImageLoader::cacheImages(const vector<string>& filePaths)
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
			threads.push_back(async(launch::async, &ImageLoader::_loadImage, this, filePath));
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
						continue;
					}

					_imageCache[finalFilePaths[i]] = loadedImage;
					Logger::throwInfo("Loaded image: \"" + finalFilePaths[i] + "\"");
				}
			}
		}
	}
}

void ImageLoader::clearImageCache(const string& filePath)
{
	if(_imageCache.find(filePath) != _imageCache.end())
	{
		_imageCache.erase(filePath);
	}
}

void ImageLoader::clearImagesCache()
{
	_imageCache.clear();
}