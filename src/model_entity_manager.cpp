#include "model_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;
using std::max;

shared_ptr<ModelEntity> ModelEntityManager::getEntity(const string& id)
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		Logger::throwError("ModelEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<ModelEntity>>& ModelEntityManager::getEntities()
{
	return _entities;
}

void ModelEntityManager::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
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
	auto entity = make_shared<ModelEntity>(id);

	_entities.insert(make_pair(id, entity));

	auto mesh = _meshLoader->loadMesh(meshPath);

	if(mesh == nullptr)
	{
		deleteEntity(id);
		return;
	}

	if((mesh->getParts().size() == 1) && !mesh->getParts()[0]->getID().empty())
	{
		Logger::throwWarning("Multiparted model with id \"" + id + "\" only has 1 part!");
		deleteEntity(id);
		return;
	}

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

		entity->createPart(part->getID());

		auto vertexBuffer = _vertexBufferCache->getBuffer(meshPath, part->getID());

		if(vertexBuffer == nullptr)
		{
			vertexBuffer = make_shared<VertexBuffer>(VertexBufferType::POS_UV_NOR_TAN, &bufferData[0], static_cast<unsigned int>(bufferData.size()));

			_vertexBufferCache->storeBuffer(meshPath, part->getID(), vertexBuffer);
		}

		entity->setMesh(part->getID(), vertexBuffer);
	}

	entity->setMeshPath(meshPath);
}

void ModelEntityManager::deleteEntity(const string& id)
{
	if(!isEntityExisting(id))
	{
		Logger::throwError("ModelEntityManager::deleteEntity");
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

void ModelEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();

		if(entity->isVisible())
		{
			if(!entity->getLevelOfDetailEntityID().empty())
			{
				auto levelOfDetailEntityPair = getEntities().find(entity->getID());
				if(levelOfDetailEntityPair == getEntities().end())
				{
					Logger::throwError("ModelEntityManager::update");
				}

				auto cameraPosition = _renderBus->getCameraPosition();
				auto entityPosition = entity->getBasePosition();
				auto absolsuteDistance = Math::calculateDistance(cameraPosition, entityPosition);

				bool isFarEnough = (absolsuteDistance > entity->getLevelOfDetailDistance()) && (!entity->getLevelOfDetailEntityID().empty());
				entity->setLevelOfDetailed(isFarEnough);
			}

			if((_timer->getPassedTickCount() % Config::UPDATES_PER_SECOND) == 0)
			{
				map<float, shared_ptr<ReflectionEntity>> reflectionDistanceMap;
				for(const auto& [key, reflectionEntity] : _reflectionManager->getEntities())
				{
					if(reflectionEntity->isVisible())
					{
						auto absoluteDistance = Math::calculateDistance(entity->getBasePosition(), reflectionEntity->getPosition());
						reflectionDistanceMap.insert(make_pair(absoluteDistance, reflectionEntity));
					}
				}

				if(_reflectionManager->getEntities().find(entity->getPreviousReflectionEntityID()) == _reflectionManager->getEntities().end())
				{
					entity->setPreviousReflectionEntityID("");
					entity->setCubeReflectionMixValue(1.0f);
				}
				if(_reflectionManager->getEntities().find(entity->getCurrentReflectionEntityID()) == _reflectionManager->getEntities().end())
				{
					entity->setCurrentReflectionEntityID("");
					entity->setCubeReflectionMixValue(1.0f);
				}
				if(entity->getPreviousReflectionEntityID() == entity->getCurrentReflectionEntityID())
				{
					entity->setPreviousReflectionEntityID("");
					entity->setCubeReflectionMixValue(1.0f);
				}

				if(!reflectionDistanceMap.empty())
				{
					auto& closestReflectionEntityID = reflectionDistanceMap.begin()->second->getID();

					if(entity->getCurrentReflectionEntityID() != closestReflectionEntityID)
					{
						entity->setPreviousReflectionEntityID(entity->getCurrentReflectionEntityID());
						entity->setCurrentReflectionEntityID(closestReflectionEntityID);

						if(!entity->getPreviousReflectionEntityID().empty())
						{
							entity->setCubeReflectionMixValue(0.0f);
						}
					}
				}

				entity->setCubeReflectionMixValue(entity->getCubeReflectionMixValue() + CUBE_REFLECTION_OVERLAP_SPEED);
			}

			entity->updateTransformationMatrix();
		}
	}
}