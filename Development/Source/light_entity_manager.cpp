#include "light_entity_manager.hpp"
#include "configuration.hpp"

LightEntityManager::LightEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{

}

LightEntity * LightEntityManager::getEntity(const string & ID)
{
	return dynamic_cast<LightEntity*>(_getBaseEntity(ID, EntityType::LIGHT));
}

const vector<LightEntity*> LightEntityManager::getEntities()
{
	vector<LightEntity*> newVector;

	for (auto& entity : _getBaseEntities())
	{
		newVector.push_back(dynamic_cast<LightEntity*>(entity));
	}

	return newVector;
}

void LightEntityManager::addLightEntity(const string & ID, vec3 position, vec3 color, float strength)
{
	// Create entity
	_createEntity(EntityType::LIGHT, ID)->load(ID);

	// Fill entity
	getEntity(ID)->setPosition(position);
	getEntity(ID)->setColor(color);
	getEntity(ID)->setStrength(strength);
}