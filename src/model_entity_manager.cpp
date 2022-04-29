#include "model_entity_manager.hpp"

#include <map>

using std::make_shared;
using std::max;
using std::map;

const shared_ptr<Model> ModelManager::getModel(const string & modelId) const
{
	auto iterator = _models.find(modelId);

	if(iterator == _models.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Model>> & ModelManager::getModels() const
{
	return _models;
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

void ModelManager::createModel(const string & modelId, const string & meshPath)
{
	if(isModelExisting(modelId))
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

	_models.insert({modelId, entity});
}

void ModelManager::deleteModel(const string & modelId)
{
	if(!isModelExisting(modelId))
	{
		abort();
	}

	_models.erase(modelId);
}

void ModelManager::deleteModels()
{
	_models.clear();
}

const bool ModelManager::isModelExisting(const string & modelId) const
{
	return (_models.find(modelId) != _models.end());
}

const bool ModelManager::isModelsExisting() const
{
	return !_models.empty();
}

void ModelManager::update()
{
	for(const auto & [entityId, entity] : _models)
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
			if(getModels().find(entity->getLevelOfDetailId()) == getModels().end())
			{
				abort();
			}

			const auto cameraPosition = _camera->getPosition();
			const auto entityPosition = entity->getBasePosition();
			const auto absolsuteDistance = Mathematics::calculateDistance(cameraPosition, entityPosition);

			entity->setLevelOfDetailed((absolsuteDistance > entity->getLevelOfDetailDistance()));
		}

		if(_captorManager->getCaptors().find(entity->getPreviousCaptorEntityId()) == _captorManager->getCaptors().end())
		{
			entity->setPreviousCaptorEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}
		if(_captorManager->getCaptors().find(entity->getCurrentCaptorEntityId()) == _captorManager->getCaptors().end())
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

			for(const auto & [captorEntityId, captorEntity] : _captorManager->getCaptors())
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