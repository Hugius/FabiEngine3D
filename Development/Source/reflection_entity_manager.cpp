#include "reflection_entity_manager.hpp"
#include "logger.hpp"

ReflectionEntityManager::ReflectionEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::REFLECTION, meshLoader, texLoader, renderBus)
{

}

shared_ptr<ReflectionEntity> ReflectionEntityManager::getEntity(const string& ID)
{
	auto result = _getReflectionEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("ReflectionEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<ReflectionEntity>>& ReflectionEntityManager::getEntities()
{
	return _getReflectionEntities();
}

void ReflectionEntityManager::createEntity(const string& ID)
{
	_createEntity(ID);
}