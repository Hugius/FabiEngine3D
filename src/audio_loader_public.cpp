#include "audio_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::seconds;

const shared_ptr<Audio> AudioLoader::loadAudio(const string& filePath)
{
	auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		return cacheIterator->second;
	}

	auto loadedAudio = _loadAudio(filePath);

	if(loadedAudio == nullptr)
	{
		Logger::throwWarning("Cannot load audio: \"" + filePath + "\"");

		return nullptr;
	}

	_cache.insert({filePath, loadedAudio});

	Logger::throwInfo("Loaded audio: \"" + filePath + "\"");

	return loadedAudio;
}

void AudioLoader::cacheAudio(const string& filePath, bool isCrucial)
{
	auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		return;
	}

	auto loadedAudio = _loadAudio(filePath);

	if(loadedAudio == nullptr)
	{
		if(isCrucial)
		{
			Logger::throwError("Cannot load audio: \"" + filePath + "\"");
		}
		else
		{
			Logger::throwWarning("Cannot load audio: \"" + filePath + "\"");
		}

		return;
	}

	_cache.insert({filePath, loadedAudio});

	Logger::throwInfo("Loaded audio: \"" + filePath + "\"");
}

void AudioLoader::cacheAudios(const vector<string>& filePaths, bool isCrucial)
{
	vector<future<shared_ptr<Audio>>> threads;
	vector<string> threadFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto& filePath : uniqueFilePaths)
	{
		if(_cache.find(filePath) == _cache.end())
		{
			threads.push_back(async(launch::async, &AudioLoader::_loadAudio, this, filePath));
			threadFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	while(finishedThreadCount != threadStatuses.size())
	{
		for(size_t i = 0; i < threadStatuses.size(); i++)
		{
			if(!threadStatuses[i])
			{
				if(threads[i].wait_for(seconds(0)) == future_status::ready)
				{
					threadStatuses[i] = true;
					finishedThreadCount++;

					auto loadedAudio = threads[i].get();

					if(loadedAudio == nullptr)
					{
						if(isCrucial)
						{
							Logger::throwError("Cannot load audio: \"" + threadFilePaths[i] + "\"");
						}
						else
						{
							Logger::throwWarning("Cannot load audio: \"" + threadFilePaths[i] + "\"");
						}

						continue;
					}

					_cache.insert({threadFilePaths[i], loadedAudio});

					Logger::throwInfo("Loaded audio: \"" + threadFilePaths[i] + "\"");
				}
			}
		}
	}
}

void AudioLoader::clearAudioCache(const string& filePath)
{
	if(_cache.find(filePath) != _cache.end())
	{
		_cache.erase(filePath);
	}
}

void AudioLoader::clearAudiosCache()
{
	_cache.clear();
}