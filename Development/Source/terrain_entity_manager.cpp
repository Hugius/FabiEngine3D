#include "terrain_entity_manager.hpp"
#include "logger.hpp"

TerrainEntityManager::TerrainEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{

}

TerrainEntity * TerrainEntityManager::getEntity(const string & ID)
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

void TerrainEntityManager::selectTerrain(const string & ID)
{
	_selectedID = ID;
}

void TerrainEntityManager::addTerrain(const string& ID)
{
	_createEntity(EntityType::TERRAIN, ID)->load(ID);
}

void TerrainEntityManager::generateModel(const string& ID)
{
	// Variables
	vector<float> terrainVertices;
	auto& pixelColors = getEntity(ID)->getPixelColors();
	float size = getEntity(ID)->getSize();
	float halfSize = size / 2.0f;
	float maxHeight = getEntity(ID)->getMaxHeight();
	float uvRepeat = getEntity(ID)->getUvRepeat();
	
	// Generate terrain vertices
	for (float x = -halfSize; x < halfSize; x++)
	{
		for (float z = -halfSize; z < halfSize; z++)
		{
			float firstVertexX = x;
			float firstVertexY = _getPixelHeight(x + halfSize, z + halfSize + 1, size, maxHeight, pixelColors);
			float firstVertexZ = z + 1;
			float firstUvX = ((x + halfSize) / size) * uvRepeat;
			float firstUvY = (((z + halfSize) / size) + (1.0f / size)) * uvRepeat;

			float secondVertexX = x + 1;
			float secondVertexY = _getPixelHeight(x + halfSize + 1, z + halfSize + 1, size, maxHeight, pixelColors);
			float secondVertexZ = z + 1;
			float secondUvX = (((x + halfSize) / size) + (1.0f / size)) * uvRepeat;
			float secondUvY = (((z + halfSize) / size) + (1.0f / size)) * uvRepeat;

			float thirdVertexX = x + 1;
			float thirdVertexY = _getPixelHeight(x + halfSize + 1, z + halfSize, size, maxHeight, pixelColors);
			float thirdVertexZ = z;
			float thirdUvX = (((x + halfSize) / size) + (1.0f / size)) * uvRepeat;
			float thirdUvY = ((z + halfSize) / size) * uvRepeat;

			float fourthVertexX = x;
			float fourthVertexY = _getPixelHeight(x + halfSize, z + halfSize, size, maxHeight, pixelColors);
			float fourthVertexZ = z;
			float fourthUvX = ((x + halfSize) / size) * uvRepeat;
			float fourthUvY = ((z + halfSize) / size) * uvRepeat;

			//// First triangle normals
			//vec3 tempOne = vec3(secondVertexX, secondVertexY, secondVertexZ) - vec3(firstVertexX, firstVertexY, firstVertexZ);
			//vec3 tempTwo = vec3(thirdVertexX, thirdVertexY, thirdVertexZ) - vec3(firstVertexX, firstVertexY, firstVertexZ);
			//vec3 normalOne = glm::cross(tempOne, tempTwo);
			//normalOne = glm::normalize(normalOne);

			//// Second triangle normal
			//vec3 tempThree = vec3(fourthVertexX, fourthVertexY, fourthVertexZ) - vec3(thirdVertexX, thirdVertexY, thirdVertexZ);
			//vec3 tempFour = vec3(firstVertexX, firstVertexY, firstVertexZ) - vec3(thirdVertexX, thirdVertexY, thirdVertexZ);
			//vec3 normalTwo = glm::cross(tempThree, tempFour);
			//normalTwo = glm::normalize(normalTwo);

			// Calculate normals
			float LH = _getPixelHeight(x + halfSize - 1, z + halfSize, size, maxHeight, pixelColors);
			float RH = _getPixelHeight(x + halfSize + 1, z + halfSize, size, maxHeight, pixelColors);
			float UH = _getPixelHeight(x + halfSize, z + halfSize + 1, size, maxHeight, pixelColors);
			float DH = _getPixelHeight(x + halfSize, z + halfSize - 1, size, maxHeight, pixelColors);
			vec3 normal = vec3(LH - RH, 2.0f, DH - UH);
			normal = glm::normalize(normal);

			terrainVertices.push_back(firstVertexX);
			terrainVertices.push_back(firstVertexY);
			terrainVertices.push_back(firstVertexZ);
			terrainVertices.push_back(firstUvX);
			terrainVertices.push_back(firstUvY);
			terrainVertices.push_back(normal.x);
			terrainVertices.push_back(normal.y);
			terrainVertices.push_back(normal.z);

			terrainVertices.push_back(secondVertexX);
			terrainVertices.push_back(secondVertexY);
			terrainVertices.push_back(secondVertexZ);
			terrainVertices.push_back(secondUvX);
			terrainVertices.push_back(secondUvY);
			terrainVertices.push_back(normal.x);
			terrainVertices.push_back(normal.y);
			terrainVertices.push_back(normal.z);

			terrainVertices.push_back(thirdVertexX);
			terrainVertices.push_back(thirdVertexY);
			terrainVertices.push_back(thirdVertexZ);
			terrainVertices.push_back(thirdUvX);
			terrainVertices.push_back(thirdUvY);
			terrainVertices.push_back(normal.x);
			terrainVertices.push_back(normal.y);
			terrainVertices.push_back(normal.z);

			terrainVertices.push_back(thirdVertexX);
			terrainVertices.push_back(thirdVertexY);
			terrainVertices.push_back(thirdVertexZ);
			terrainVertices.push_back(thirdUvX);
			terrainVertices.push_back(thirdUvY);
			terrainVertices.push_back(normal.x);
			terrainVertices.push_back(normal.y);
			terrainVertices.push_back(normal.z);

			terrainVertices.push_back(fourthVertexX);
			terrainVertices.push_back(fourthVertexY);
			terrainVertices.push_back(fourthVertexZ);
			terrainVertices.push_back(fourthUvX);
			terrainVertices.push_back(fourthUvY);
			terrainVertices.push_back(normal.x);
			terrainVertices.push_back(normal.y);
			terrainVertices.push_back(normal.z);

			terrainVertices.push_back(firstVertexX);
			terrainVertices.push_back(firstVertexY);
			terrainVertices.push_back(firstVertexZ);
			terrainVertices.push_back(firstUvX);
			terrainVertices.push_back(firstUvY);
			terrainVertices.push_back(normal.x);
			terrainVertices.push_back(normal.y);
			terrainVertices.push_back(normal.z);
		}
	}
	
	getEntity(ID)->clearOglBuffers();
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_3D, &terrainVertices[0], terrainVertices.size()));
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
