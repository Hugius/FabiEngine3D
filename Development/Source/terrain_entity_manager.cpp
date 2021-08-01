#include "terrain_entity_manager.hpp"
#include "logger.hpp"

TerrainEntityManager::TerrainEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::TERRAIN, meshLoader, texLoader, renderBus)
{

}

shared_ptr<TerrainEntity> TerrainEntityManager::getEntity(const string& ID)
{
	auto result = _getTerrainEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Non-existing terrain entity with ID \"" + ID + "\" requested!");
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
	if (isExisting(ID) || ID.empty())
	{
		_selectedID = ID;
	}
	else
	{
		Logger::throwError("Tried to select terrain entity with ID \"" + ID + "\": not existing!");
	}
}

void TerrainEntityManager::createEntity(const string& ID, const string& heightMapPath)
{
	_createEntity(ID);
	loadMesh(ID, heightMapPath);
}

void TerrainEntityManager::loadMesh(const string& ID, const string& heightMapPath)
{
	// Temporary values
	auto entity = getEntity(ID);

	// Load height map
	auto pixelValues = _textureLoader.getBitmapPixels(heightMapPath);
	entity->setHeightMapPath(heightMapPath);
	entity->setPixelValues({});
	entity->setSize(0.0f);
	entity->setRenderBuffer(nullptr);

	// Check if height map loading failed
	if (pixelValues == nullptr)
	{
		return;
	}

	// Check if height map resolution too high
	auto heightMapSize = static_cast<unsigned int>(sqrt(static_cast<double>(pixelValues->size())));
	if (heightMapSize > MAX_HEIGHT_MAP_RESOLUTION)
	{
		Logger::throwWarning("Tried to load mesh of terrain with ID \"" + ID + "\": height map resolution too high!");
		return;
	}

	// Set properties
	entity->setPixelValues(*pixelValues);
	entity->setSize(static_cast<float>(heightMapSize));

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

	for (float x = -halfSize; x < halfSize; x++) // X direction
	{
		for (float z = -halfSize; z < halfSize; z++) // Z direction
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

			// Add data
			tempVertices.push_back(Vec3(vertexX, vertexY, vertexZ));
			tempUvCoords.push_back(Vec2(uvX, uvY));
			tempNormals.push_back(normal);
		}
	}
	
	// Compose vertices, UV coordinates, normals
	vector<Vec3> vertices;
	vector<Vec2> uvCoords;
	vector<Vec3> normals;
	for (unsigned int x = 0; x < uSize - 1; x++)
	{
		for (unsigned int z = 0; z < uSize - 1; z++)
		{
			// Indices
			unsigned int topLeftIndex = (z * uSize) + x;
			unsigned int topRightIndex = topLeftIndex + 1;
			unsigned int bottomLeftIndex = ((z + 1) * uSize) + x;
			unsigned int bottomRightIndex = bottomLeftIndex + 1;

			// Top-left
			vertices.push_back(tempVertices[topLeftIndex]);
			uvCoords.push_back(tempUvCoords[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);

			// Top-right
			vertices.push_back(tempVertices[topRightIndex]);
			uvCoords.push_back(tempUvCoords[topRightIndex]);
			normals.push_back(tempNormals[topRightIndex]);

			// Bottom-right
			vertices.push_back(tempVertices[bottomRightIndex]);
			uvCoords.push_back(tempUvCoords[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			// Bottom-right
			vertices.push_back(tempVertices[bottomRightIndex]);
			uvCoords.push_back(tempUvCoords[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			// Bottom-left
			vertices.push_back(tempVertices[bottomLeftIndex]);
			uvCoords.push_back(tempUvCoords[bottomLeftIndex]);
			normals.push_back(tempNormals[bottomLeftIndex]);

			// Top-left
			vertices.push_back(tempVertices[topLeftIndex]);
			uvCoords.push_back(tempUvCoords[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);
		}
	}
	
	// Calculate tangents
	vector<Vec3> tangents;
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
	entity->setVertices(vertices);
	entity->setUvCoords(uvCoords);
	entity->setNormals(normals);
	entity->setRenderBuffer(std::make_shared<RenderBuffer>(BufferType::VERTEX_UV_NORMAL_TANGENT, &finalDataCollection[0], static_cast<unsigned int>(finalDataCollection.size())));
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