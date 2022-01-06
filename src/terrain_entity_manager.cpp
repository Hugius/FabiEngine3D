#include "terrain_entity_manager.hpp"
#include "terrain_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<TerrainEntity> TerrainEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("TerrainEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

shared_ptr<TerrainEntity> TerrainEntityManager::getSelectedTerrain()
{
	if(_entities.empty() || _selectedID.empty())
	{
		return nullptr;
	}
	else
	{
		return getEntity(_selectedID);
	}
}

const unordered_map<string, shared_ptr<TerrainEntity>>& TerrainEntityManager::getEntities()
{
	return _entities;
}

void TerrainEntityManager::createEntity(const string& ID, const string& heightMapPath)
{
	auto entity = make_shared<TerrainEntity>(ID);

	_entities.insert(make_pair(ID, entity));

	auto image = _imageLoader->loadImage(heightMapPath);

	if(image == nullptr)
	{
		deleteEntity(ID);
		return;
	}

	if(image->getWidth() != image->getHeight())
	{
		Logger::throwWarning("Tried to create terrain with ID \"" + ID + "\": height map resolution not the same!");
		deleteEntity(ID);
		return;
	}

	auto size = static_cast<float>(image->getWidth());

	if(size > MAX_SIZE)
	{
		Logger::throwWarning("Tried to create terrain with ID \"" + ID + "\": height map resolution too high!");
		deleteEntity(ID);
		return;
	}

	vector<float> pixels;
	for(unsigned int i = 0; i < (image->getWidth() * image->getHeight()); i++)
	{
		pixels.push_back(static_cast<float>(image->getPixels()[i]) / 255.0f);
	}

	_loadMesh(entity, size, 0.0f, pixels);

	entity->setHeightMapPath(heightMapPath);
	entity->setPixels(pixels);
	entity->setSize(size);
}

void TerrainEntityManager::selectTerrain(const string& ID)
{
	if(isEntityExisting(ID) || ID.empty())
	{
		_selectedID = ID;
	}
	else
	{
		Logger::throwError("TerrainEntityManager::selectTerrain");
	}
}

void TerrainEntityManager::inject(shared_ptr<ImageLoader> imageLoader)
{
	_imageLoader = imageLoader;
}

void TerrainEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("TerrainEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void TerrainEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool TerrainEntityManager::isEntityExisting(const string& ID) const
{
	return (_entities.find(ID) != _entities.end());
}

void TerrainEntityManager::loadMesh(const string& ID)
{
	_loadMesh(getEntity(ID), getEntity(ID)->getSize(), getEntity(ID)->getMaxHeight(), getEntity(ID)->getPixels());
}

void TerrainEntityManager::_loadMesh(shared_ptr<TerrainEntity> entity, float size, float maxHeight, const vector<float>& pixels)
{
	const auto halfSize = (size / 2.0f);
	const auto uSize = static_cast<unsigned int>(size);

	vector<fvec3> tempPositions;
	vector<fvec2> tempUvs;
	vector<fvec3> tempNormals;
	for(float x = -halfSize; x < halfSize; x++)
	{
		for(float z = -halfSize; z < halfSize; z++)
		{
			float positionX = x;
			float positionY = _getPixelHeight(x + halfSize, z + halfSize, size, maxHeight, pixels);
			float positionZ = z;

			float uvX = ((x + halfSize) / size);
			float uvY = ((z + halfSize) / size);

			float LH = _getPixelHeight(x + halfSize - 1, z + halfSize, size, maxHeight, pixels);
			float RH = _getPixelHeight(x + halfSize + 1, z + halfSize, size, maxHeight, pixels);
			float UH = _getPixelHeight(x + halfSize, z + halfSize + 1, size, maxHeight, pixels);
			float DH = _getPixelHeight(x + halfSize, z + halfSize - 1, size, maxHeight, pixels);
			fvec3 normal = fvec3(LH - RH, 3.0f, DH - UH);
			normal = Math::normalize(normal);

			tempPositions.push_back(fvec3(positionX, positionY, positionZ));
			tempUvs.push_back(fvec2(uvX, uvY));
			tempNormals.push_back(normal);
		}
	}

	vector<fvec3> positions;
	vector<fvec2> uvs;
	vector<fvec3> normals;
	for(unsigned int x = 0; x < uSize - 1; x++)
	{
		for(unsigned int z = 0; z < uSize - 1; z++)
		{
			unsigned int topLeftIndex = (z * uSize) + x;
			unsigned int topRightIndex = topLeftIndex + 1;
			unsigned int bottomLeftIndex = ((z + 1) * uSize) + x;
			unsigned int bottomRightIndex = bottomLeftIndex + 1;

			positions.push_back(tempPositions[topLeftIndex]);
			uvs.push_back(tempUvs[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);

			positions.push_back(tempPositions[topRightIndex]);
			uvs.push_back(tempUvs[topRightIndex]);
			normals.push_back(tempNormals[topRightIndex]);

			positions.push_back(tempPositions[bottomRightIndex]);
			uvs.push_back(tempUvs[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			positions.push_back(tempPositions[bottomRightIndex]);
			uvs.push_back(tempUvs[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			positions.push_back(tempPositions[bottomLeftIndex]);
			uvs.push_back(tempUvs[bottomLeftIndex]);
			normals.push_back(tempNormals[bottomLeftIndex]);

			positions.push_back(tempPositions[topLeftIndex]);
			uvs.push_back(tempUvs[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);
		}
	}

	vector<fvec3> tangents;
	for(size_t i = 0; i < positions.size(); i += 3)
	{
		fvec3 v0 = positions[i + 0];
		fvec3 v1 = positions[i + 1];
		fvec3 v2 = positions[i + 2];

		fvec2 uv0 = uvs[i + 0];
		fvec2 uv1 = uvs[i + 1];
		fvec2 uv2 = uvs[i + 2];

		fvec3 deltaPos1 = v1 - v0;
		fvec3 deltaPos2 = v2 - v0;

		fvec2 deltaUv1 = uv1 - uv0;
		fvec2 deltaUv2 = uv2 - uv0;

		float r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
		fvec3 tangent = (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * r;

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);
	}

	vector<float> bufferData;
	for(size_t i = 0; i < positions.size(); i++)
	{
		bufferData.push_back(positions[i].x);
		bufferData.push_back(positions[i].y);
		bufferData.push_back(positions[i].z);

		bufferData.push_back(uvs[i].x);
		bufferData.push_back(uvs[i].y);

		bufferData.push_back(normals[i].x);
		bufferData.push_back(normals[i].y);
		bufferData.push_back(normals[i].z);

		bufferData.push_back(tangents[i].x);
		bufferData.push_back(tangents[i].y);
		bufferData.push_back(tangents[i].z);
	}

	auto bufferDataCount = static_cast<unsigned int>(bufferData.size());

	entity->setMesh(make_shared<VertexBuffer>(VertexBufferType::POS_UV_NOR_TAN, &bufferData[0], bufferDataCount));
}

const float TerrainEntityManager::getPixelHeight(const string& ID, float x, float z)
{
	return _getPixelHeight(x, z, getEntity(ID)->getSize(), getEntity(ID)->getMaxHeight(), getEntity(ID)->getPixels());
}

const bool TerrainEntityManager::isInside(const string& ID, float x, float z)
{
	if(x > 0 && x < getEntity(ID)->getSize() && z > 0 && z < getEntity(ID)->getSize())
	{
		return true;
	}
	else
	{
		return false;
	}
}

float TerrainEntityManager::_getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixels)
{
	if(x == size)
	{
		x--;
	}

	if(z == size)
	{
		z--;
	}

	if(x < 0 || x > size || z < 0 || z > size)
	{
		return 0.0f;
	}

	int index = (static_cast<int>(x) * static_cast<int>(size)) + static_cast<int>(z);
	return (pixels[index] * maxHeight);
}