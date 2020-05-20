#include "terrain_entity_manager.hpp"
#include "Logger.hpp"

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

void TerrainEntityManager::addTerrainEntity
(
	const string& ID, const string& heightmapPath, const string& textureName,
	vec3 pos, float size, float maxHeight, float uvRepeat
)
{
	// Variables
	vector<float> terrainVertices;
	auto& pixelColors = _texLoader.getHeightMap(heightmapPath);

	// Size correction if needed
	if ((size * size) > pixelColors.size())
	{
		size = float(sqrt(pixelColors.size()));
	}

	// Define half size
	float halfSize = size / 2.0f;

	// Generate terrain vertices
	for (float x = -halfSize; x < halfSize; x++)
	{
		for (float z = -halfSize; z < halfSize; z++)
		{
			float firstVertexX = pos.x + x;
			float firstVertexY = pos.y + _getPixelHeight(x + halfSize, z + halfSize + 1, size, maxHeight, pixelColors);
			float firstVertexZ = pos.z + z + 1;
			float firstUvX = (x / size) * uvRepeat;
			float firstUvY = ((z / size) + (1.0f / size)) * uvRepeat;

			float secondVertexX = pos.x + x + 1;
			float secondVertexY = pos.y + _getPixelHeight(x + halfSize + 1, z + halfSize + 1, size, maxHeight, pixelColors);
			float secondVertexZ = pos.z + z + 1;
			float secondUvX = ((x / size) + (1.0f / size)) * uvRepeat;
			float secondUvY = ((z / size) + (1.0f / size)) * uvRepeat;

			float thirdVertexX = pos.x + x + 1;
			float thirdVertexY = pos.y + _getPixelHeight(x + halfSize + 1, z + halfSize, size, maxHeight, pixelColors);
			float thirdVertexZ = pos.z + z;
			float thirdUvX = ((x / size) + (1.0f / size)) * uvRepeat;
			float thirdUvY = (z / size) * uvRepeat;

			float fourthVertexX = pos.x + x;
			float fourthVertexY = pos.y + _getPixelHeight(x + halfSize, z + halfSize, size, maxHeight, pixelColors);
			float fourthVertexZ = pos.z + z;
			float fourthUvX = (x / size) * uvRepeat;
			float fourthUvY = (z / size) * uvRepeat;

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

	// Create entity
	_createEntity(EntityType::TERRAIN, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_3D, &terrainVertices[0], terrainVertices.size()));
	getEntity(ID)->setDiffuseMap(_texLoader.getTexture(textureName, true, true));
	getEntity(ID)->setPixelColors(pixelColors);
	getEntity(ID)->setHeight(maxHeight);
	getEntity(ID)->setBlendRepeat(uvRepeat);
	getEntity(ID)->setSize(size);
}

void TerrainEntityManager::addBlendingToTerrain
(
	const string& ID, const string& blendMap, const string& blendMapR,
	const string& blendMapG, const string& blendMapB,
	float blendRepeatR, float blendRepeatG, float blendRepeatB
)
{
	getEntity(ID)->setBlendMapped(true);
	getEntity(ID)->setBlendMap(_texLoader.getTexture(blendMap,  true, true));
	getEntity(ID)->setBlendMapR(_texLoader.getTexture(blendMapR, true, true));
	getEntity(ID)->setBlendMapG(_texLoader.getTexture(blendMapG, true, true));
	getEntity(ID)->setBlendMapB(_texLoader.getTexture(blendMapB, true, true));
	getEntity(ID)->setBlendRepeatR(blendRepeatR);
	getEntity(ID)->setBlendRepeatG(blendRepeatG);
	getEntity(ID)->setBlendRepeatB(blendRepeatB);
}

float TerrainEntityManager::getPixelHeight(float x, float z)
{
	auto entity = getSelectedTerrain();
	return _getPixelHeight(x, z, entity->getSize(), entity->getHeight(), entity->getPixelColors());
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

bool TerrainEntityManager::isInside(float x, float z)
{
	// Return true if point within terrain bounds
	if (x > 0 || x < getSelectedTerrain()->getSize() || z > 0 || z < getSelectedTerrain()->getSize())
	{
		return true;
	}
	else
	{
		return false;
	}
}
