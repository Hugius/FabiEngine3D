#include "mesh_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;

void MeshLoader::cacheMeshesMultiThreaded(const vector<string>& meshPaths, vector<string>& resultingTexturePaths)
{
	// Temporary values
	vector<std::future<vector<MeshPart>>> threads;
	vector<bool> meshStatuses;

	// Remove duplicates
	auto tempFilePaths = set<string>(meshPaths.begin(), meshPaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for (const auto& filePath : uniqueFilePaths)
	{
		// Check if mesh is not already cached
		if (_meshCache.find(filePath) == _meshCache.end())
		{
			threads.push_back(std::async(std::launch::async, &MeshLoader::_loadMesh, this, filePath));
			meshStatuses.push_back(false);
		}
		else
		{
			meshStatuses.push_back(true);
		}
	}

	// Wait for all threads to finish
	for (size_t i = 0; i < meshStatuses.size(); i++)
	{
		// Check if mesh is not processed yet
		if (!meshStatuses[i])
		{
			// Retrieve mesh parts
			auto meshParts = threads[i].get();

			// Check if model loading went well
			if (!meshParts.empty())
			{
				// Logging
				Logger::throwInfo("Loaded mesh: \"" + uniqueFilePaths[i] + "\"");

				// Cache model
				_meshCache[uniqueFilePaths[i]] = meshParts;
			}

			// Extract possible texture paths
			for (const auto& part : meshParts)
			{
				if (!part.diffuseMapPath.empty()) // Diffuse map
				{
					resultingTexturePaths.push_back(part.diffuseMapPath);
				}
				if (!part.emissionMapPath.empty()) // Emission map
				{
					resultingTexturePaths.push_back(part.emissionMapPath);
				}
				if (!part.normalMapPath.empty()) // Normal map
				{
					resultingTexturePaths.push_back(part.normalMapPath);
				}
				if (!part.reflectionMapPath.empty()) // Reflection map
				{
					resultingTexturePaths.push_back(part.reflectionMapPath);
				}
			}
		}
	}
}

const vector<MeshPart>* MeshLoader::loadMesh(const string& filePath)
{
	// Check if mesh data was loaded already, if not, load data and store in std::map
BEGIN: auto iterator = _meshCache.find(filePath); // Search for existing mesh parts
	if (iterator == _meshCache.end()) 
	{
		// Load mesh
		auto loadedModel = _loadMesh(filePath);

		// Check model status
		if (loadedModel.empty())
		{
			return nullptr;
		}
		else
		{
			// Logging
			Logger::throwInfo("Loaded mesh: \"" + filePath + "\"");

			// Cache model
			_meshCache.insert(make_pair(filePath, loadedModel));

			// Return new model
			goto BEGIN;
		}
	}
	else
	{
		return &iterator->second; // Return the corresponding mesh parts
	}
}

void MeshLoader::clearMeshCache(const string& filePath)
{
	if (_meshCache.find(filePath) != _meshCache.end())
	{
		_meshCache.erase(filePath);
	}
}