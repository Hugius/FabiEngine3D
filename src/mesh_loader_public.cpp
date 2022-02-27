#include "mesh_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::seconds;

const shared_ptr<Mesh> MeshLoader::loadMesh(const string& filePath)
{
	auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		return cacheIterator->second;
	}

	auto loadedMesh = _loadMesh(filePath);

	if(loadedMesh == nullptr)
	{
		Logger::throwWarning("Cannot load mesh: \"" + filePath + "\"");

		return nullptr;
	}

	_cache.insert({filePath, loadedMesh});

	Logger::throwInfo("Loaded mesh: \"" + filePath + "\"");

	return loadedMesh;
}

void MeshLoader::cacheMesh(const string& filePath, bool isCrucial)
{
	auto cacheIterator = _cache.find(filePath);

	if(cacheIterator != _cache.end())
	{
		return;
	}

	auto loadedMesh = _loadMesh(filePath);

	if(loadedMesh == nullptr)
	{
		if(isCrucial)
		{
			Logger::throwError("Cannot load mesh: \"" + filePath + "\"");
		}
		else
		{
			Logger::throwWarning("Cannot load mesh: \"" + filePath + "\"");
		}

		return;
	}

	_cache.insert({filePath, loadedMesh});

	Logger::throwInfo("Loaded mesh: \"" + filePath + "\"");
}

void MeshLoader::cacheMeshes(const vector<string>& filePaths, bool isCrucial)
{
	vector<future<shared_ptr<Mesh>>> threads;
	vector<string> threadFilePaths;
	vector<bool> threadStatuses;
	unsigned int finishedThreadCount = 0;

	auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto& filePath : uniqueFilePaths)
	{
		if(_cache.find(filePath) == _cache.end())
		{
			threads.push_back(async(launch::async, &MeshLoader::_loadMesh, this, filePath));
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

					auto loadedMesh = threads[i].get();

					if(loadedMesh == nullptr)
					{
						if(isCrucial)
						{
							Logger::throwError("Cannot load mesh: \"" + threadFilePaths[i] + "\"");
						}
						else
						{
							Logger::throwWarning("Cannot load mesh: \"" + threadFilePaths[i] + "\"");
						}

						continue;
					}

					_cache.insert({threadFilePaths[i], loadedMesh});

					Logger::throwInfo("Loaded mesh: \"" + threadFilePaths[i] + "\"");
				}
			}
		}
	}
}

void MeshLoader::clearMeshCache(const string& filePath)
{
	if(_cache.find(filePath) != _cache.end())
	{
		_cache.erase(filePath);
	}
}

void MeshLoader::clearMeshesCache()
{
	_cache.clear();
}