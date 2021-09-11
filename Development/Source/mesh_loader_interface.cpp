#include "mesh_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;

void MeshLoader::cacheMeshesMultiThreaded(const vector<string>& meshPaths, vector<string>& resultingTexturePaths)
{
	// Temporary values
	vector<future<pair<string, vector<MeshPart>>>> threads;
	vector<bool> threadStatuses;

	// Remove duplicates
	auto tempFilePaths = set<string>(meshPaths.begin(), meshPaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for (const auto& filePath : uniqueFilePaths)
	{
		// Check if mesh is not already cached
		if (_meshCache.find(filePath) == _meshCache.end())
		{
			threads.push_back(async(launch::async, &MeshLoader::_loadMesh, this, filePath));
			threadStatuses.push_back(false);
		}
		else
		{
			threadStatuses.push_back(true);
		}
	}

	// Wait for all threads to finish
	for (size_t i = 0; i < threadStatuses.size(); i++)
	{
		// Check if mesh is not processed yet
		if (!threadStatuses[i])
		{
			// Retrieve return value
			auto returnValue = threads[i].get();

			// Check mesh status
			if (returnValue.second.empty())
			{
				Logger::throwWarning(returnValue.first);
			}
			else
			{
				// Extract any texture paths
				for (const auto& part : returnValue.second)
				{
					if (!part.getDiffuseMapPath().empty()) // Diffuse map
					{
						resultingTexturePaths.push_back(part.getDiffuseMapPath());
					}
					if (!part.getEmissionMapPath().empty()) // Emission map
					{
						resultingTexturePaths.push_back(part.getEmissionMapPath());
					}
					if (!part.getNormalMapPath().empty()) // Normal map
					{
						resultingTexturePaths.push_back(part.getNormalMapPath());
					}
					if (!part.getReflectionMapPath().empty()) // Reflection map
					{
						resultingTexturePaths.push_back(part.getReflectionMapPath());
					}
				}

				// Cache mesh
				_meshCache[uniqueFilePaths[i]] = returnValue.second;

				// Logging
				Logger::throwInfo("Loaded mesh: \"" + uniqueFilePaths[i] + "\"");
			}
		}
	}
}

const vector<MeshPart>* MeshLoader::loadMesh(const string& filePath)
{
BEGIN:
	// Search cache
	auto cacheIterator = _meshCache.find(filePath);

	// Return from cache
	if (cacheIterator != _meshCache.end())
	{
		return &cacheIterator->second;
	}

	// Load mesh
	auto returnValue = _loadMesh(filePath);

	// Check mesh status
	if (returnValue.second.empty())
	{
		Logger::throwWarning(returnValue.first);
		return {};
	}
	else
	{
		// Cache mesh
		_meshCache.insert(make_pair(filePath, returnValue.second));

		// Logging
		Logger::throwInfo("Loaded mesh: \"" + filePath + "\"");

		// Return new model
		goto BEGIN;
	}
}

void MeshLoader::clearMeshCache(const string& filePath)
{
	if (_meshCache.find(filePath) != _meshCache.end())
	{
		_meshCache.erase(filePath);
	}
}