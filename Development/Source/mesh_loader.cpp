#include "mesh_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#pragma warning(disable:4996) // Disabling annoying warning

#include <GLEW\\glew.h>
#include <filesystem>
#include <future>
#include <set>

void MeshLoader::cacheMeshesMultiThreaded(const vector<string>& meshPaths, vector<string>& resultingTexturePaths)
{
	// Temporary values
	vector<std::future<vector<MeshPart>>> threads;
	vector<bool> meshStatuses;

	// Remove duplicates
	auto tempFilePaths = std::set<string>(meshPaths.begin(), meshPaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	// Start all loading threads
	for (const auto& filePath : uniqueFilePaths)
	{
		// Check if mesh is not already cached
		if (_meshCache.find(filePath) == _meshCache.end())
		{
			threads.push_back(std::async(std::launch::async, &MeshLoader::_loadMesh, this, filePath, false));
			meshStatuses.push_back(false);
		}
		else
		{
			meshStatuses.push_back(true);
		}
	}

	// Wait for all threads to finish
	for (unsigned int i = 0; i < meshStatuses.size(); i++)
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
				if (!part.lightMapPath.empty()) // Light map
				{
					resultingTexturePaths.push_back(part.lightMapPath);
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

const vector<MeshPart>& MeshLoader::loadMesh(const string& filePath, bool calculateTangents)
{
	// Check if mesh data was loaded already, if not, load data and store in std::map
	begin : auto iterator = _meshCache.find(filePath); // Search for existing mesh parts
	if (iterator == _meshCache.end()) 
	{
		// Load mesh
		auto loadedModel = _loadMesh(filePath, calculateTangents);

		// Check model status
		if (loadedModel.empty())
		{
			return {};
		}
		else
		{
			// Logging
			Logger::throwInfo("Loaded mesh: \"" + filePath + "\"");

			// Cache model
			_meshCache.insert(std::make_pair(filePath, loadedModel));

			// Return new model
			goto begin;
		}
	}
	else
	{
		// Calculate tangents once for this model
		if (calculateTangents)
		{
			_calculateTangents(iterator->second);
		}

		return iterator->second; // Return the corresponding mesh parts
	}
}

void MeshLoader::clearMeshCache(const string& filePath)
{
	if (_meshCache.find(filePath) != _meshCache.end())
	{
		_meshCache.erase(filePath);
	}
}

vector<MeshPart> MeshLoader::_loadMesh(const string& filePath, bool calculateTangents)
{
	// Declare variables
	vector<MeshPart> meshParts;
	vector<Vec3> temp_positions;
	vector<Vec2> temp_uvs;
	vector<Vec3> temp_normals;
	string selectedPartName = "";
	string tempDiffuseMapPath = "";
	string tempLightMapPath = "";
	string tempNormalMapPath = "";
	string tempReflectionMapPath = "";

	// Get application root directory
	string rootDir = Tools::getInst().getRootDirectory();

	// Load .obj file
	string path = rootDir + filePath;
	FILE * file = fopen(path.c_str(), "r");
	if (!std::filesystem::exists(path) || filePath == "")
	{
		Logger::throwWarning("Cannot open mesh file: \"" + filePath + "\"");
		return {};
	}

	// Fill the vector with the data from the file
	while (true)
	{
		// Check for end of file
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}
		
		// File content
		if (strcmp(lineHeader, "v") == 0) // Vertices
		{
			Vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_positions.push_back(vertex);

			continue;
		}
		else if (strcmp(lineHeader, "vt") == 0) // Uv coords
		{
			Vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);

			continue;
		}
		else if (strcmp(lineHeader, "vn") == 0) // Normals
		{
			Vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_PART") == 0) // New part
		{
			char name[128];
			fscanf(file, "%s\n", name);
			selectedPartName = name;

			// Cannot be a questionmark
			if (selectedPartName == "?")
			{
				Logger::throwError("Model part name cannot be '?' of model with filepath \"" + filePath + "\"!");
			}

			// Reset material paths
			tempDiffuseMapPath = "";
			tempLightMapPath = "";
			tempReflectionMapPath = "";
			tempNormalMapPath = "";

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_DIFFUSE_MAP") == 0) // Diffuse map material
		{
			if (selectedPartName != "")
			{
				char name[128];
				fscanf(file, "%s\n", name);
				tempDiffuseMapPath = name;
			}

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_LIGHT_MAP") == 0) // Light map material
		{
			if (selectedPartName != "")
			{
				char name[128];
				fscanf(file, "%s\n", name);
				tempLightMapPath = name;
			}

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_REFLECTION_MAP") == 0) // Reflection map material
		{
			if (selectedPartName != "")
			{
				char name[128];
				fscanf(file, "%s\n", name);
				tempReflectionMapPath = name;
			}

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_NORMAL_MAP") == 0) // Normal map material
		{
			if (selectedPartName != "")
			{
				char name[128];
				fscanf(file, "%s\n", name);
				tempNormalMapPath = name;
			}

			continue;
		}
		else if (strcmp(lineHeader, "f") == 0) // Faces (triangle data)
		{
			// Declare variables
			GLuint posIndex[3];
			GLuint uvIndex[3];
			GLuint normalIndex[3];
			int matches;

			// Read face indices
			matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
				&posIndex[0], &uvIndex[0], &normalIndex[0], 
				&posIndex[1], &uvIndex[1], &normalIndex[1], 
				&posIndex[2], &uvIndex[2], &normalIndex[2]);

			// Check if face amount is correct (3x3)
			if (matches != 9)
			{
				Logger::throwWarning("Too many or not enough faces at mesh file: \"" + filePath + "\"");
				return {};
			}

			bool alreadyExisting = false;

			// Check if able to add to existing mesh part
			for (auto& meshPart : meshParts)
			{
				// Find mesh part
				if (meshPart.name == selectedPartName)
				{
					alreadyExisting = true;

					// Add vertices
					for (int i = 0; i < 3; i++)
					{
						meshPart.vertices.push_back(temp_positions[posIndex[i] - 1]);
						meshPart.uvCoords.push_back(temp_uvs[uvIndex[i] - 1]);
						meshPart.normals.push_back(temp_normals[normalIndex[i] - 1]);
					}

					// Part is found
					break;
				}
			}

			// Create new mesh part
			if (!alreadyExisting)
			{
				MeshPart newPart;

				// Add vertices
				for (int i = 0; i < 3; i++)
				{
					newPart.vertices.push_back(temp_positions[posIndex[i] - 1]);
					newPart.uvCoords.push_back(temp_uvs[uvIndex[i] - 1]);
					newPart.normals.push_back(temp_normals[normalIndex[i] - 1]);
				}

				// Set mesh part name
				newPart.name = selectedPartName;

				// Set texture map paths
				newPart.diffuseMapPath = tempDiffuseMapPath.empty() ? "" : string("game_assets\\textures\\diffuse_maps\\" + tempDiffuseMapPath);
				newPart.lightMapPath = tempLightMapPath.empty() ? "" : string("game_assets\\textures\\light_maps\\" + tempLightMapPath);
				newPart.normalMapPath = tempNormalMapPath.empty() ? "" : string("game_assets\\textures\\normal_maps\\" + tempNormalMapPath);
				newPart.reflectionMapPath = tempReflectionMapPath.empty() ? "" : string("game_assets\\textures\\reflection_maps\\" + tempReflectionMapPath);

				// Add new mesh part
				meshParts.push_back(newPart);
			}
		}
	}

	// Calculate tangents for all mesh parts
	if (calculateTangents)
	{
		_calculateTangents(meshParts);
	}

	// Error checking
	if (meshParts.empty())
	{
		Logger::throwWarning("Incorrect or too little content at mesh file: \"" + filePath + "\"");
		return {};
	}

	// Return new mesh parts
	return meshParts;
}

void MeshLoader::_calculateTangents(vector<MeshPart>& meshParts)
{
	// Calculate tangents for normal mapping
	for (auto& meshPart : meshParts)
	{
		for (size_t i = 0; i < meshPart.vertices.size(); i += 3)
		{
			// Vertices of 1 triangle
			Vec3 v0 = meshPart.vertices[i + 0];
			Vec3 v1 = meshPart.vertices[i + 1];
			Vec3 v2 = meshPart.vertices[i + 2];

			// Shortcuts for UVs
			Vec2 uv0 = meshPart.uvCoords[i + 0];
			Vec2 uv1 = meshPart.uvCoords[i + 1];
			Vec2 uv2 = meshPart.uvCoords[i + 2];

			// Vertex delta
			Vec3 deltaPos1 = v1 - v0;
			Vec3 deltaPos2 = v2 - v0;

			// UV delta
			Vec2 deltaUV1 = uv1 - uv0;
			Vec2 deltaUV2 = uv2 - uv0;

			// Calculate tangent vector
			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			Vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

			// Add to current mesh part
			meshPart.tangents.push_back(tangent);
			meshPart.tangents.push_back(tangent);
			meshPart.tangents.push_back(tangent);
		}
	}
}