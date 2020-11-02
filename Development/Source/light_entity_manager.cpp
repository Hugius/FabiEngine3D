#include "light_entity_manager.hpp"
#include "configuration.hpp"

LightEntityManager::LightEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::LIGHT, objLoader, texLoader, renderBus)
{

}

shared_ptr<LightEntity> LightEntityManager::getEntity(const string& ID)
{
	return _getLightEntity(ID);
}

const vector<shared_ptr<LightEntity>> LightEntityManager::getEntities()
{
	return _getLightEntities();
}

void LightEntityManager::addLightEntity(const string& ID, vec3 position, vec3 color, float intensity, float distanceFactor)
{
	// Create entity
	_createEntity(ID);

	// Fill entity
	getEntity(ID)->setPosition(position);
	getEntity(ID)->setColor(color);
	getEntity(ID)->setIntensity(intensity);
	getEntity(ID)->setDistanceFactor(distanceFactor);
}

void LightEntityManager::update()
{

}