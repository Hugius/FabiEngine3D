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
	// Variables
	float surfaceHeight = pos.y;
	pos.y = 0.0f;
	float halfSize = size / 2.0f;
	vector<float> waterVertices;

	// Top-left vertex
	waterVertices.push_back(pos.x - halfSize);
	waterVertices.push_back(pos.y);
	waterVertices.push_back(pos.z + halfSize);
	waterVertices.push_back(0.0f);
	waterVertices.push_back(1.0f);

	// Top-right vertex
	waterVertices.push_back(pos.x + halfSize);
	waterVertices.push_back(pos.y);
	waterVertices.push_back(pos.z + halfSize);
	waterVertices.push_back(1.0f);
	waterVertices.push_back(1.0f);

	// Bottom-right vertex
	waterVertices.push_back(pos.x + halfSize);
	waterVertices.push_back(pos.y);
	waterVertices.push_back(pos.z - halfSize);
	waterVertices.push_back(1.0f);
	waterVertices.push_back(0.0f);

	// Bottom-right vertex
	waterVertices.push_back(pos.x + halfSize);
	waterVertices.push_back(pos.y);
	waterVertices.push_back(pos.z - halfSize);
	waterVertices.push_back(1.0f);
	waterVertices.push_back(0.0f);

	// Bottom-left vertex
	waterVertices.push_back(pos.x - halfSize);
	waterVertices.push_back(pos.y);
	waterVertices.push_back(pos.z - halfSize);
	waterVertices.push_back(0.0f);
	waterVertices.push_back(0.0f);

	// Top-left vertex
	waterVertices.push_back(pos.x - halfSize);
	waterVertices.push_back(pos.y);
	waterVertices.push_back(pos.z + halfSize);
	waterVertices.push_back(0.0f);
	waterVertices.push_back(1.0f);
	
	// Create entity
	_createEntity(EntityType::WATER, ID)->load(ID);

	// Fill entity
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_SURFACE, &waterVertices[0], waterVertices.size()));
	getEntity(ID)->setSurfaceHeight(surfaceHeight);
	getEntity(ID)->setSize(size);

	// Cleanup
	waterVertices.clear();
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