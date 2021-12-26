#include "terrain_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

TerrainEntityManager::TerrainEntityManager(TextureLoader& textureLoader)
	:
	_textureLoader(textureLoader)
{

}

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
	_entities.insert(make_pair(ID, make_shared<TerrainEntity>(ID, heightMapPath)));

	auto pixelsPointer = _textureLoader.loadBitmap(heightMapPath);

	if(pixelsPointer == nullptr)
	{
		deleteEntity(ID);
		return;
	}

	auto& pixels = *pixelsPointer;
	auto heightMapSize = static_cast<unsigned int>(sqrt(static_cast<double>(pixels.size())));
	if(heightMapSize > MAX_SIZE)
	{
		Logger::throwWarning("Tried to create terrain with ID \"" + ID + "\": height map resolution too high!");
		deleteEntity(ID);
		return;
	}

	auto entity = getEntity(ID);

	entity->setPixels(pixels);
	entity->setSize(static_cast<float>(heightMapSize));

	loadMesh(ID);
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

const bool TerrainEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}

void TerrainEntityManager::loadMesh(const string& ID)
{
	auto entity = getEntity(ID);
	const auto& pixels = entity->getPixels();
	const float size = entity->getSize();
	const unsigned int uSize = static_cast<unsigned int>(size);
	const float halfSize = size / 2.0f;
	const float maxHeight = entity->getMaxHeight();
	vector<fvec3> tempVertices;
	vector<fvec2> tempUvCoords;
	vector<fvec3> tempNormals;

	for(float x = -halfSize; x < halfSize; x++)
	{
		for(float z = -halfSize; z < halfSize; z++)
		{
			float vertexX = x;
			float vertexY = _getPixelHeight(x + halfSize, z + halfSize, size, maxHeight, pixels);
			float vertexZ = z;

			float uvX = ((x + halfSize) / size);
			float uvY = ((z + halfSize) / size);

			float LH = _getPixelHeight(x + halfSize - 1, z + halfSize, size, maxHeight, pixels);
			float RH = _getPixelHeight(x + halfSize + 1, z + halfSize, size, maxHeight, pixels);
			float UH = _getPixelHeight(x + halfSize, z + halfSize + 1, size, maxHeight, pixels);
			float DH = _getPixelHeight(x + halfSize, z + halfSize - 1, size, maxHeight, pixels);
			fvec3 normal = fvec3(LH - RH, 3.0f, DH - UH);
			normal = Math::normalize(normal);

			tempVertices.push_back(fvec3(vertexX, vertexY, vertexZ));
			tempUvCoords.push_back(fvec2(uvX, uvY));
			tempNormals.push_back(normal);
		}
	}

	vector<fvec3> vertices;
	vector<fvec2> uvCoords;
	vector<fvec3> normals;
	for(unsigned int x = 0; x < uSize - 1; x++)
	{
		for(unsigned int z = 0; z < uSize - 1; z++)
		{
			unsigned int topLeftIndex = (z * uSize) + x;
			unsigned int topRightIndex = topLeftIndex + 1;
			unsigned int bottomLeftIndex = ((z + 1) * uSize) + x;
			unsigned int bottomRightIndex = bottomLeftIndex + 1;

			vertices.push_back(tempVertices[topLeftIndex]);
			uvCoords.push_back(tempUvCoords[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);

			vertices.push_back(tempVertices[topRightIndex]);
			uvCoords.push_back(tempUvCoords[topRightIndex]);
			normals.push_back(tempNormals[topRightIndex]);

			vertices.push_back(tempVertices[bottomRightIndex]);
			uvCoords.push_back(tempUvCoords[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			vertices.push_back(tempVertices[bottomRightIndex]);
			uvCoords.push_back(tempUvCoords[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			vertices.push_back(tempVertices[bottomLeftIndex]);
			uvCoords.push_back(tempUvCoords[bottomLeftIndex]);
			normals.push_back(tempNormals[bottomLeftIndex]);

			vertices.push_back(tempVertices[topLeftIndex]);
			uvCoords.push_back(tempUvCoords[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);
		}
	}

	vector<fvec3> tangents;
	for(size_t i = 0; i < vertices.size(); i += 3)
	{
		fvec3 v0 = vertices[i + 0];
		fvec3 v1 = vertices[i + 1];
		fvec3 v2 = vertices[i + 2];

		fvec2 uv0 = uvCoords[i + 0];
		fvec2 uv1 = uvCoords[i + 1];
		fvec2 uv2 = uvCoords[i + 2];

		fvec3 deltaPos1 = v1 - v0;
		fvec3 deltaPos2 = v2 - v0;

		fvec2 deltaUV1 = uv1 - uv0;
		fvec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		fvec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);
	}

	vector<float> bufferData;
	for(size_t i = 0; i < vertices.size(); i++)
	{
		bufferData.push_back(vertices[i].x);
		bufferData.push_back(vertices[i].y);
		bufferData.push_back(vertices[i].z);

		bufferData.push_back(uvCoords[i].x);
		bufferData.push_back(uvCoords[i].y);

		bufferData.push_back(normals[i].x);
		bufferData.push_back(normals[i].y);
		bufferData.push_back(normals[i].z);

		bufferData.push_back(tangents[i].x);
		bufferData.push_back(tangents[i].y);
		bufferData.push_back(tangents[i].z);
	}

	entity->setRenderBuffer(make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV_NORMAL_TANGENT, &bufferData[0], static_cast<unsigned int>(bufferData.size())));

	entity->setVertices(vertices);
	entity->setUvCoords(uvCoords);
	entity->setNormals(normals);
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
	return ((pixels[index]) / 255.0f) * maxHeight;
}