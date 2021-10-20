#include "pointlight_entity_manager.hpp"
#include "logger.hpp"

PointlightEntityManager::PointlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::POINTLIGHT, meshLoader, textureLoader, renderBus)
{

}

shared_ptr<PointlightEntity> PointlightEntityManager::getEntity(const string& ID)
{
	auto result = _getPointlightEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("PointlightEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<PointlightEntity>>& PointlightEntityManager::getEntities()
{
	return _getPointlightEntities();
}

void PointlightEntityManager::createEntity(const string& ID)
{
	if (getEntities().size() == MAX_LIGHT_COUNT)
	{
		Logger::throwError("PointlightEntityManager::createEntity");
	}

	_createEntity(ID);
}

void PointlightEntityManager::update()
{
	for (const auto& [keyID, entity] : _getPointlightEntities())
	{
		if (entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}