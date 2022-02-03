#include "mesh_loader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <array>

using std::replace;
using std::make_shared;
using std::ifstream;
using std::istringstream;
using std::array;

shared_ptr<Mesh> MeshLoader::_loadMesh(const string& filePath)
{
	vector<shared_ptr<MeshPart>> meshParts;
	vector<fvec3> temp_positions;
	vector<fvec2> temp_uvs;
	vector<fvec3> temp_normals;
	string selectedPartId = "";

	const auto rootPath = Tools::getRootDirectoryPath();
	const auto fullFilePath = string(rootPath + filePath);
	auto file = ifstream(fullFilePath);
	if(!file)
	{
		return nullptr;
	}

	string line;
	while(getline(file, line))
	{
		string lineType;

		replace(line.begin(), line.end(), '/', ' ');

		istringstream iss(line);

		iss >> lineType;

		if(lineType == "FE3D_PART")
		{
			string id;
			iss >> id;

			selectedPartId = string(id);

			if(selectedPartId == "?")
			{
				return nullptr;
			}

			continue;
		}
		else if(lineType == "v")
		{
			float x, y, z;
			iss
				>> x
				>> y
				>> z;

			temp_positions.push_back(fvec3(x, y, z));

			continue;
		}
		else if(lineType == "vt")
		{
			float x, y;
			iss
				>> x
				>> y;

			temp_uvs.push_back(fvec2(x, y));

			continue;
		}
		else if(lineType == "vn")
		{
			float x, y, z;
			iss
				>> x
				>> y
				>> z;

			temp_normals.push_back(fvec3(x, y, z));

			continue;
		}
		else if(lineType == "f")
		{
			array<unsigned int, 9> indices = {};
			iss
				>> indices[0]
				>> indices[1]
				>> indices[2]
				>> indices[3]
				>> indices[4]
				>> indices[5]
				>> indices[6]
				>> indices[7]
				>> indices[8];

			for(auto& index : indices)
			{
				index--;
			}

			if(temp_positions.empty() || temp_uvs.empty() || temp_normals.empty())
			{
				return nullptr;
			}

			bool isAlreadyExisting = false;
			for(const auto& meshPart : meshParts)
			{
				if(meshPart->getId() == selectedPartId)
				{
					isAlreadyExisting = true;

					meshPart->addPosition(temp_positions[indices[0]]);
					meshPart->addPosition(temp_positions[indices[3]]);
					meshPart->addPosition(temp_positions[indices[6]]);
					meshPart->addUv(temp_uvs[indices[1]]);
					meshPart->addUv(temp_uvs[indices[4]]);
					meshPart->addUv(temp_uvs[indices[7]]);
					meshPart->addNormal(temp_normals[indices[2]]);
					meshPart->addNormal(temp_normals[indices[5]]);
					meshPart->addNormal(temp_normals[indices[8]]);

					break;
				}
			}

			if(!isAlreadyExisting)
			{
				auto newPart = make_shared<MeshPart>(selectedPartId);

				newPart->addPosition(temp_positions[indices[0]]);
				newPart->addPosition(temp_positions[indices[3]]);
				newPart->addPosition(temp_positions[indices[6]]);
				newPart->addUv(temp_uvs[indices[1]]);
				newPart->addUv(temp_uvs[indices[4]]);
				newPart->addUv(temp_uvs[indices[7]]);
				newPart->addNormal(temp_normals[indices[2]]);
				newPart->addNormal(temp_normals[indices[5]]);
				newPart->addNormal(temp_normals[indices[8]]);

				meshParts.push_back(newPart);
			}
		}
	}

	for(const auto& meshPart : meshParts)
	{
		for(size_t i = 0; i < meshPart->getPositions().size(); i += 3)
		{
			fvec3 v0 = meshPart->getPositions()[i + 0];
			fvec3 v1 = meshPart->getPositions()[i + 1];
			fvec3 v2 = meshPart->getPositions()[i + 2];

			fvec2 uv0 = meshPart->getUvs()[i + 0];
			fvec2 uv1 = meshPart->getUvs()[i + 1];
			fvec2 uv2 = meshPart->getUvs()[i + 2];

			fvec3 deltaPosition1 = (v1 - v0);
			fvec3 deltaPosition2 = (v2 - v0);

			fvec2 deltaUv1 = (uv1 - uv0);
			fvec2 deltaUv2 = (uv2 - uv0);

			float r = (1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x));
			fvec3 tangent = ((deltaPosition1 * deltaUv2.y - deltaPosition2 * deltaUv1.y) * r);

			meshPart->addTangent(tangent);
			meshPart->addTangent(tangent);
			meshPart->addTangent(tangent);
		}
	}

	if(meshParts.empty())
	{
		return nullptr;
	}

	if((meshParts.size() == 1) && !meshParts[0]->getId().empty())
	{
		return nullptr;
	}

	auto mesh = make_shared<Mesh>();

	for(const auto& meshPart : meshParts)
	{
		mesh->addPart(meshPart);
	}

	return mesh;
}