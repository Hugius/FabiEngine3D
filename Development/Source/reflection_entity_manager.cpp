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
	// Create entity
	_createEntity(ID);

	// Temporary values
	auto entity = getEntity(ID);

	// Create environment map
	TextureID environmentMap;
	glGenTextures(1, &environmentMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, environmentMap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	entity->setEnvironmentMap(environmentMap);

	// Create capture buffers
	for (unsigned int i = 0; i < 6; i++)
	{
		entity->getCaptureBuffer(i).createColorTexture(Ivec2(0), Ivec2(500), 1, false);
	}
}