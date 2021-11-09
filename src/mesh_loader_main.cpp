#include "mesh_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#pragma warning(disable:4996) // Disabling annoying warning

using std::make_shared;

pair<string, vector<shared_ptr<MeshPart>>> MeshLoader::_loadMesh(const string& filePath)
{
	// Declare variables
	vector<shared_ptr<MeshPart>> meshParts;
	vector<Vec3> temp_positions;
	vector<Vec2> temp_uvs;
	vector<Vec3> temp_normals;
	string selectedPartID = "";

	// Get application root directory
	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	// Load .obj file
	string path = rootDirectoryPath + filePath;
	FILE* file = fopen(path.c_str(), "r");
	if(!Tools::isFileExisting(path) || filePath.empty())
	{
		string warningMessage = string("Cannot load mesh file: \"" + filePath + "\"!");
		return make_pair(warningMessage, meshParts);
	}

	// Fill the vector with the data from the file
	while(true)
	{
		// Scan line to string
		char* lineHeader = new char[128];
		int res = fscanf(file, "%s", lineHeader);

		// Check for end of file
		if(res == EOF)
		{
			break;
		}

		// File content
		if(strcmp(lineHeader, "FE3D_PART") == 0) // New part
		{
			char* ID = new char[128];
			auto temp = fscanf(file, "%s\n", ID);
			selectedPartID = string(ID);

			// Cannot be a questionmark
			if(selectedPartID == "?")
			{
				string warningMessage = string("Mesh part ID cannot be '?' in mesh file: \"" + filePath + "\"!");
				return make_pair(warningMessage, meshParts);
			}

			continue;
		}
		else if(strcmp(lineHeader, "v") == 0) // Vertices
		{
			Vec3 vertex;
			auto temp = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_positions.push_back(vertex);

			continue;
		}
		else if(strcmp(lineHeader, "vt") == 0) // UV coordinates
		{
			Vec2 uv;
			auto temp = fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);

			continue;
		}
		else if(strcmp(lineHeader, "vn") == 0) // Normals
		{
			Vec3 normal;
			auto temp = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);

			continue;
		}
		else if(strcmp(lineHeader, "f") == 0) // Faces (triangle data)
		{
			// Temporary values
			unsigned int posIndex[3];
			unsigned int uvIndex[3];
			unsigned int normalIndex[3];

			// Read face indices
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
								 &posIndex[0], &uvIndex[0], &normalIndex[0],
								 &posIndex[1], &uvIndex[1], &normalIndex[1],
								 &posIndex[2], &uvIndex[2], &normalIndex[2]);

			// Check if face amount is correct (3x3)
			if(matches != 9)
			{
				string warningMessage = string("Too many or not enough faces in mesh file: \"" + filePath + "\"");
				return make_pair(warningMessage, meshParts);
			}

			// Check if able to add to existing mesh part
			bool isAlreadyExisting = false;
			for(const auto& meshPart : meshParts)
			{
				// Find mesh part
				if(meshPart->getID() == selectedPartID)
				{
					// Prevent mesh part creation
					isAlreadyExisting = true;

					// Add data
					for(int i = 0; i < 3; i++)
					{
						meshPart->addVertex(temp_positions[posIndex[i] - 1]);
						meshPart->addUV(temp_uvs[uvIndex[i] - 1]);
						meshPart->addNormal(temp_normals[normalIndex[i] - 1]);
					}

					// Part is found
					break;
				}
			}

			// Create new mesh part
			if(!isAlreadyExisting)
			{
				// Create mesh part
				MeshPart newPart(selectedPartID);

				// Add first data
				for(int i = 0; i < 3; i++)
				{
					newPart.addVertex(temp_positions[posIndex[i] - 1]);
					newPart.addUV(temp_uvs[uvIndex[i] - 1]);
					newPart.addNormal(temp_normals[normalIndex[i] - 1]);
				}

				// Add new mesh part
				meshParts.push_back(make_shared<MeshPart>(newPart));
			}
		}
	}

	// Calculate tangents for normal mapping
	for(const auto& meshPart : meshParts)
	{
		for(size_t i = 0; i < meshPart->getVertices().size(); i += 3)
		{
			// Vertices of 1 triangle
			Vec3 v0 = meshPart->getVertices()[i + 0];
			Vec3 v1 = meshPart->getVertices()[i + 1];
			Vec3 v2 = meshPart->getVertices()[i + 2];

			// Shortcuts for UVs
			Vec2 uv0 = meshPart->getUVs()[i + 0];
			Vec2 uv1 = meshPart->getUVs()[i + 1];
			Vec2 uv2 = meshPart->getUVs()[i + 2];

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
			meshPart->addTangent(tangent);
			meshPart->addTangent(tangent);
			meshPart->addTangent(tangent);
		}
	}

	// Validate mesh parts
	if(meshParts.empty())
	{
		string warningMessage = string("Incorrect or too little content in mesh file: \"" + filePath + "\"");
		return make_pair(warningMessage, meshParts);
	}

	// Return new mesh parts
	return make_pair("", meshParts);
}