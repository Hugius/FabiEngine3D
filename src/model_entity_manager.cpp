#include "model_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;
using std::max;

ModelEntityManager::ModelEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus, Timer& timer)
	:
	BaseEntityManager(EntityType::MODEL, meshLoader, textureLoader, renderBus),
	_timer(timer)
{

}

shared_ptr<ModelEntity> ModelEntityManager::getEntity(const string& ID)
{
	auto result = _getModelEntity(ID);

	if(result == nullptr)
	{
		Logger::throwError("ModelEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<ModelEntity>>& ModelEntityManager::getEntities()
{
	return _getModelEntities();
}

void ModelEntityManager::createEntity(const string& ID, const string& meshPath)
{
	// Create entity
	_createEntity(ID);

	// Load mesh file
	auto partsPointer = _meshLoader.loadMesh(meshPath);

	// Check if model loading failed
	if(partsPointer == nullptr)
	{
		deleteEntity(ID);
		return;
	}

	// Check if multiparted model only has 1 part
	auto& parts = *partsPointer;
	if((parts.size() == 1) && !parts[0]->getID().empty())
	{
		Logger::throwWarning("Multiparted model with ID \"" + ID + "\" only has 1 part!");
		deleteEntity(ID);
		return;
	}

	// Temporary values
	auto entity = getEntity(ID);

	// Set mesh path
	entity->setMeshPath(meshPath);

	// Process parts
	for(const auto& part : parts)
	{
		// Temporary values
		vector<float> bufferData;

		// For every triangle vertex point
		for(size_t i = 0; i < part->getVertices().size(); i++)
		{
			// Vertex coordinate
			bufferData.push_back(part->getVertices()[i].x);
			bufferData.push_back(part->getVertices()[i].y);
			bufferData.push_back(part->getVertices()[i].z);

			// UV coordinate
			bufferData.push_back(part->getUVs()[i].x);
			bufferData.push_back(part->getUVs()[i].y);

			// Normal vector
			bufferData.push_back(part->getNormals()[i].x);
			bufferData.push_back(part->getNormals()[i].y);
			bufferData.push_back(part->getNormals()[i].z);

			// Tangent vector
			bufferData.push_back(part->getTangents()[i].x);
			bufferData.push_back(part->getTangents()[i].y);
			bufferData.push_back(part->getTangents()[i].z);
		}

		// New model part
		entity->createPart(part->getID());

		// Render buffer
		entity->setRenderBuffer(part->getID(), make_shared<RenderBuffer>(RenderBufferType::VERTEX_UV_NORMAL_TANGENT, &bufferData[0], static_cast<unsigned int>(bufferData.size())));
	}
}

void ModelEntityManager::update()
{
	Logger::throwError("ModelEntityManager::update");
}

void ModelEntityManager::update(const unordered_map<string, shared_ptr<ReflectionEntity>>& reflectionEntities)
{
	for(const auto& [keyID, entity] : _getModelEntities())
	{
		// Update transformation
		entity->updateTransformation();

		// Update model if visible
		if(entity->isVisible())
		{
			// Check if model has level of detail entity
			if(!entity->getLevelOfDetailEntityID().empty())
			{
				// Check if level of detail entity still exists
				auto levelOfDetailEntityPair = getEntities().find(entity->getID());
				if(levelOfDetailEntityPair == getEntities().end())
				{
					Logger::throwError("ModelEntityManager::update");
				}

				// Calculate absolute distance between camera and entity
				Vec3 cameraPosition = _renderBus.getCameraPosition();
				Vec3 entityPosition = entity->getBasePosition();
				auto absolsuteDistance = Math::calculateDistance(cameraPosition, entityPosition);

				// Check if entity is farther than level of detail distance
				bool isFarEnough = (absolsuteDistance > _levelOfDetailDistance) && (!entity->getLevelOfDetailEntityID().empty());
				entity->setLevelOfDetailed(isFarEnough);
			}

			// Update cube reflections every second
			if((_timer.getPassedTickCount() % Config::UPDATES_PER_SECOND) == 0)
			{
				// Sort reflection entities based on distance
				map<float, shared_ptr<ReflectionEntity>> reflectionDistanceMap;
				for(const auto& [keyID, reflectionEntity] : reflectionEntities)
				{
					if(reflectionEntity->isVisible())
					{
						auto absoluteDistance = Math::calculateDistance(entity->getBasePosition(), reflectionEntity->getPosition());
						reflectionDistanceMap.insert(std::make_pair(absoluteDistance, reflectionEntity));
					}
				}

				// Validate reflection IDs
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

				// Check if any reflection entity is found
				if(!reflectionDistanceMap.empty())
				{
					// Temporary values
					auto& closestReflectionEntityID = reflectionDistanceMap.begin()->second->getID();

					// Check if current reflection changed
					if(entity->getCurrentReflectionEntityID() != closestReflectionEntityID)
					{
						// Set IDs
						entity->setPreviousReflectionEntityID(entity->getCurrentReflectionEntityID());
						entity->setCurrentReflectionEntityID(closestReflectionEntityID);

						// Reset overlapping
						if(!entity->getPreviousReflectionEntityID().empty())
						{
							entity->setCubeReflectionMixValue(0.0f);
						}
					}
				}

				// Update cube reflection overlapping
				entity->setCubeReflectionMixValue(entity->getCubeReflectionMixValue() + CUBE_REFLECTION_OVERLAP_SPEED);
			}

			// Update transformation matrix
			entity->updateTransformationMatrix();
		}
	}
}

void ModelEntityManager::setLevelOfDetailDistance(float distance)
{
	_levelOfDetailDistance = max(0.0f, distance);
}

const float ModelEntityManager::getLevelOfDetailDistance() const
{
	return _levelOfDetailDistance;
}