#include "model_entity_manager.hpp"

#include <map>

using std::make_shared;
using std::max;
using std::map;

const shared_ptr<Model> ModelManager::getEntity(const string & modelId) const
{
	auto iterator = _entities.find(modelId);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Model>> & ModelManager::getEntities() const
{
	return _entities;
}

void ModelManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void ModelManager::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void ModelManager::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void ModelManager::inject(shared_ptr<CaptorManager> captorManager)
{
	_captorManager = captorManager;
}

void ModelManager::inject(shared_ptr<MeshLoader> meshLoader)
{
	_meshLoader = meshLoader;
}

void ModelManager::inject(shared_ptr<VertexBufferCache> vertexBufferCache)
{
	_vertexBufferCache = vertexBufferCache;
}

void ModelManager::createEntity(const string & modelId, const string & meshPath)
{
	if(isEntityExisting(modelId))
	{
		abort();
	}

	auto mesh = _meshLoader->loadMesh(meshPath);

	if(mesh == nullptr)
	{
		return;
	}

	auto entity = make_shared<Model>(modelId);

	for(const auto & part : mesh->getParts())
	{
		vector<float> bufferData;

		for(int index = 0; index < static_cast<int>(part->getPositions().size()); index++)
		{
			bufferData.push_back(part->getPositions()[index].x);
			bufferData.push_back(part->getPositions()[index].y);
			bufferData.push_back(part->getPositions()[index].z);

			bufferData.push_back(part->getUvs()[index].x);
			bufferData.push_back(part->getUvs()[index].y);

			bufferData.push_back(part->getNormals()[index].x);
			bufferData.push_back(part->getNormals()[index].y);
			bufferData.push_back(part->getNormals()[index].z);

			bufferData.push_back(part->getTangents()[index].x);
			bufferData.push_back(part->getTangents()[index].y);
			bufferData.push_back(part->getTangents()[index].z);
		}

		entity->createPart(part->getName());

		auto vertexBuffer = _vertexBufferCache->getBuffer(meshPath, part->getName());

		if(vertexBuffer == nullptr)
		{
			vertexBuffer = make_shared<VertexBuffer>(VertexBufferType::POS_UV_NOR_TAN, &bufferData[0], static_cast<int>(bufferData.size()));

			_vertexBufferCache->storeBuffer(meshPath, part->getName(), vertexBuffer);
		}

		entity->setVertexBuffer(part->getName(), vertexBuffer);
	}

	entity->setMeshPath(meshPath);

	_entities.insert({modelId, entity});
}

void ModelManager::deleteEntity(const string & modelId)
{
	if(!isEntityExisting(modelId))
	{
		abort();
	}

	_entities.erase(modelId);
}

void ModelManager::deleteEntities()
{
	_entities.clear();
}

const bool ModelManager::isEntityExisting(const string & modelId) const
{
	return (_entities.find(modelId) != _entities.end());
}

const bool ModelManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void ModelManager::update()
{
	for(const auto & [entityId, entity] : _entities)
	{
		entity->updateTarget();

		if(!entity->isVisible())
		{
			continue;
		}

		if(entity->getLevelOfDetailId().empty())
		{
			entity->setLevelOfDetailed(false);
		}
		else
		{
			if(getEntities().find(entity->getLevelOfDetailId()) == getEntities().end())
			{
				abort();
			}

			const auto cameraPosition = _camera->getPosition();
			const auto entityPosition = entity->getBasePosition();
			const auto absolsuteDistance = Mathematics::calculateDistance(cameraPosition, entityPosition);

			entity->setLevelOfDetailed((absolsuteDistance > entity->getLevelOfDetailDistance()));
		}

		if(_captorManager->getEntities().find(entity->getPreviousCaptorEntityId()) == _captorManager->getEntities().end())
		{
			entity->setPreviousCaptorEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}
		if(_captorManager->getEntities().find(entity->getCurrentCaptorEntityId()) == _captorManager->getEntities().end())
		{
			entity->setCurrentCaptorEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}
		if(entity->getPreviousCaptorEntityId() == entity->getCurrentCaptorEntityId())
		{
			entity->setPreviousCaptorEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}

		if((_renderStorage->getCubeReflectionInterval() == 0) || (_timer->getPassedUpdateCount() % _renderStorage->getCubeReflectionInterval()) == 0)
		{
			map<float, shared_ptr<Captor>> orderedCaptorEntities;

			for(const auto & [captorEntityId, captorEntity] : _captorManager->getEntities())
			{
				if(captorEntity->isVisible())
				{
					const auto absoluteDistance = Mathematics::calculateDistance(entity->getBasePosition(), captorEntity->getPosition());

					orderedCaptorEntities.insert({absoluteDistance, captorEntity});
				}
			}

			if(!orderedCaptorEntities.empty())
			{
				const auto closestCaptorEntityId = orderedCaptorEntities.begin()->second->getId();

				if(entity->getCurrentCaptorEntityId() != closestCaptorEntityId)
				{
					entity->setPreviousCaptorEntityId(entity->getCurrentCaptorEntityId());
					entity->setCurrentCaptorEntityId(closestCaptorEntityId);

					if(!entity->getPreviousCaptorEntityId().empty())
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