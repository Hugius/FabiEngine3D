#include "water_entity_manager.hpp"
#include "shader_bus.hpp"

#include <iostream>

WaterEntityManager::WaterEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{

}

WaterEntity * WaterEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<WaterEntity*>(_getBaseEntity(ID, EntityType::WATER));
}

WaterEntity * WaterEntityManager::getSelectedWater()
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

void WaterEntityManager::selectWater(const string & ID)
{
	_selectedID = ID;
}

void WaterEntityManager::addWaterEntity(const string & ID, vec3 pos, float size)
{
	// Saving the surface height
	float surfaceHeight = pos.y;
	pos.y = 0.0f;

	// Make (0,0) the center
	size /= 2.0f;

	// Variables
	vector<float> waterVertices;

	// Creating flat tiled water surface
	for (float x = -size; x < size; x++)
	{
		for (float z = -size; z < size; z++)
		{
			float firstVertexX = pos.x + x;
			float firstVertexY = pos.y;
			float firstVertexZ = pos.z + z + 1;
			float firstUvX = (x / size);
			float firstUvY = ((z / size) + (1.0f / size));

			float secondVertexX = pos.x + x + 1;
			float secondVertexY = pos.y;
			float secondVertexZ = pos.z + z + 1;
			float secondUvX = ((x / size) + (1.0f / size));
			float secondUvY = ((z / size) + (1.0f / size));

			float thirdVertexX = pos.x + x + 1;
			float thirdVertexY = pos.y;
			float thirdVertexZ = pos.z + z;
			float thirdUvX = ((x / size) + (1.0f / size));
			float thirdUvY = (z / size);

			float fourthVertexX = pos.x + x;
			float fourthVertexY = pos.y;
			float fourthVertexZ = pos.z + z;
			float fourthUvX = (x / size);
			float fourthUvY = (z / size);

			waterVertices.push_back(firstVertexX);
			waterVertices.push_back(firstVertexY);
			waterVertices.push_back(firstVertexZ);
			waterVertices.push_back(firstUvX);
			waterVertices.push_back(firstUvY);

			waterVertices.push_back(secondVertexX);
			waterVertices.push_back(secondVertexY);
			waterVertices.push_back(secondVertexZ);
			waterVertices.push_back(secondUvX);
			waterVertices.push_back(secondUvY);

			waterVertices.push_back(thirdVertexX);
			waterVertices.push_back(thirdVertexY);
			waterVertices.push_back(thirdVertexZ);
			waterVertices.push_back(thirdUvX);
			waterVertices.push_back(thirdUvY);

			waterVertices.push_back(thirdVertexX);
			waterVertices.push_back(thirdVertexY);
			waterVertices.push_back(thirdVertexZ);
			waterVertices.push_back(thirdUvX);
			waterVertices.push_back(thirdUvY);

			waterVertices.push_back(fourthVertexX);
			waterVertices.push_back(fourthVertexY);
			waterVertices.push_back(fourthVertexZ);
			waterVertices.push_back(fourthUvX);
			waterVertices.push_back(fourthUvY);

			waterVertices.push_back(firstVertexX);
			waterVertices.push_back(firstVertexY);
			waterVertices.push_back(firstVertexZ);
			waterVertices.push_back(firstUvX);
			waterVertices.push_back(firstUvY);
		}
	}
	
	// Create entity
	_createEntity(EntityType::WATER, ID)->load(ID);

	// Filly entity
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_SURFACE, &waterVertices[0], waterVertices.size()));
	getEntity(ID)->setSurfaceHeight(surfaceHeight);
	getEntity(ID)->setSize(size * 2.0f);
}

void WaterEntityManager::update()
{
	// Update reflection height
	if (getSelectedWater() != nullptr && _shaderBus.isWaterEffectsEnabled())
	{
		_shaderBus.setSceneReflectionHeight(getSelectedWater()->getSurfaceHeight());
	}

	// Update all water entities
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary water entity object
		auto * water = getEntity(baseEntity->getID());

		if (water->isEnabled() && _shaderBus.isWaterEffectsEnabled())
		{
			water->setRipplePos(water->getRipplePos() + water->getWavingSpeed() / 100.0f);
			water->setRipplePos(fmod(water->getRipplePos(), 1.0f));

			// X waves
			//float timeX = water->getTimeX() + water->getWavingSpeed() / 300.0f;
			//timeX = timeX > 0.235f ? 0.2f : timeX;
			//water->setTimeX(timeX);

			//// Z waves
			//float timeZ = water->getTimeZ() + water->getWavingSpeed() / 300.0f;
			//timeZ = timeX > 0.235f ? 0.2f : timeX;
			//water->setTimeZ(timeZ);
		}
	}
}