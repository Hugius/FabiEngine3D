#include "reflection_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

shared_ptr<ReflectionEntity> ReflectionEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("ReflectionEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<ReflectionEntity>>& ReflectionEntityManager::getEntities()
{
	return _entities;
}

void ReflectionEntityManager::createEntity(const string& ID)
{
	auto entity = make_shared<ReflectionEntity>(ID);

	_entities.insert(make_pair(ID, entity));

	BufferID textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	entity->setCubeMap(make_shared<TextureBuffer>(textureID));
}

void ReflectionEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();
	}
}

void ReflectionEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("ReflectionEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void ReflectionEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool ReflectionEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}