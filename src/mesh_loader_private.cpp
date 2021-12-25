#include "mesh_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#pragma warning(disable:4996)

using std::make_shared;

pair<string, vector<shared_ptr<MeshPart>>> MeshLoader::_loadMesh(const string& filePath)
{
	vector<shared_ptr<MeshPart>> meshParts;
	vector<fvec3> temp_positions;
	vector<fvec2> temp_uvs;
	vector<fvec3> temp_normals;
	string selectedPartID = "";

	const auto rootDirectoryPath = Tools::getRootDirectoryPath();

	string path = rootDirectoryPath + filePath;
	FILE* file = fopen(path.c_str(), "r");
	if(!Tools::isFileExisting(path) || filePath.empty())
	{
		string warningMessage = string("Cannot load mesh: \"" + filePath + "\"!");
		return make_pair(warningMessage, meshParts);
	}

	while(true)
	{
		char* lineHeader = new char[128];
		int res = fscanf(file, "%s", lineHeader);

		if(res == EOF)
		{
			break;
		}

		if(strcmp(lineHeader, "FE3D_PART") == 0)
		{
			char* ID = new char[128];
			auto temp = fscanf(file, "%s\n", ID);
			selectedPartID = string(ID);

			if(selectedPartID == "?")
			{
				string warningMessage = string("Mesh part ID cannot be '?' in mesh file: \"" + filePath + "\"!");
				return make_pair(warningMessage, meshParts);
			}

			continue;
		}
		else if(strcmp(lineHeader, "v") == 0)
		{
			fvec3 vertex;
			auto temp = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_positions.push_back(vertex);

			continue;
		}
		else if(strcmp(lineHeader, "vt") == 0)
		{
			fvec2 uv;
			auto temp = fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);

			continue;
		}
		else if(strcmp(lineHeader, "vn") == 0)
		{
			fvec3 normal;
			auto temp = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);

			continue;
		}
		else if(strcmp(lineHeader, "f") == 0)
		{
			unsigned int posIndex[3];
			unsigned int uvIndex[3];
			unsigned int normalIndex[3];

			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
								 &posIndex[0], &uvIndex[0], &normalIndex[0],
								 &posIndex[1], &uvIndex[1], &normalIndex[1],
								 &posIndex[2], &uvIndex[2], &normalIndex[2]);

			if(matches != 9)
			{
				string warningMessage = string("Too many or not enough faces in mesh file: \"" + filePath + "\"");
				return make_pair(warningMessage, meshParts);
			}

			bool isAlreadyExisting = false;
			for(const auto& meshPart : meshParts)
			{
				if(meshPart->getID() == selectedPartID)
				{
					isAlreadyExisting = true;

					for(int i = 0; i < 3; i++)
					{
						meshPart->addVertex(temp_positions[posIndex[i] - 1]);
						meshPart->addUV(temp_uvs[uvIndex[i] - 1]);
						meshPart->addNormal(temp_normals[normalIndex[i] - 1]);
					}

					break;
				}
			}

			if(!isAlreadyExisting)
			{
				MeshPart newPart(selectedPartID);

				for(int i = 0; i < 3; i++)
				{
					newPart.addVertex(temp_positions[posIndex[i] - 1]);
					newPart.addUV(temp_uvs[uvIndex[i] - 1]);
					newPart.addNormal(temp_normals[normalIndex[i] - 1]);
				}

				meshParts.push_back(make_shared<MeshPart>(newPart));
			}
		}
	}

	for(const auto& meshPart : meshParts)
	{
		for(size_t i = 0; i < meshPart->getVertices().size(); i += 3)
		{
			fvec3 v0 = meshPart->getVertices()[i + 0];
			fvec3 v1 = meshPart->getVertices()[i + 1];
			fvec3 v2 = meshPart->getVertices()[i + 2];

			fvec2 uv0 = meshPart->getUVs()[i + 0];
			fvec2 uv1 = meshPart->getUVs()[i + 1];
			fvec2 uv2 = meshPart->getUVs()[i + 2];

			fvec3 deltaPos1 = (v1 - v0);
			fvec3 deltaPos2 = (v2 - v0);

			fvec2 deltaUV1 = (uv1 - uv0);
			fvec2 deltaUV2 = (uv2 - uv0);

			float r = (1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x));
			fvec3 tangent = ((deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r);

			meshPart->addTangent(tangent);
			meshPart->addTangent(tangent);
			meshPart->addTangent(tangent);
		}
	}

	if(meshParts.empty())
	{
		string warningMessage = string("Incorrect or too little content in mesh file: \"" + filePath + "\"");
		return make_pair(warningMessage, meshParts);
	}

	return make_pair("", meshParts);
}