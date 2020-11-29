#include "terrain_entity_manager.hpp"
#include "logger.hpp"

TerrainEntityManager::TerrainEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::TERRAIN, objLoader, texLoader, renderBus)
{

}

shared_ptr<TerrainEntity> TerrainEntityManager::getEntity(const string& ID)
{
	auto result = _getTerrainEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting TERRAIN entity with ID \"" + ID + "\" requested");
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

void TerrainEntityManager::addTerrain(const string& ID)
{
	_createEntity(ID);
}

void TerrainEntityManager::generateModel(const string& ID)
{
	// Data collections
	vector<Vec3> vertices;
	vector<Vec2> uvCoords;
	vector<Vec3> normals;

	// Handy values
	const auto& pixelColors = getEntity(ID)->getPixelColors();
	const float size = getEntity(ID)->getSize();
	const unsigned int uSize = static_cast<unsigned int>(size);
	const float halfSize = size / 2.0f;
	const float maxHeight = getEntity(ID)->getMaxHeight();
	const float uvRepeat = getEntity(ID)->getUvRepeat();

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
			vertices.push_back(Vec3(vertexX, vertexY, vertexZ));
			uvCoords.push_back(Vec2(uvX, uvY));
			normals.push_back(normal);
		}
	}

	// Compose single data collection
	vector<float> finalDataCollection;
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
			finalDataCollection.push_back(vertices[topLeftIndex].x);
			finalDataCollection.push_back(vertices[topLeftIndex].y);
			finalDataCollection.push_back(vertices[topLeftIndex].z);
			finalDataCollection.push_back(uvCoords[topLeftIndex].x);
			finalDataCollection.push_back(uvCoords[topLeftIndex].y);
			finalDataCollection.push_back(normals[topLeftIndex].x);
			finalDataCollection.push_back(normals[topLeftIndex].y);
			finalDataCollection.push_back(normals[topLeftIndex].z);

			// Top-right
			finalDataCollection.push_back(vertices[topRightIndex].x);
			finalDataCollection.push_back(vertices[topRightIndex].y);
			finalDataCollection.push_back(vertices[topRightIndex].z);
			finalDataCollection.push_back(uvCoords[topRightIndex].x);
			finalDataCollection.push_back(uvCoords[topRightIndex].y);
			finalDataCollection.push_back(normals[topRightIndex].x);
			finalDataCollection.push_back(normals[topRightIndex].y);
			finalDataCollection.push_back(normals[topRightIndex].z);

			// Bottom-right
			finalDataCollection.push_back(vertices[bottomRightIndex].x);
			finalDataCollection.push_back(vertices[bottomRightIndex].y);
			finalDataCollection.push_back(vertices[bottomRightIndex].z);
			finalDataCollection.push_back(uvCoords[bottomRightIndex].x);
			finalDataCollection.push_back(uvCoords[bottomRightIndex].y);
			finalDataCollection.push_back(normals[bottomRightIndex].x);
			finalDataCollection.push_back(normals[bottomRightIndex].y);
			finalDataCollection.push_back(normals[bottomRightIndex].z);

			// Bottom-right
			finalDataCollection.push_back(vertices[bottomRightIndex].x);
			finalDataCollection.push_back(vertices[bottomRightIndex].y);
			finalDataCollection.push_back(vertices[bottomRightIndex].z);
			finalDataCollection.push_back(uvCoords[bottomRightIndex].x);
			finalDataCollection.push_back(uvCoords[bottomRightIndex].y);
			finalDataCollection.push_back(normals[bottomRightIndex].x);
			finalDataCollection.push_back(normals[bottomRightIndex].y);
			finalDataCollection.push_back(normals[bottomRightIndex].z);

			// Bottom-left
			finalDataCollection.push_back(vertices[bottomLeftIndex].x);
			finalDataCollection.push_back(vertices[bottomLeftIndex].y);
			finalDataCollection.push_back(vertices[bottomLeftIndex].z);
			finalDataCollection.push_back(uvCoords[bottomLeftIndex].x);
			finalDataCollection.push_back(uvCoords[bottomLeftIndex].y);
			finalDataCollection.push_back(normals[bottomLeftIndex].x);
			finalDataCollection.push_back(normals[bottomLeftIndex].y);
			finalDataCollection.push_back(normals[bottomLeftIndex].z);

			// Top-left
			finalDataCollection.push_back(vertices[topLeftIndex].x);
			finalDataCollection.push_back(vertices[topLeftIndex].y);
			finalDataCollection.push_back(vertices[topLeftIndex].z);
			finalDataCollection.push_back(uvCoords[topLeftIndex].x);
			finalDataCollection.push_back(uvCoords[topLeftIndex].y);
			finalDataCollection.push_back(normals[topLeftIndex].x);
			finalDataCollection.push_back(normals[topLeftIndex].y);
			finalDataCollection.push_back(normals[topLeftIndex].z);
		}
	}

	// Create OpenGL buffer
	getEntity(ID)->clearOglBuffers();
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(BufferType::MODEL, &finalDataCollection[0], finalDataCollection.size()));
}

void TerrainEntityManager::update()
{

}

float TerrainEntityManager::getPixelHeight(const string& ID, float x, float z)
{
	return _getPixelHeight(x, z, getEntity(ID)->getSize(), getEntity(ID)->getMaxHeight(), getEntity(ID)->getPixelColors());
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
	int index = (int(x) * int(size)) + int(z);
	return ((pixelColors[index]) / 255.0f) * maxHeight;
}

bool TerrainEntityManager::isInside(const string& ID, float x, float z)
{
	// Return true if point within terrain bounds
	if (x > 0 || x < getEntity(ID)->getSize() || z > 0 || z < getEntity(ID)->getSize())
	{
		return true;
	}
	else
	{
		return false;
	}
}