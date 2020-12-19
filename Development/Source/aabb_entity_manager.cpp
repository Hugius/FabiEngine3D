#include "aabb_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp" 
#include "tools.hpp"

AabbEntityManager::AabbEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::AABB, objLoader, texLoader, renderBus)
{
	float box_data[] =
	{
		-0.5f,  1.0f, -0.5f,
		 0.5f,  1.0f, -0.5f,
		 0.5f,  0.0f, -0.5f,
		-0.5f,  0.0f, -0.5f,
		-0.5f,  1.0f, -0.5f,
		-0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f,  0.5f,
		 0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f,  0.5f,
		-0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f, -0.5f,
		 0.5f,  0.0f, -0.5f,
		 0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f, -0.5f
	};

	_openglBuffer = new OpenGLBuffer(BufferType::AABB, box_data, sizeof(box_data) / sizeof(float));
}

shared_ptr<AabbEntity> AabbEntityManager::getEntity(const string& ID)
{
	auto result = _getAabbEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting AABB entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<AabbEntity>>& AabbEntityManager::getEntities()
{
	return _getAabbEntities();
}

void AabbEntityManager::addAabbEntity(const string& ID, Vec3 position, Vec3 size, bool responsive)
{
	// Create entity
	_createEntity(ID);
	auto entity = getEntity(ID);
	entity->addOglBuffer(_openglBuffer, false);

	// Other
	entity->setLocalTranslation(position);
	entity->setLocalScaling(size);
	entity->setTranslation(position);
	entity->setScaling(size);
	entity->setResponsive(responsive);
}

void AabbEntityManager::bindAabbEntity(const string& ID, const string& parentID, AabbParentType parentType, Vec3 position, Vec3 size, bool responsive)
{
	addAabbEntity(ID, position, size, responsive);
	getEntity(ID)->setParent(parentID, parentType);
}

void AabbEntityManager::update(
	const unordered_map<string, shared_ptr<GameEntity>>& gameEntities, 
	const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities)
{
	for (auto& [keyID, entity] : _getAabbEntities())
	{
		// Optional translation update
		if (entity->getParentID() != "")
		{
			// Determine parent type
			if (entity->getParentType() == AabbParentType::GAME_ENTITY)
			{
				// Try to find the parent entity
				auto foundPair = gameEntities.find(entity->getParentID());
				if(foundPair != gameEntities.end())
				{
					auto parentEntity = foundPair->second;

					// Game entity must not be LODded
					if (!parentEntity->isLevelOfDetailed())
					{
						// Update scaling (based on parent scaling)
						entity->setScaling(entity->getLocalScaling() * parentEntity->getScaling());

						// Update translation (based on parent translation + scaling)
						entity->setTranslation(parentEntity->getTranslation() + (entity->getLocalTranslation() * parentEntity->getScaling()));

						// Update visibility
						entity->setVisible(parentEntity->isVisible());
					}
				}
				else
				{
					Logger::throwError("AABB entity \"" + entity->getID() + "\" bound to nonexisting GAME entity \"" + entity->getParentID() + "\"");
				}
			}
			else if(entity->getParentType() == AabbParentType::BILLBOARD_ENTITY)
			{
				// Try to find the parent entity
				auto foundPair = billboardEntities.find(entity->getParentID());
				if (foundPair != billboardEntities.end())
				{
					auto parentEntity = foundPair->second;

					// Retrieve parent rotation & size
					float rotationX = fabsf(parentEntity->getRotation().x);
					float rotationY = fabsf(parentEntity->getRotation().y);
					float rotationZ = fabsf(parentEntity->getRotation().z);
					Vec3 parentSize = parentEntity->getScaling();
					float maxParentSize = std::max(parentSize.x, parentSize.y);
					Vec3 newAabbSize = Vec3(parentSize.x, parentSize.y, 0.1f);

					// Determine rotation direction
					if (rotationX != 0.0f)
					{
						newAabbSize.z = fabsf(sinf(Math::degreesToRadians(rotationX)) * parentSize.y);
					}
					else if (rotationY != 0.0f)
					{
						newAabbSize.x = fabsf(cosf(Math::degreesToRadians(rotationY)) * parentSize.x);
						newAabbSize.z = fabsf(sinf(Math::degreesToRadians(rotationY)) * parentSize.x);
					}
					else if (rotationZ != 0.0f)
					{
						newAabbSize.x = fabsf(sinf(Math::degreesToRadians(rotationZ)) * parentSize.y) +
							fabsf(cosf(Math::degreesToRadians(rotationZ)) * parentSize.x);
						newAabbSize.y = fabsf(sinf(Math::degreesToRadians(rotationZ)) * parentSize.x)
							+ fabsf(cosf(Math::degreesToRadians(rotationZ)) * parentSize.y);
					}

					// Update scaling (based on parent rotation)
					entity->setScaling(newAabbSize);

					// Update translation (based on parent translation + scaling)
					Vec3 halfSizeOffset = Vec3(0.0f, (parentEntity->getScaling().y / 2.0f), 0.0f);
					entity->setTranslation(parentEntity->getTranslation() + entity->getLocalTranslation() - halfSizeOffset);

					// Update visibility
					entity->setVisible(parentEntity->isVisible());
				}
				else
				{
					Logger::throwError("AABB entity \"" + entity->getID() + "\" bound to nonexisting BILLBOARD entity \"" + entity->getParentID() + "\"");
				}
			}
		}

		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}
	}
}