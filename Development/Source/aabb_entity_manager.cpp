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
		Logger::throwError("Nonexisting AABB entity with ID " + ID + " requested");
	}

	return result;
}

const vector<shared_ptr<AabbEntity>>& AabbEntityManager::getEntities()
{
	return _getAabbEntities();
}

void AabbEntityManager::addAabbEntity(const string& ID, vec3 position, vec3 size, bool responsive)
{
	// Create entity
	_createEntity(ID);
	getEntity(ID)->addOglBuffer(_openglBuffer, false);

	// Other
	getEntity(ID)->setLocalTranslation(position);
	getEntity(ID)->setLocalScaling(size);
	getEntity(ID)->setTranslation(position);
	getEntity(ID)->setScaling(size);
	getEntity(ID)->setResponsiveness(responsive);
}

void AabbEntityManager::bindAabbEntity(const string& ID, const string& parentID, AabbParentType parentType, vec3 position, vec3 size, bool responsive)
{
	addAabbEntity(ID, position, size, responsive);
	getEntity(ID)->setParent(parentID, parentType);
}

void AabbEntityManager::update(const vector<shared_ptr<GameEntity>>& gameEntities, const vector<shared_ptr<BillboardEntity>>& billboardEntities)
{
	for (auto& entity : _getAabbEntities())
	{
		// Optional translation update
		if (entity->getParentID() != "")
		{
			bool found = false;

			// Determine parent type
			if (entity->getParentType() == AabbParentType::GAME_ENTITY)
			{
				for (auto& parentEntity : gameEntities) // Loop over GAME entities
				{
					if (entity->getParentID() == parentEntity->getID()) // Check for match
					{
						vec3 parentSizeChange = parentEntity->getScaling() / parentEntity->getOriginalScaling();

						// Update scaling (based on parent scaling)
						entity->setScaling(entity->getLocalScaling() * parentSizeChange);

						// Update translation (based on parent translation + scaling)
						entity->setTranslation(parentEntity->getTranslation() + (entity->getLocalTranslation() * parentSizeChange));

						// Update visibility
						entity->setVisible(parentEntity->isVisible());

						found = true;
					}
				}

				// Error logging
				if (!found)
				{
					Logger::throwError("AABB entity \"" + entity->getID() + "\" bound to nonexisting GAME entity \"" + entity->getParentID() + "\"");
				}
			}
			else if(entity->getParentType() == AabbParentType::BILLBOARD_ENTITY)
			{
				for (auto& parentEntity : billboardEntities) // Loop over BILLBOARD entities
				{
					if (entity->getParentID() == parentEntity->getID()) // Check for match
					{
						// Retrieve parent rotation & size
						float rotationX = fabsf(parentEntity->getRotation().x);
						float rotationY = fabsf(parentEntity->getRotation().y);
						float rotationZ = fabsf(parentEntity->getRotation().z);
						vec3 parentSize = parentEntity->getScaling();
						float maxParentSize = std::max(parentSize.x, parentSize.y);
						vec3 newAabbSize = vec3(parentSize.x, parentSize.y, 0.1f);

						// Determine rotation direction
						if (rotationX != 0.0f)
						{
							newAabbSize.z = fabsf(sinf(Tools::getInst().degreeToRadians(rotationX)) * parentSize.y);
						}
						else if (rotationY != 0.0f)
						{
							newAabbSize.x = fabsf(cosf(Tools::getInst().degreeToRadians(rotationY)) * parentSize.x);
							newAabbSize.z = fabsf(sinf(Tools::getInst().degreeToRadians(rotationY)) * parentSize.x);
						}
						else if (rotationZ != 0.0f)
						{
							newAabbSize.x = fabsf(sinf(Tools::getInst().degreeToRadians(rotationZ)) * parentSize.y) +
								fabsf(cosf(Tools::getInst().degreeToRadians(rotationZ)) * parentSize.x);
							newAabbSize.y = fabsf(sinf(Tools::getInst().degreeToRadians(rotationZ)) * parentSize.x)
								+ fabsf(cosf(Tools::getInst().degreeToRadians(rotationZ)) * parentSize.y);
						}

						// Update scaling (based on parent rotation)
						entity->setScaling(newAabbSize);

						// Update translation (based on parent translation + scaling)
						vec3 halfSizeOffset = vec3(0.0f, (parentEntity->getScaling().y / 2.0f), 0.0f);
						entity->setTranslation(parentEntity->getTranslation() + entity->getLocalTranslation() - halfSizeOffset);

						// Update visibility
						entity->setVisible(parentEntity->isVisible());


						found = true;
					}
				}

				// Error logging
				if (!found)
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