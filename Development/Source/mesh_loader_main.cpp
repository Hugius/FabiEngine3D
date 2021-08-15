#include "mesh_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#pragma warning(disable:4996) // Disabling annoying warning

#include <filesystem>

using std::filesystem::exists;

vector<MeshPart> MeshLoader::_loadMesh(const string& filePath)
{
	// Declare variables
	vector<MeshPart> meshParts;
	vector<Vec3> temp_positions;
	vector<Vec2> temp_uvs;
	vector<Vec3> temp_normals;
	string selectedPartID = "";
	string tempDiffuseMapPath = "";
	string tempEmissionMapPath = "";
	string tempNormalMapPath = "";
	string tempReflectionMapPath = "";

	// Get application root directory
	const auto rootDir = Tools::getRootDirectory();

	// Load .obj file
	string path = rootDir + filePath;
	FILE* file = fopen(path.c_str(), "r");
	if (!exists(path) || filePath.empty())
	{
		Logger::throwWarning("Cannot load mesh file: \"" + filePath + "\"!");
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
			auto temp = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_positions.push_back(vertex);

			continue;
		}
		else if (strcmp(lineHeader, "vt") == 0) // Uv coords
		{
			Vec2 uv;
			auto temp = fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);

			continue;
		}
		else if (strcmp(lineHeader, "vn") == 0) // Normals
		{
			Vec3 normal;
			auto temp = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_PART") == 0) // New part
		{
			char ID[128];
			auto temp = fscanf(file, "%s\n", ID);
			selectedPartID = ID;

			// Cannot be a questionmark
			if (selectedPartID == "?")
			{
				Logger::throwWarning("Mesh part ID cannot be '?' in mesh file: \"" + filePath + "\"!");
				return {};
			}

			// Reset material paths
			tempDiffuseMapPath = "";
			tempEmissionMapPath = "";
			tempReflectionMapPath = "";
			tempNormalMapPath = "";

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_DIFFUSE_MAP") == 0) // Diffuse map material
		{
			if (selectedPartID != "")
			{
				char path[128];
				auto temp = fscanf(file, "%s\n", path);
				tempDiffuseMapPath = path;
			}

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_EMISSION_MAP") == 0) // Emission map material
		{
			if (selectedPartID != "")
			{
				char path[128];
				auto temp = fscanf(file, "%s\n", path);
				tempEmissionMapPath = path;
			}

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_REFLECTION_MAP") == 0) // Reflection map material
		{
			if (selectedPartID != "")
			{
				char path[128];
				auto temp = fscanf(file, "%s\n", path);
				tempReflectionMapPath = path;
			}

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_NORMAL_MAP") == 0) // Normal map material
		{
			if (selectedPartID != "")
			{
				char path[128];
				auto temp = fscanf(file, "%s\n", path);
				tempNormalMapPath = path;
			}

			continue;
		}
		else if (strcmp(lineHeader, "f") == 0) // Faces (triangle data)
		{
			// Declare variables
			unsigned int posIndex[3];
			unsigned int uvIndex[3];
			unsigned int normalIndex[3];
			int matches;

			// Read face indices
			matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
				&posIndex[0], &uvIndex[0], &normalIndex[0], 
				&posIndex[1], &uvIndex[1], &normalIndex[1], 
				&posIndex[2], &uvIndex[2], &normalIndex[2]);

			// Check if face amount is correct (3x3)
			if (matches != 9)
			{
				Logger::throwWarning("Too many or not enough faces in mesh file: \"" + filePath + "\"");
				return {};
			}

			// Check if able to add to existing mesh part
			bool isAlreadyExisting = false;
			for (auto& meshPart : meshParts)
			{
				// Find mesh part
				if (meshPart.ID == selectedPartID)
				{
					isAlreadyExisting = true;

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
			if (!isAlreadyExisting)
			{
				MeshPart newPart;

				// Add vertices
				for (int i = 0; i < 3; i++)
				{
					newPart.vertices.push_back(temp_positions[posIndex[i] - 1]);
					newPart.uvCoords.push_back(temp_uvs[uvIndex[i] - 1]);
					newPart.normals.push_back(temp_normals[normalIndex[i] - 1]);
				}

				// Set mesh part ID
				newPart.ID = selectedPartID;

				// Set texture map paths
				newPart.diffuseMapPath = tempDiffuseMapPath.empty() ? "" : string("game_assets\\textures\\diffuse_maps\\" + tempDiffuseMapPath);
				newPart.emissionMapPath = tempEmissionMapPath.empty() ? "" : string("game_assets\\textures\\emission_maps\\" + tempEmissionMapPath);
				newPart.normalMapPath = tempNormalMapPath.empty() ? "" : string("game_assets\\textures\\normal_maps\\" + tempNormalMapPath);
				newPart.reflectionMapPath = tempReflectionMapPath.empty() ? "" : string("game_assets\\textures\\reflection_maps\\" + tempReflectionMapPath);

				// Add new mesh part
				meshParts.push_back(newPart);
			}
		}
	}

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
			Vec3 deltaPos1 = (v1 - v0);
			Vec3 deltaPos2 = (v2 - v0);

			// UV delta
			Vec2 deltaUV1 = (uv1 - uv0);
			Vec2 deltaUV2 = (uv2 - uv0);

			// Calculate tangent vector
			float r = (1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x));
			Vec3 tangent = ((deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r);

			// Add to current mesh part
			meshPart.tangents.push_back(tangent);
			meshPart.tangents.push_back(tangent);
			meshPart.tangents.push_back(tangent);
		}
	}

	// Validate mesh parts
	if (meshParts.empty())
	{
		Logger::throwWarning("Incorrect or too little content in mesh file: \"" + filePath + "\"");
		return {};
	}

	// Return new mesh parts
	return meshParts;
}