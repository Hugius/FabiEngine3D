#include "obj_loader.hpp"
#include "logger.hpp"

#pragma warning(disable:4996) // Disabling annoying warning

#include <GLEW\\glew.h>
#include <filesystem>

vector<ObjPart> & OBJLoader::loadOBJ(const string& filePath, bool calculateTangents)
{
	// Check if mesh data was loaded already, if not, load data and store in std::map
	begin : auto iterator = _objPartsMap.find(filePath); // Search for existing OBJ parts
	if (iterator == _objPartsMap.end()) 
	{
		_objPartsMap.insert(std::make_pair(filePath, _loadOBJ(filePath, calculateTangents))); // Insert new data
		goto begin;
	}
	else
	{
		return iterator->second; // Return the corresponding OBJ parts
	}
}

void OBJLoader::clearOBJCache(const string& filePath)
{
	if (_objPartsMap.find(filePath) != _objPartsMap.end())
	{
		_objPartsMap.erase(filePath);
	}
}

vector<ObjPart> OBJLoader::_loadOBJ(const string& filePath, bool calculateTangents)
{
	// Declare variables
	vector<ObjPart> objParts;
	vector<vec3> temp_positions;
	vector<vec2> temp_uvs;
	vector<vec3> temp_normals;
	string selectedPartName = "";
	string tempDiffuseMapName = "";
	string tempLightMapName = "";
	string tempReflectionMapName = "";

	// Get application root directory
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len);
	string rootDir = buffer;
	rootDir = rootDir.substr(0, rootDir.size() - 25);

	// Load .obj file
	string path = rootDir + filePath;
	FILE * file = fopen(path.c_str(), "r");
	if (!std::filesystem::exists(path) || filePath == "")
	{
		Logger::getInst().throwError("Could not load .obj file: " + filePath);
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
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_positions.push_back(vertex);

			continue;
		}
		else if (strcmp(lineHeader, "vt") == 0) // Uv coords
		{
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);

			continue;
		}
		else if (strcmp(lineHeader, "vn") == 0) // Normals
		{
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_PART") == 0) // New part
		{
			char name[128];
			fscanf(file, "%s\n", name);
			selectedPartName = name;

			// Reset material names
			tempDiffuseMapName = "";
			tempLightMapName = "";
			tempReflectionMapName = "";

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_DIFFUSE_MAP") == 0) // Diffuse material
		{
			if (selectedPartName != "")
			{
				char name[128];
				fscanf(file, "%s\n", name);
				tempDiffuseMapName = name;
			}

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_LIGHT_MAP") == 0) // Light material
		{
			if (selectedPartName != "")
			{
				char name[128];
				fscanf(file, "%s\n", name);
				tempLightMapName = name;
			}

			continue;
		}
		else if (strcmp(lineHeader, "FE3D_REFLECTION_MAP") == 0) // Light material
		{
			if (selectedPartName != "")
			{
				char name[128];
				fscanf(file, "%s\n", name);
				tempReflectionMapName = name;
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
				Logger::getInst().throwError("Too many or not enough faces at file: " + filePath);
			}

			bool alreadyExisting = false;

			// Check if able to add to existing OBJ part
			for (auto& objPart : objParts)
			{
				// Find OBJ part
				if (objPart.partName == selectedPartName)
				{
					alreadyExisting = true;

					// Add vertices
					for (int i = 0; i < 3; i++)
					{
						objPart.vertices.push_back(temp_positions[posIndex[i] - 1]);
						objPart.uvCoords.push_back(temp_uvs[uvIndex[i] - 1]);
						objPart.normals.push_back(temp_normals[normalIndex[i] - 1]);
					}

					// Set material names
					objPart.diffuseMapName = tempDiffuseMapName;
					objPart.lightMapName = tempLightMapName;
					objPart.reflectionMapName = tempReflectionMapName;

					break;
				}
			}

			// Create new OBJ part
			if (!alreadyExisting)
			{
				ObjPart newPart;

				// Add vertices
				for (int i = 0; i < 3; i++)
				{
					newPart.vertices.push_back(temp_positions[posIndex[i] - 1]);
					newPart.uvCoords.push_back(temp_uvs[uvIndex[i] - 1]);
					newPart.normals.push_back(temp_normals[normalIndex[i] - 1]);
				}

				// Set OBJ part names
				newPart.partName = selectedPartName;
				newPart.diffuseMapName = tempDiffuseMapName;
				newPart.lightMapName = tempLightMapName;
				newPart.reflectionMapName = tempReflectionMapName;

				// Add new OBJ part
				objParts.push_back(newPart);
			}
		}
	}

	// Calculate tangents for normal mapping
	if (calculateTangents)
	{
		for (auto& objPart : objParts)
		{
			for (size_t i = 0; i < objPart.vertices.size(); i += 3)
			{
				// Vertices of 1 triangle
				vec3 v0 = objPart.vertices[i + 0];
				vec3 v1 = objPart.vertices[i + 1];
				vec3 v2 = objPart.vertices[i + 2];

				// Shortcuts for UVs
				vec2 uv0 = objPart.uvCoords[i + 0];
				vec2 uv1 = objPart.uvCoords[i + 1];
				vec2 uv2 = objPart.uvCoords[i + 2];

				// Vertex delta
				vec3 deltaPos1 = v1 - v0;
				vec3 deltaPos2 = v2 - v0;

				// UV delta
				vec2 deltaUV1 = uv1 - uv0;
				vec2 deltaUV2 = uv2 - uv0;

				// Calculate tangent vector
				float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

				// Add to current OBJ part
				objPart.tangents.push_back(tangent);
				objPart.tangents.push_back(tangent);
				objPart.tangents.push_back(tangent);
			}
		}
	}

	// Error checking
	if (objParts.empty())
	{
		Logger::getInst().throwError("Incorrect or too little content at file: " + filePath);
	}

	// Logging
	Logger::getInst().throwInfo("Loaded OBJ model: " + filePath);

	// Return new OBJ parts
	return objParts;
}