#include "aabb_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

AabbEntityManager::AabbEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(objLoader, texLoader, renderBus)
{
	
}

AabbEntity * AabbEntityManager::getEntity(const string& ID)
{
	return dynamic_cast<AabbEntity*>(_getBaseEntity(ID, EntityType::AABB));
}

const vector<AabbEntity*> AabbEntityManager::getEntities()
{
	vector<AabbEntity*> newVector;

	for (auto& entity : _getBaseEntities())
	{
		newVector.push_back(dynamic_cast<AabbEntity*>(entity));
	}

	return newVector;
}

void AabbEntityManager::addAabbEntity(const string& ID, vec3 position, vec3 size, bool responsive)
{
	// Load OBJ model
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

	// Create entity
	_createEntity(EntityType::AABB, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(BufferType::AABB, box_data, sizeof(box_data) / sizeof(float)));

	// Other
	getEntity(ID)->setLocalTranslation(position);
	getEntity(ID)->setTranslation(position);
	getEntity(ID)->setScaling(size);
	getEntity(ID)->setResponsiveness(responsive);
}

void AabbEntityManager::bindAabbEntity(const string& ID, const string& parentID, AabbParentType parentType, vec3 position, vec3 size, bool responsive)
{
	addAabbEntity(ID, position, size, responsive);
	getEntity(ID)->setParent(parentID, parentType);
}

void AabbEntityManager::update(const vector<GameEntity*>& gameEntities, const vector<BillboardEntity*>& billboardEntities)
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary billboard entity object
		auto * entity = getEntity(baseEntity->getID());

		// Optional translation update
		if (entity->getParentID() != "")
		{
			bool found = false;

			// Determine parent type
			if (entity->getParentType() == AabbParentType::GAME_ENTITY)
			{
				for (auto& gameEntity : gameEntities) // Loop over GAME entities
				{
					if (entity->getParentID() == gameEntity->getID()) // Check for match
					{
						entity->setTranslation(gameEntity->getTranslation() + entity->getLocalTranslation()); // Update translation
						found = true;
					}
				}

				// Error logging
				if (!found)
				{
					Logger::throwError("Collision entity \"" + entity->getID() + "\" bound to nonexisting GAME entity \"" + entity->getParentID() + "\"");
				}
			}
			else if(entity->getParentType() == AabbParentType::BILLBOARD_ENTITY)
			{
				for (auto& billboardEntity : billboardEntities) // Loop over BILLBOARD entities
				{
					if (entity->getParentID() == billboardEntity->getID()) // Check for match
					{
						entity->setTranslation(billboardEntity->getTranslation() + entity->getLocalTranslation()); // Update translation
						found = true;
					}
				}

				// Error logging
				if (!found)
				{
					Logger::throwError("Collision entity \"" + entity->getID() + "\" bound to nonexisting BILLBOARD entity \"" + entity->getParentID() + "\"");
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