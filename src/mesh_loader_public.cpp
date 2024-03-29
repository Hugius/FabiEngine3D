#include "mesh_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::seconds;

const shared_ptr<Mesh> MeshLoader::getMesh(const string & filePath)
{
	const auto iterator = _cache.find(filePath);

	if(iterator != _cache.end())
	{
		return iterator->second;
	}

	auto loadedMesh = _getMesh(filePath);

	if(loadedMesh == nullptr)
	{
		Logger::throwWarning("Cannot load mesh: \"" + filePath + "\"");

		return nullptr;
	}

	_cache.insert({filePath, loadedMesh});

	Logger::throwInfo("Loaded mesh: \"" + filePath + "\"");

	return loadedMesh;
}

void MeshLoader::cacheMesh(const string & filePath, bool isCrucial)
{
	const auto iterator = _cache.find(filePath);

	if(iterator != _cache.end())
	{
		return;
	}

	auto loadedMesh = _getMesh(filePath);

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

void MeshLoader::cacheMeshes(const vector<string> & filePaths, bool isCrucial)
{
	vector<future<shared_ptr<Mesh>>> threads = {};
	vector<string> threadFilePaths = {};
	vector<bool> threadStatuses = {};
	int finishedThreadCount = 0;

	const auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	const auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto & filePath : uniqueFilePaths)
	{
		if(_cache.find(filePath) == _cache.end())
		{
			threads.push_back(async(launch::async, &MeshLoader::_getMesh, this, filePath));
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

					const auto loadedMesh = threads[index].get();

					if(loadedMesh == nullptr)
					{
						if(isCrucial)
						{
							Logger::throwError("Cannot load mesh: \"" + threadFilePaths[index] + "\"");
						}
						else
						{
							Logger::throwWarning("Cannot load mesh: \"" + threadFilePaths[index] + "\"");
						}

						continue;
					}

					_cache.insert({threadFilePaths[index], loadedMesh});

					Logger::throwInfo("Loaded mesh: \"" + threadFilePaths[index] + "\"");
				}
			}
		}
	}
}

void MeshLoader::clearMeshCache(const string & filePath)
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