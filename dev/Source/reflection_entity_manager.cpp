#include "reflection_entity_manager.hpp"
#include "logger.hpp"

ReflectionEntityManager::ReflectionEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::REFLECTION, meshLoader, textureLoader, renderBus)
{

}

shared_ptr<ReflectionEntity> ReflectionEntityManager::getEntity(const string& ID)
{
	auto result = _getReflectionEntity(ID);

	if(result == nullptr)
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
	// Create entity
	_createEntity(ID);

	// Temporary values
	auto entity = getEntity(ID);

	// Create cube map
	TextureID cubeMap;
	glGenTextures(1, &cubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	entity->setCubeMap(cubeMap);
}

void ReflectionEntityManager::update()
{
	for(const auto& [keyID, entity] : _getReflectionEntities())
	{
		entity->updateTransformation();
	}
}