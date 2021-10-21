#include "spotlight_entity_manager.hpp"
#include "logger.hpp"

SpotlightEntityManager::SpotlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::SPOTLIGHT, meshLoader, textureLoader, renderBus)
{

}

shared_ptr<SpotlightEntity> SpotlightEntityManager::getEntity(const string& ID)
{
	auto result = _getSpotlightEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("SpotlightEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<SpotlightEntity>>& SpotlightEntityManager::getEntities()
{
	return _getSpotlightEntities();
}

void SpotlightEntityManager::createEntity(const string& ID)
{
	if (getEntities().size() == MAX_LIGHT_COUNT)
	{
		Logger::throwError("SpotlightEntityManager::createEntity");
	}

	_createEntity(ID);
}

void SpotlightEntityManager::update()
{
	for (const auto& [keyID, entity] : _getSpotlightEntities())
	{
		// Update transformation
		entity->updateTransformation();

		// Update front vector
		if (entity->isVisible())
		{
			entity->updateFrontVector();
		}
	}
}