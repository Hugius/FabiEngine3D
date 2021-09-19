#include "light_entity_manager.hpp"
#include "configuration.hpp"
#include "logger.hpp"

LightEntityManager::LightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::LIGHT, meshLoader, textureLoader, renderBus)
{

}

shared_ptr<LightEntity> LightEntityManager::getEntity(const string& ID)
{
	auto result = _getLightEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("LightEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<LightEntity>>& LightEntityManager::getEntities()
{
	return _getLightEntities();
}

void LightEntityManager::createEntity(const string& ID)
{
	if (getEntities().size() == MAX_LIGHT_COUNT)
	{
		Logger::throwError("LightEntityManager::createEntity");
	}

	_createEntity(ID);
}

void LightEntityManager::update()
{
	for (const auto& [keyID, entity] : _getLightEntities())
	{
		if (entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}