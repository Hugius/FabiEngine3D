#include "model_entity_manager.hpp"
#include "logger.hpp"

#include <map>

using std::make_shared;
using std::max;
using std::map;

shared_ptr<ModelEntity> ModelEntityManager::getEntity(const string& id)
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<ModelEntity>>& ModelEntityManager::getEntities()
{
	return _entities;
}

void ModelEntityManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void ModelEntityManager::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void ModelEntityManager::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void ModelEntityManager::inject(shared_ptr<ReflectionEntityManager> reflectionManager)
{
	_reflectionManager = reflectionManager;
}

void ModelEntityManager::inject(shared_ptr<MeshLoader> meshLoader)
{
	_meshLoader = meshLoader;
}

void ModelEntityManager::inject(shared_ptr<VertexBufferCache> vertexBufferCache)
{
	_vertexBufferCache = vertexBufferCache;
}

void ModelEntityManager::createEntity(const string& id, const string& meshPath)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto mesh = _meshLoader->loadMesh(meshPath);

	if(mesh == nullptr)
	{
		return;
	}

	auto entity = make_shared<ModelEntity>(id);

	for(const auto& part : mesh->getParts())
	{
		vector<float> bufferData;

		for(size_t i = 0; i < part->getPositions().size(); i++)
		{
			bufferData.push_back(part->getPositions()[i].x);
			bufferData.push_back(part->getPositions()[i].y);
			bufferData.push_back(part->getPositions()[i].z);

			bufferData.push_back(part->getUvs()[i].x);
			bufferData.push_back(part->getUvs()[i].y);

			bufferData.push_back(part->getNormals()[i].x);
			bufferData.push_back(part->getNormals()[i].y);
			bufferData.push_back(part->getNormals()[i].z);

			bufferData.push_back(part->getTangents()[i].x);
			bufferData.push_back(part->getTangents()[i].y);
			bufferData.push_back(part->getTangents()[i].z);
		}

		entity->createPart(part->getId());

		auto vertexBuffer = _vertexBufferCache->getBuffer(meshPath, part->getId());

		if(vertexBuffer == nullptr)
		{
			vertexBuffer = make_shared<VertexBuffer>(VertexBufferType::POS_UV_NOR_TAN, &bufferData[0], static_cast<unsigned int>(bufferData.size()));

			_vertexBufferCache->storeBuffer(meshPath, part->getId(), vertexBuffer);
		}

		entity->setMesh(part->getId(), vertexBuffer);
	}

	entity->setMeshPath(meshPath);

	_entities.insert(make_pair(id, entity));
}

void ModelEntityManager::deleteEntity(const string& id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void ModelEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool ModelEntityManager::isEntityExisting(const string& id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool ModelEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void ModelEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTarget();

		if(!entity->isVisible())
		{
			continue;
		}

		if(entity->getLevelOfDetailEntityId().empty())
		{
			entity->setLevelOfDetailed(false);
		}
		else
		{
			if(getEntities().find(entity->getId()) == getEntities().end())
			{
				abort();
			}

			const auto cameraPosition = _camera->getPosition();
			const auto entityPosition = entity->getBasePosition();
			const auto absolsuteDistance = Math::calculateDistance(cameraPosition, entityPosition);

			entity->setLevelOfDetailed((absolsuteDistance > entity->getLevelOfDetailDistance()));
		}

		if(_reflectionManager->getEntities().find(entity->getPreviousReflectionEntityId()) == _reflectionManager->getEntities().end())
		{
			entity->setPreviousReflectionEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}
		if(_reflectionManager->getEntities().find(entity->getCurrentReflectionEntityId()) == _reflectionManager->getEntities().end())
		{
			entity->setCurrentReflectionEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}
		if(entity->getPreviousReflectionEntityId() == entity->getCurrentReflectionEntityId())
		{
			entity->setPreviousReflectionEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}

		if((_renderStorage->getCubeReflectionInterval() == 0) || (_timer->getPassedUpdateCount() % _renderStorage->getCubeReflectionInterval()) == 0)
		{
			map<float, shared_ptr<ReflectionEntity>> orderedReflectionEntities;

			for(const auto& [key, reflectionEntity] : _reflectionManager->getEntities())
			{
				if(reflectionEntity->isVisible())
				{
					const auto absoluteDistance = Math::calculateDistance(entity->getBasePosition(), reflectionEntity->getPosition());

					orderedReflectionEntities.insert(make_pair(absoluteDistance, reflectionEntity));
				}
			}

			if(!orderedReflectionEntities.empty())
			{
				const auto closestReflectionEntityId = orderedReflectionEntities.begin()->second->getId();

				if(entity->getCurrentReflectionEntityId() != closestReflectionEntityId)
				{
					entity->setPreviousReflectionEntityId(entity->getCurrentReflectionEntityId());
					entity->setCurrentReflectionEntityId(closestReflectionEntityId);

					if(!entity->getPreviousReflectionEntityId().empty())
					{
						entity->setCubeReflectionMixValue(0.0f);
					}
				}
			}

			entity->setCubeReflectionMixValue(entity->getCubeReflectionMixValue() + CUBE_REFLECTION_OVERLAP_SPEED);
		}

		entity->updateTransformation();
	}
}