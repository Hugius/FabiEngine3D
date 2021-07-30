#include "terrain_entity_manager.hpp"
#include "logger.hpp"

TerrainEntityManager::TerrainEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::TERRAIN, meshLoader, texLoader, renderBus)
{

}

shared_ptr<TerrainEntity> TerrainEntityManager::getEntity(const string& ID)
{
	auto result = _getTerrainEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Non-existing terrain entity with ID \"" + ID + "\" requested");
	}

	return result;
}

shared_ptr<TerrainEntity> TerrainEntityManager::getSelectedTerrain()
{
	if (_getTerrainEntities().empty() || _selectedID == "")
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
	return _getTerrainEntities();
}

void TerrainEntityManager::selectTerrain(const string& ID)
{
	_selectedID = ID;
}

void TerrainEntityManager::createEntity(const string& ID)
{
	_createEntity(ID);
}

void TerrainEntityManager::loadMesh(const string& ID)
{
	auto entity = getEntity(ID);

	// Data collections
	vector<Vec3> tempVertices;
	vector<Vec2> tempUvCoords;
	vector<Vec3> tempNormals;

	// Handy values
	const auto& pixelColors = entity->getPixelValues();
	const float size = entity->getSize();
	const unsigned int uSize = static_cast<unsigned int>(size);
	const float halfSize = size / 2.0f;
	const float maxHeight = entity->getMaxHeight();
	const float uvRepeat = entity->getUvRepeat();

	// Generate terrain vertices
	for (float x = -halfSize; x < halfSize; x++)
	{
		for (float z = -halfSize; z < halfSize; z++)
		{
			// Calculate vertex
			float vertexX = x;
			float vertexY = _getPixelHeight(x + halfSize, z + halfSize, size, maxHeight, pixelColors);
			float vertexZ = z;

			// Calculate UV coordinate
			float uvX = ((x + halfSize) / size) * uvRepeat;
			float uvY = ((z + halfSize) / size) * uvRepeat;

			// Calculate normal vector
			float LH = _getPixelHeight(x + halfSize - 1, z + halfSize, size, maxHeight, pixelColors);
			float RH = _getPixelHeight(x + halfSize + 1, z + halfSize, size, maxHeight, pixelColors);
			float UH = _getPixelHeight(x + halfSize, z + halfSize + 1, size, maxHeight, pixelColors);
			float DH = _getPixelHeight(x + halfSize, z + halfSize - 1, size, maxHeight, pixelColors);
			Vec3 normal = Vec3(LH - RH, 3.0f, DH - UH);
			normal.normalize();

			// Single vertex
			tempVertices.push_back(Vec3(vertexX, vertexY, vertexZ));
			tempUvCoords.push_back(Vec2(uvX, uvY));
			tempNormals.push_back(normal);
		}
	}

	// Compose single data collection
	vector<float> finalDataCollection;
	auto& vertices = getEntity(ID)->getVertices();
	auto& uvCoords = getEntity(ID)->getUvCoords();
	auto& normals = getEntity(ID)->getNormals();
	vertices.clear();
	uvCoords.clear();
	normals.clear();
	for (unsigned int x = 0; x < uSize - 1; x++)
	{
		for (unsigned int z = 0; z < uSize - 1; z++)
		{
			// Indices for vertices collection
			unsigned int topLeftIndex = (z * uSize) + x;
			unsigned int topRightIndex = topLeftIndex + 1;
			unsigned int bottomLeftIndex = ((z + 1) * uSize) + x;
			unsigned int bottomRightIndex = bottomLeftIndex + 1;

			// Top-left
			finalDataCollection.push_back(tempVertices[topLeftIndex].x);
			finalDataCollection.push_back(tempVertices[topLeftIndex].y);
			finalDataCollection.push_back(tempVertices[topLeftIndex].z);
			finalDataCollection.push_back(tempUvCoords[topLeftIndex].x);
			finalDataCollection.push_back(tempUvCoords[topLeftIndex].y);
			finalDataCollection.push_back(tempNormals[topLeftIndex].x);
			finalDataCollection.push_back(tempNormals[topLeftIndex].y);
			finalDataCollection.push_back(tempNormals[topLeftIndex].z);
			vertices.push_back(tempVertices[topLeftIndex]);
			uvCoords.push_back(tempUvCoords[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);

			// Top-right
			finalDataCollection.push_back(tempVertices[topRightIndex].x);
			finalDataCollection.push_back(tempVertices[topRightIndex].y);
			finalDataCollection.push_back(tempVertices[topRightIndex].z);
			finalDataCollection.push_back(tempUvCoords[topRightIndex].x);
			finalDataCollection.push_back(tempUvCoords[topRightIndex].y);
			finalDataCollection.push_back(tempNormals[topRightIndex].x);
			finalDataCollection.push_back(tempNormals[topRightIndex].y);
			finalDataCollection.push_back(tempNormals[topRightIndex].z);
			vertices.push_back(tempVertices[topRightIndex]);
			uvCoords.push_back(tempUvCoords[topRightIndex]);
			normals.push_back(tempNormals[topRightIndex]);

			// Bottom-right
			finalDataCollection.push_back(tempVertices[bottomRightIndex].x);
			finalDataCollection.push_back(tempVertices[bottomRightIndex].y);
			finalDataCollection.push_back(tempVertices[bottomRightIndex].z);
			finalDataCollection.push_back(tempUvCoords[bottomRightIndex].x);
			finalDataCollection.push_back(tempUvCoords[bottomRightIndex].y);
			finalDataCollection.push_back(tempNormals[bottomRightIndex].x);
			finalDataCollection.push_back(tempNormals[bottomRightIndex].y);
			finalDataCollection.push_back(tempNormals[bottomRightIndex].z);
			vertices.push_back(tempVertices[bottomRightIndex]);
			uvCoords.push_back(tempUvCoords[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			// Bottom-right
			finalDataCollection.push_back(tempVertices[bottomRightIndex].x);
			finalDataCollection.push_back(tempVertices[bottomRightIndex].y);
			finalDataCollection.push_back(tempVertices[bottomRightIndex].z);
			finalDataCollection.push_back(tempUvCoords[bottomRightIndex].x);
			finalDataCollection.push_back(tempUvCoords[bottomRightIndex].y);
			finalDataCollection.push_back(tempNormals[bottomRightIndex].x);
			finalDataCollection.push_back(tempNormals[bottomRightIndex].y);
			finalDataCollection.push_back(tempNormals[bottomRightIndex].z);
			vertices.push_back(tempVertices[bottomRightIndex]);
			uvCoords.push_back(tempUvCoords[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			// Bottom-left
			finalDataCollection.push_back(tempVertices[bottomLeftIndex].x);
			finalDataCollection.push_back(tempVertices[bottomLeftIndex].y);
			finalDataCollection.push_back(tempVertices[bottomLeftIndex].z);
			finalDataCollection.push_back(tempUvCoords[bottomLeftIndex].x);
			finalDataCollection.push_back(tempUvCoords[bottomLeftIndex].y);
			finalDataCollection.push_back(tempNormals[bottomLeftIndex].x);
			finalDataCollection.push_back(tempNormals[bottomLeftIndex].y);
			finalDataCollection.push_back(tempNormals[bottomLeftIndex].z);
			vertices.push_back(tempVertices[bottomLeftIndex]);
			uvCoords.push_back(tempUvCoords[bottomLeftIndex]);
			normals.push_back(tempNormals[bottomLeftIndex]);

			// Top-left
			finalDataCollection.push_back(tempVertices[topLeftIndex].x);
			finalDataCollection.push_back(tempVertices[topLeftIndex].y);
			finalDataCollection.push_back(tempVertices[topLeftIndex].z);
			finalDataCollection.push_back(tempUvCoords[topLeftIndex].x);
			finalDataCollection.push_back(tempUvCoords[topLeftIndex].y);
			finalDataCollection.push_back(tempNormals[topLeftIndex].x);
			finalDataCollection.push_back(tempNormals[topLeftIndex].y);
			finalDataCollection.push_back(tempNormals[topLeftIndex].z);
			vertices.push_back(tempVertices[topLeftIndex]);
			uvCoords.push_back(tempUvCoords[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);
		}
	}

	// Create render buffer
	entity->clearRenderBuffers();
	entity->addRenderBuffer(new RenderBuffer(BufferType::MODEL, &finalDataCollection[0], static_cast<unsigned int>(finalDataCollection.size())));
}

float TerrainEntityManager::getPixelHeight(const string& ID, float x, float z)
{
	return _getPixelHeight(x, z, getEntity(ID)->getSize(), getEntity(ID)->getMaxHeight(), getEntity(ID)->getPixelValues());
}

bool TerrainEntityManager::isInside(const string& ID, float x, float z)
{
	// Return true if point is within terrain bounds
	if (x > 0 && x < getEntity(ID)->getSize() && z > 0 && z < getEntity(ID)->getSize())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TerrainEntityManager::update()
{
	for (const auto& [keyID, entity] : _getTerrainEntities())
	{
		// Update normal mapping
		if (entity->hasNormalMap() || entity->hasNormalMapR() || entity->hasNormalMapG() || entity->hasNormalMapB())
		{
			_loadNormalMapping(entity->getID());
		}
		else
		{
			_unloadNormalMapping(entity->getID());
		}
	}
}

void TerrainEntityManager::_loadNormalMapping(const string& ID)
{
	// Temporary values
	auto entity = getEntity(ID);
	const unsigned int uSize = static_cast<unsigned int>(entity->getSize());

	// Check if entity has a buffer
	if (!entity->getRenderBuffers().empty())
	{
		// Check if renderbuffer not already reloaded
		if (entity->getRenderBuffer()->getBufferType() != BufferType::MODEL_TANGENT)
		{
			// Data collections
			auto vertices = entity->getVertices();
			auto uvCoords = entity->getUvCoords();
			auto normals = entity->getNormals();
			vector<Vec3> tangents;

			// Calculate tangents
			for (size_t i = 0; i < vertices.size(); i += 3)
			{
				// Vertices of 1 triangle
				Vec3 v0 = vertices[i + 0];
				Vec3 v1 = vertices[i + 1];
				Vec3 v2 = vertices[i + 2];

				// Shortcuts for UVs
				Vec2 uv0 = uvCoords[i + 0];
				Vec2 uv1 = uvCoords[i + 1];
				Vec2 uv2 = uvCoords[i + 2];

				// Vertex delta
				Vec3 deltaPos1 = v1 - v0;
				Vec3 deltaPos2 = v2 - v0;

				// UV delta
				Vec2 deltaUV1 = uv1 - uv0;
				Vec2 deltaUV2 = uv2 - uv0;

				// Calculate tangent vector
				float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				Vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

				// Add to list
				tangents.push_back(tangent);
				tangents.push_back(tangent);
				tangents.push_back(tangent);
			}

			// Compose final data collection
			vector<float> finalDataCollection;
			for (size_t i = 0; i < vertices.size(); i++)
			{
				// Vertex coordinate
				finalDataCollection.push_back(vertices[i].x);
				finalDataCollection.push_back(vertices[i].y);
				finalDataCollection.push_back(vertices[i].z);

				// UV coordinate
				finalDataCollection.push_back(uvCoords[i].x);
				finalDataCollection.push_back(uvCoords[i].y);

				// Normal vector
				finalDataCollection.push_back(normals[i].x);
				finalDataCollection.push_back(normals[i].y);
				finalDataCollection.push_back(normals[i].z);

				// Tangent vector
				finalDataCollection.push_back(tangents[i].x);
				finalDataCollection.push_back(tangents[i].y);
				finalDataCollection.push_back(tangents[i].z);
			}

			// Create render buffer
			entity->clearRenderBuffers();
			entity->addRenderBuffer(new RenderBuffer(BufferType::MODEL_TANGENT, &finalDataCollection[0], static_cast<unsigned int>(finalDataCollection.size())));
		}
	}
}

void TerrainEntityManager::_unloadNormalMapping(const string& ID)
{
	// Temporary values
	auto entity = getEntity(ID);
	const unsigned int uSize = static_cast<unsigned int>(entity->getSize());

	// Check if entity has a buffer
	if (!entity->getRenderBuffers().empty())
	{
		// Check if renderbuffer not already reloaded
		if (entity->getRenderBuffer()->getBufferType() != BufferType::MODEL)
		{
			// Data collections
			auto vertices = entity->getVertices();
			auto uvCoords = entity->getUvCoords();
			auto normals = entity->getNormals();

			// Compose final data collection
			vector<float> finalDataCollection;
			for (size_t i = 0; i < vertices.size(); i++)
			{
				// Vertex coordinate
				finalDataCollection.push_back(vertices[i].x);
				finalDataCollection.push_back(vertices[i].y);
				finalDataCollection.push_back(vertices[i].z);

				// UV coordinate
				finalDataCollection.push_back(uvCoords[i].x);
				finalDataCollection.push_back(uvCoords[i].y);

				// Normal vector
				finalDataCollection.push_back(normals[i].x);
				finalDataCollection.push_back(normals[i].y);
				finalDataCollection.push_back(normals[i].z);
			}

			// Create render buffer
			entity->clearRenderBuffers();
			entity->addRenderBuffer(new RenderBuffer(BufferType::MODEL, &finalDataCollection[0], static_cast<unsigned int>(finalDataCollection.size())));
		}
	}
}

float TerrainEntityManager::_getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixelColors)
{
	// If reached end of terrain X
	if (x == size)
	{
		x--;
	}

	// If reached end of terrain Z
	if(z == size)
	{
		z--;
	}

	// Checking if coordinate inside bounds
	if (x < 0 || x > size || z < 0 || z > size)
	{
		return 0.0f;
	}
	
	// Returning the corresponding height
	int index = (static_cast<int>(x) * static_cast<int>(size)) + static_cast<int>(z);
	return ((pixelColors[index]) / 255.0f) * maxHeight;
}