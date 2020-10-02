#include "terrain_entity_manager.hpp"
#include "logger.hpp"

TerrainEntityManager::TerrainEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(objLoader, texLoader, renderBus)
{

}

TerrainEntity * TerrainEntityManager::getEntity(const string& ID)
{
	return dynamic_cast<TerrainEntity*>(_getBaseEntity(ID, EntityType::TERRAIN));
}

TerrainEntity * TerrainEntityManager::getSelectedTerrain()
{
	if (_getBaseEntities().empty() || _selectedID == "")
	{
		return nullptr;
	}
	else
	{
		return getEntity(_selectedID);
	}
}

void TerrainEntityManager::selectTerrain(const string& ID)
{
	_selectedID = ID;
}

void TerrainEntityManager::addTerrain(const string& ID)
{
	_createEntity(EntityType::TERRAIN, ID)->load(ID);
}

void TerrainEntityManager::generateModel(const string& ID)
{
	// Data collections
	auto& vertices = getEntity(ID)->getVertices();
	auto& uvCoords = getEntity(ID)->getUvCoords();
	auto& normals = getEntity(ID)->getNormals();
	vertices.clear();
	uvCoords.clear();
	normals.clear();

	// Handy values
	const auto& pixelColors = getEntity(ID)->getPixelColors();
	const float size = getEntity(ID)->getSize();
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
			vec3 normal = vec3(LH - RH, 3.0f, DH - UH);
			normal = glm::normalize(normal);

			// Single vertex
			vertices.push_back(vec3(vertexX, vertexY, vertexZ));
			uvCoords.push_back(vec2(uvX, uvY));
			normals.push_back(normal);
		}
	}
	
	// Compose single data collection
	vector<float> finalDataCollection;
	for (unsigned int x = 0; x < size - 1; x++)
	{
		for (unsigned int z = 0; z < size - 1; z++)
		{
			// Indices for vertices collection
			unsigned int topLeftIndex = (z * size) + x;
			unsigned int topRightIndex = topLeftIndex + 1;
			unsigned int bottomLeftIndex = ((z + 1) * size) + x;
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

			// Bottom-left
			finalDataCollection.push_back(vertices[bottomLeftIndex].x);
			finalDataCollection.push_back(vertices[bottomLeftIndex].y);
			finalDataCollection.push_back(vertices[bottomLeftIndex].z);
			finalDataCollection.push_back(uvCoords[bottomLeftIndex].x);
			finalDataCollection.push_back(uvCoords[bottomLeftIndex].y);
			finalDataCollection.push_back(normals[bottomLeftIndex].x);
			finalDataCollection.push_back(normals[bottomLeftIndex].y);
			finalDataCollection.push_back(normals[bottomLeftIndex].z);

			// Bottom-right
			finalDataCollection.push_back(vertices[bottomRightIndex].x);
			finalDataCollection.push_back(vertices[bottomRightIndex].y);
			finalDataCollection.push_back(vertices[bottomRightIndex].z);
			finalDataCollection.push_back(uvCoords[bottomRightIndex].x);
			finalDataCollection.push_back(uvCoords[bottomRightIndex].y);
			finalDataCollection.push_back(normals[bottomRightIndex].x);
			finalDataCollection.push_back(normals[bottomRightIndex].y);
			finalDataCollection.push_back(normals[bottomRightIndex].z);
		}
	}
	
	// Create OpenGL buffer
	getEntity(ID)->clearOglBuffers();
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(BufferType::MODEL, &finalDataCollection[0], finalDataCollection.size()));
	std::cout << getEntity(ID)->getOglBuffer()->getVertexCount() << std::endl;
}

void TerrainEntityManager::loadNormalMapping(const string& ID)
{
	// Data collections
	auto& vertices = getEntity(ID)->getVertices();
	auto& uvCoords = getEntity(ID)->getUvCoords();
	auto& normals = getEntity(ID)->getNormals();
	vector<vec3> tangents;

	// Calculate tangents
	for (size_t i = 0; i < vertices.size(); i += 3)
	{
		// Vertices of 1 triangle
		vec3 v0 = vertices[i + 0];
		vec3 v1 = vertices[i + 1];
		vec3 v2 = vertices[i + 2];

		// Shortcuts for UVs
		vec2 uv0 = uvCoords[i + 0];
		vec2 uv1 = uvCoords[i + 1];
		vec2 uv2 = uvCoords[i + 2];

		// Vertex delta
		vec3 deltaPos1 = v1 - v0;
		vec3 deltaPos2 = v2 - v0;

		// UV delta
		vec2 deltaUV1 = uv1 - uv0;
		vec2 deltaUV2 = uv2 - uv0;

		// Calculate tangent vector
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

		// Add to current OBJ part
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);
	}

	// Compose single data collection
	vector<float> finalDataCollection;
	for (size_t i = 0; i < vertices.size(); i++)
	{
		finalDataCollection.push_back(vertices[i].x);
		finalDataCollection.push_back(vertices[i].y);
		finalDataCollection.push_back(vertices[i].z);
		finalDataCollection.push_back(uvCoords[i].x);
		finalDataCollection.push_back(uvCoords[i].y);
		finalDataCollection.push_back(normals[i].x);
		finalDataCollection.push_back(normals[i].y);
		finalDataCollection.push_back(normals[i].z);
		finalDataCollection.push_back(tangents[i].x);
		finalDataCollection.push_back(tangents[i].y);
		finalDataCollection.push_back(tangents[i].z);
	}

	getEntity(ID)->clearOglBuffers();
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(BufferType::MODEL_TANGENT, &finalDataCollection[0], finalDataCollection.size()));
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
