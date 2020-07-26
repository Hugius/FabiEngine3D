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

void WaterEntityManager::addWaterEntity(const string & ID, float size)
{
	// Variables
	float halfSize = size / 2.0f;
	vector<float> waterVertices;
	waterVertices.reserve(size_t(size) * size_t(size) * 30);

	// Try to fill the vector
	try
	{
		// Creating flat tiled water surface
		for (float x = -size; x < size; x++)
		{
			for (float z = -size; z < size; z++)
			{
				float firstVertexX = x;
				float firstVertexY = 0.0f;
				float firstVertexZ = z + 1;
				float firstUvX = (x / size);
				float firstUvY = ((z / size) + (1.0f / size));

				float secondVertexX = x + 1;
				float secondVertexY = 0.0f;
				float secondVertexZ = z + 1;
				float secondUvX = ((x / size) + (1.0f / size));
				float secondUvY = ((z / size) + (1.0f / size));

				float thirdVertexX = x + 1;
				float thirdVertexY = 0.0f;
				float thirdVertexZ = z;
				float thirdUvX = ((x / size) + (1.0f / size));
				float thirdUvY = (z / size);

				float fourthVertexX = x;
				float fourthVertexY = 0.0f;
				float fourthVertexZ = z;
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
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what();
	}
	
	// Create entity
	_createEntity(EntityType::WATER, ID)->load(ID);

	// Fill entity
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_SURFACE, &waterVertices[0], waterVertices.size()));
	getEntity(ID)->setSize(size);

	// Cleanup
	waterVertices.clear();
}

void WaterEntityManager::update()
{
	// Update reflection height
	if (getSelectedWater() != nullptr && _shaderBus.isWaterEffectsEnabled())
	{
		_shaderBus.setSceneReflectionHeight(getSelectedWater()->getPosition().y);
	}

	// Update all water entities
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary water entity object
		auto * water = getEntity(baseEntity->getID());

		// Update water animations (rippling & waving)
		if (water->isVisible() && _shaderBus.isWaterEffectsEnabled())
		{
			water->setRippleOffset(water->getRippleOffset() + water->getSpeed());
			water->setRippleOffset(fmod(water->getRippleOffset(), 1.0f));
			water->setWaveOffset(water->getWaveOffset() + water->getSpeed());
		}
	}
}