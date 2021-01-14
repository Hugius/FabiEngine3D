#include "obj_loader.hpp"
#include "logger.hpp"

#pragma warning(disable:4996) // Disabling annoying warning

#include <GLEW\\glew.h>
#include <filesystem>

const vector<ObjPart>& OBJLoader::loadOBJ(const string& filePath, bool calculateTangents)
{
	// Check if mesh data was loaded already, if not, load data and store in std::map
	begin : auto iterator = _objPartsMap.find(filePath); // Search for existing OBJ parts
	if (iterator == _objPartsMap.end()) 
	{
		auto loadedModel = _loadOBJ(filePath, calculateTangents);

		// Determine if needs to be cached
		if (loadedModel.empty())
		{
			return {};
		}
		else
		{
			_objPartsMap.insert(std::make_pair(filePath, loadedModel)); // Insert new data
			goto begin;
		}
	}
	else
	{
		// Calculate tangents once for this model
		if (calculateTangents && iterator->second[0].tangents.empty())
		{
			_calculateTangents(iterator->second);
		}

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
	vector<Vec3> temp_positions;
	vector<Vec2> temp_uvs;
	vector<Vec3> temp_normals;
	string selectedPartName = "";
	string tempDiffuseMapPath = "";
	string tempLightMapPath = "";
	string tempNormalMapPath = "";
	string tempReflectionMapPath = "";

	// Get application root directory
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len);
	string rootDir = buffer;
	rootDir = rootDir.substr(0, rootDir.size() - string("bin\\FabiEngine3D.exe").size());

	// Load .obj file
	string path = rootDir + filePath;
	FILE * file = fopen(path.c_str(), "r");
	if (!std::filesystem::exists(path) || filePath == "")
	{
		Logger::throwWarning("Cannot open OBJ file: \"" + filePath + "\"");
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
				Logger::throwWarning("Too many or not enough faces at OBJ file: \"" + filePath + "\"");
				return {};
			}

			bool alreadyExisting = false;

			// Check if able to add to existing OBJ part
			for (auto& objPart : objParts)
			{
				// Find OBJ part
				if (objPart.name == selectedPartName)
				{
					alreadyExisting = true;

					// Add vertices
					for (int i = 0; i < 3; i++)
					{
						objPart.vertices.push_back(temp_positions[posIndex[i] - 1]);
						objPart.uvCoords.push_back(temp_uvs[uvIndex[i] - 1]);
						objPart.normals.push_back(temp_normals[normalIndex[i] - 1]);
					}

					// Part is found
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

				// Set OBJ part name
				newPart.name = selectedPartName;

				// Set texture map paths
				newPart.diffuseMapPath = tempDiffuseMapPath;
				newPart.lightMapPath = tempLightMapPath;
				newPart.normalMapPath = tempNormalMapPath;
				newPart.reflectionMapPath = tempReflectionMapPath;

				// Add new OBJ part
				objParts.push_back(newPart);
			}
		}
	}

	// Calculate tangents for all obj parts
	if (calculateTangents)
	{
		_calculateTangents(objParts);
	}

	// Error checking
	if (objParts.empty())
	{
		Logger::throwWarning("Incorrect or too little content at OBJ file: \"" + filePath + "\"");
		return {};
	}

	// Logging
	Logger::throwInfo("Loaded OBJ model: \"" + filePath + "\"");

	// Return new OBJ parts
	return objParts;
}

void OBJLoader::_calculateTangents(vector<ObjPart>& objParts)
{
	// Calculate tangents for normal mapping
	for (auto& objPart : objParts)
	{
		for (size_t i = 0; i < objPart.vertices.size(); i += 3)
		{
			// Vertices of 1 triangle
			Vec3 v0 = objPart.vertices[i + 0];
			Vec3 v1 = objPart.vertices[i + 1];
			Vec3 v2 = objPart.vertices[i + 2];

			// Shortcuts for UVs
			Vec2 uv0 = objPart.uvCoords[i + 0];
			Vec2 uv1 = objPart.uvCoords[i + 1];
			Vec2 uv2 = objPart.uvCoords[i + 2];

			// Vertex delta
			Vec3 deltaPos1 = v1 - v0;
			Vec3 deltaPos2 = v2 - v0;

			// UV delta
			Vec2 deltaUV1 = uv1 - uv0;
			Vec2 deltaUV2 = uv2 - uv0;

			// Calculate tangent vector
			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			Vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

			// Add to current OBJ part
			objPart.tangents.push_back(tangent);
			objPart.tangents.push_back(tangent);
			objPart.tangents.push_back(tangent);
		}
	}
}