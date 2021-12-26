#include "model_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;
using std::max;

ModelEntityManager::ModelEntityManager(MeshLoader& meshLoader, RenderBus& renderBus, Timer& timer)
	:
	_meshLoader(meshLoader),
	_renderBus(renderBus),
	_timer(timer)
{

}

shared_ptr<ModelEntity> ModelEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

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

void ModelEntityManager::createEntity(const string& ID, const string& meshPath)
{
	_entities.insert(make_pair(ID, make_shared<ModelEntity>(ID, meshPath)));

	auto partsPointer = _meshLoader.loadMesh(meshPath);

	if(partsPointer == nullptr)
	{
		deleteEntity(ID);
		return;
	}

	auto& parts = *partsPointer;
	if((parts.size() == 1) && !parts[0]->getID().empty())
	{
		Logger::throwWarning("Multiparted model with ID \"" + ID + "\" only has 1 part!");
		deleteEntity(ID);
		return;
	}

	auto entity = getEntity(ID);

	for(const auto& part : parts)
	{
		vector<float> bufferData;

		for(size_t i = 0; i < part->getVertices().size(); i++)
		{
			bufferData.push_back(part->getVertices()[i].x);
			bufferData.push_back(part->getVertices()[i].y);
			bufferData.push_back(part->getVertices()[i].z);

			bufferData.push_back(part->getUVs()[i].x);
			bufferData.push_back(part->getUVs()[i].y);

			bufferData.push_back(part->getNormals()[i].x);
			bufferData.push_back(part->getNormals()[i].y);
			bufferData.push_back(part->getNormals()[i].z);

			bufferData.push_back(part->getTangents()[i].x);
			bufferData.push_back(part->getTangents()[i].y);
			bufferData.push_back(part->getTangents()[i].z);
		}

		entity->createPart(part->getID());

		entity->setRenderBuffer(part->getID(), make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV_NORMAL_TANGENT, &bufferData[0], static_cast<unsigned int>(bufferData.size())));
	}
}

void ModelEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("ModelEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void ModelEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool ModelEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}

void ModelEntityManager::update(const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities)
{
	for(const auto& [keyID, entity] : _entities)
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

				auto cameraPosition = _renderBus.getCameraPosition();
				auto entityPosition = entity->getBasePosition();
				auto absolsuteDistance = Math::calculateDistance(cameraPosition, entityPosition);

				bool isFarEnough = (absolsuteDistance > entity->getLevelOfDetailDistance()) && (!entity->getLevelOfDetailEntityID().empty());
				entity->setLevelOfDetailed(isFarEnough);
			}

			if((_timer.getPassedTickCount() % Config::UPDATES_PER_SECOND) == 0)
			{
				map<float, shared_ptr<ReflectionEntity>> reflectionDistanceMap;
				for(const auto& [keyID, reflectionEntity] : reflectionEntities)
				{
					if(reflectionEntity->isVisible())
					{
						auto absoluteDistance = Math::calculateDistance(entity->getBasePosition(), reflectionEntity->getPosition());
						reflectionDistanceMap.insert(make_pair(absoluteDistance, reflectionEntity));
					}
				}

				if(reflectionEntities.find(entity->getPreviousReflectionEntityID()) == reflectionEntities.end())
				{
					entity->setPreviousReflectionEntityID("");
					entity->setCubeReflectionMixValue(1.0f);
				}
				if(reflectionEntities.find(entity->getCurrentReflectionEntityID()) == reflectionEntities.end())
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