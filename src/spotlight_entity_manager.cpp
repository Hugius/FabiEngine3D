#include "spotlight_entity_manager.hpp"
#include "logger.hpp"

SpotlightEntityManager::SpotlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::SPOTLIGHT, meshLoader, textureLoader, renderBus)
{

}

shared_ptr<SpotlightEntity> SpotlightEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("SpotlightEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<SpotlightEntity>>& SpotlightEntityManager::getEntities()
{
	return _entities;
}

void SpotlightEntityManager::createEntity(const string& ID)
{
	if(getEntities().size() == MAX_LIGHT_COUNT)
	{
		Logger::throwError("SpotlightEntityManager::createEntity");
	}

	_createEntity(ID);
}

void SpotlightEntityManager::update()
{
	for(const auto& [keyID, entity] : _entities)
	{
		// Update transformation
		entity->updateTransformation();

		// Update front vector
		if(entity->isVisible())
		{
			entity->updateFrontVector();
		}
	}
}