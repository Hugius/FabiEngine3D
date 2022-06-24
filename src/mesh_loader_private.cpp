#include "mesh_loader.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <array>

using std::replace;
using std::make_shared;
using std::ifstream;
using std::istringstream;
using std::array;

shared_ptr<Mesh> MeshLoader::_loadMesh(const string & filePath) const
{
	vector<shared_ptr<MeshPart>> meshParts = {};
	vector<fvec3> temp_positions = {};
	vector<fvec2> temp_uvs = {};
	vector<fvec3> temp_normals = {};
	string selectedPartId = "";

	const auto rootPath = Tools::getRootDirectoryPath();

	auto file = ifstream(rootPath + filePath);

	if(!file)
	{
		return nullptr;
	}

	string line = "";

	while(getline(file, line))
	{
		string lineType;

		replace(line.begin(), line.end(), '/', ' ');

		auto iss = istringstream(line);

		iss >> lineType;

		if(lineType == "FE3D_PART")
		{
			string partId;

			iss >> partId;

			if(partId.empty())
			{
				return nullptr;
			}

			if(any_of(partId.begin(), partId.end(), isspace))
			{
				return nullptr;
			}

			if(any_of(partId.begin(), partId.end(), isupper))
			{
				return nullptr;
			}

			if(partId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
			{
				return nullptr;
			}

			selectedPartId = partId;

			continue;
		}
		else if(lineType == "v")
		{
			float x;
			float y;
			float z;

			iss
				>> x
				>> y
				>> z;

			temp_positions.push_back(fvec3(x, y, z));

			continue;
		}
		else if(lineType == "vt")
		{
			float x;
			float y;

			iss
				>> x
				>> y;

			temp_uvs.push_back(fvec2(x, y));

			continue;
		}
		else if(lineType == "vn")
		{
			float x;
			float y;
			float z;

			iss
				>> x
				>> y
				>> z;

			temp_normals.push_back(fvec3(x, y, z));

			continue;
		}
		else if(lineType == "f")
		{
			array<int, 9> indices = {};

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

			if((temp_positions.size() < indices[0]) || (temp_positions.size() < indices[3]) || (temp_positions.size() < indices[6]))
			{
				return nullptr;
			}

			if((temp_uvs.size() < indices[1]) || (temp_uvs.size() < indices[4]) || (temp_uvs.size() < indices[7]))
			{
				return nullptr;
			}

			if((temp_normals.size() < indices[2]) || (temp_normals.size() < indices[5]) || (temp_normals.size() < indices[8]))
			{
				return nullptr;
			}

			for(auto & index : indices)
			{
				index--;
			}

			bool isAlreadyExisting = false;

			for(const auto & meshPart : meshParts)
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

	for(const auto & meshPart : meshParts)
	{
		for(int index = 0; index < static_cast<int>(meshPart->getPositions().size()); index += 3)
		{
			const auto v0 = meshPart->getPositions()[index + 0];
			const auto v1 = meshPart->getPositions()[index + 1];
			const auto v2 = meshPart->getPositions()[index + 2];

			const auto uv0 = meshPart->getUvs()[index + 0];
			const auto uv1 = meshPart->getUvs()[index + 1];
			const auto uv2 = meshPart->getUvs()[index + 2];

			const auto deltaPosition1 = (v1 - v0);
			const auto deltaPosition2 = (v2 - v0);

			const auto deltaUv1 = (uv1 - uv0);
			const auto deltaUv2 = (uv2 - uv0);

			const auto r = (1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x));
			const auto tangent = ((deltaPosition1 * deltaUv2.y - deltaPosition2 * deltaUv1.y) * r);

			meshPart->addTangent(tangent);
			meshPart->addTangent(tangent);
			meshPart->addTangent(tangent);
		}
	}

	if(meshParts.empty())
	{
		return nullptr;
	}
	else if(meshParts.size() == 1)
	{
		if(!meshParts[0]->getId().empty())
		{
			return nullptr;
		}
	}
	else if(meshParts.size() > 1)
	{
		for(const auto & meshPart : meshParts)
		{
			if(meshPart->getId().empty())
			{
				return nullptr;
			}
		}
	}

	auto mesh = make_shared<Mesh>();

	for(const auto & meshPart : meshParts)
	{
		mesh->addPart(meshPart);
	}

	return mesh;
}