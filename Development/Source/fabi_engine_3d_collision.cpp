#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::aabbEntity_deleteAll()
{
	_core->_aabbEntityManager.deleteAllEntities();
}

void FabiEngine3D::aabbEntity_add(const string& ID, vec3 position, vec3 size, bool responsive)
{
	_core->_aabbEntityManager.addAabbEntity(ID, position, size, responsive);
}

void FabiEngine3D::aabbEntity_bindToGameEntity(const string& parentID, vec3 position, vec3 size, bool responsive, const string& customAabbID)
{
	if (customAabbID == "") // Use parent ID
	{
		if (_core->_gameEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(parentID, parentID, AabbParentType::GAME_ENTITY, position, size, responsive);
		}
		else
		{
			logger_throwError("Tried to bind AABB entity to non-existing GAME entity \"" + parentID + "\"");
		}
	}
	else // Use custom ID
	{
		if (_core->_gameEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(customAabbID, parentID, AabbParentType::GAME_ENTITY, position, size, responsive);
		}
		else
		{
			logger_throwError("Tried to bind AABB entity \"" + customAabbID + "\" to non-existing GAME entity \"" + parentID + "\"");
		}
	}
}

void FabiEngine3D::aabbEntity_bindToBillboardEntity(const string& parentID, bool responsive, const string& customAabbID)
{
	if (customAabbID == "") // Use parent ID
	{
		if (_core->_billboardEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(parentID, parentID, AabbParentType::BILLBOARD_ENTITY, vec3(0.0f), vec3(0.0f), responsive);
		}
		else
		{
			logger_throwError("Tried to bind AABB entity to non-existing BILLBOARD entity \"" + parentID + "\"");
		}
	}
	else // Use custom ID
	{
		if (_core->_billboardEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(customAabbID, parentID, AabbParentType::BILLBOARD_ENTITY, vec3(0.0f), vec3(0.0f), responsive);
		}
		else
		{
			logger_throwError("Tried to bind AABB entity \"" + customAabbID + "\" to non-existing BILLBOARD entity \"" + parentID + "\"");
		}
	}
}

void FabiEngine3D::aabbEntity_delete(const string& ID)
{
	_core->_aabbEntityManager.deleteEntity(ID);
}

void FabiEngine3D::aabbEntity_hide(const string& ID)
{
	_core->_aabbEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::aabbEntity_show(const string& ID)
{
	_core->_aabbEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::aabbEntity_setResponsiveness(const string& ID, bool responsive)
{
	_core->_aabbEntityManager.getEntity(ID)->setResponsiveness(responsive);
}

void FabiEngine3D::aabbEntity_setPosition(const string& ID, vec3 position)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "") // Standalone entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setTranslation(position);
	}
	else // Bound entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setLocalTranslation(position);
	}
}

void FabiEngine3D::aabbEntity_setSize(const string& ID, vec3 size)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "") // Standalone entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setScaling(size);
	}
	else // Bound entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setLocalScaling(size);
	}
}

vec3 FabiEngine3D::aabbEntity_getPosition(const string& ID)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "") // Standalone entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getTranslation();
	}
	else // Bound entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalTranslation();
	}
}

vec3 FabiEngine3D::aabbEntity_getSize(const string& ID)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "") // Standalone entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getScaling();
	}
	else // Bound entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalScaling();
	}
}

bool FabiEngine3D::aabbEntity_isResponsive(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isResponsive();
}

bool FabiEngine3D::aabbEntity_isExisting(const string& ID)
{
	return _core->_aabbEntityManager.isExisting(ID);
}

bool FabiEngine3D::aabbEntity_isVisible(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isVisible();
}

vector<string> FabiEngine3D::aabbEntity_getBoundIDs(const string& parentID, bool gameEntity, bool billboardEntity)
{
	vector<string> IDs;

	for (auto entity : _core->_aabbEntityManager.getEntities())
	{
		if (parentID == entity->getParentID() && 
			((entity->getParentType() == AabbParentType::GAME_ENTITY && gameEntity) ||
			(entity->getParentType() == AabbParentType::BILLBOARD_ENTITY && billboardEntity)))
		{
			IDs.push_back(entity->getID());
		}
	}

	return IDs;
}

vector<string> FabiEngine3D::aabbEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto entity : _core->_aabbEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

void FabiEngine3D::collision_enableCameraResponse()
{
	_core->_collisionResolver.enableAabbResponse();
}

void FabiEngine3D::collision_disableCameraResponse()
{
	_core->_collisionResolver.disableAabbResponse();
}

void FabiEngine3D::collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed)
{
	_core->_collisionResolver.enableTerrainResponse(cameraHeight, cameraSpeed);
}

void FabiEngine3D::collision_disableCameraTerrainResponse()
{
	_core->_collisionResolver.disableTerrainResponse();
}

bool FabiEngine3D::collision_checkAnyWithCamera()
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
	{
		if (entity->getCollisionDirection() != Direction::NONE)
		{
			return true;
		}
	}

	return false;
}

bool FabiEngine3D::collision_checkEntityWithCamera(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection() != Direction::NONE;
}

const string& FabiEngine3D::collision_checkEntityWithOthers(const string& ID)
{
	// Self entity
	auto self = _core->_aabbEntityManager.getEntity(ID);
	vec3 selfPos = self->getTranslation();
	vec3 selfSize = self->getScaling();

	if (self->isResponsive())
	{
		for (auto other : _core->_aabbEntityManager.getEntities()) // Loop over all AABB entities
		{
			if (other->getID() != ID && other->isResponsive()) // Don't check own entity & other entity must be responsive
			{
				vec3 otherPos = other->getTranslation();
				vec3 otherSize = other->getScaling();

				// Check XYZ collision between 2 entities
				if
					(
						// Check both all X collision situations
						((selfPos.z > otherPos.z - otherSize.z && selfPos.z < otherPos.z + otherSize.z) || // Middle coordinate within
							(selfPos.z - selfSize.z > otherPos.z - otherSize.z && selfPos.z - selfSize.z < otherPos.z + otherSize.z) || // Lower corner within
							(selfPos.z + selfSize.z > otherPos.z - otherSize.z && selfPos.z + selfSize.z < otherPos.z + otherSize.z) || // Upper corner within 
							(selfPos.z - selfSize.z < otherPos.z - otherSize.z && selfPos.z + selfSize.z > otherPos.z + otherSize.z))   // AABB too big but overlapping 

						&&

						// Check both all Y collision situations
						((selfPos.y > otherPos.y - otherSize.y && selfPos.y < otherPos.y + otherSize.y) || // Middle coordinate within
							(selfPos.y - selfSize.y > otherPos.y - otherSize.y && selfPos.y - selfSize.y < otherPos.y + otherSize.y) || // Lower corner within
							(selfPos.y + selfSize.y > otherPos.y - otherSize.y && selfPos.y + selfSize.y < otherPos.y + otherSize.y) || // Upper corner within 
							(selfPos.y - selfSize.y < otherPos.y - otherSize.y && selfPos.y + selfSize.y > otherPos.y + otherSize.y))   // AABB too big but overlapping 

						&&

						// Check both all Z collision situations
						((selfPos.x > otherPos.x - otherSize.x && selfPos.x < otherPos.x + otherSize.x) || // Middle coordinate within
							(selfPos.x - selfSize.x > otherPos.x - otherSize.x && selfPos.x - selfSize.x < otherPos.x + otherSize.x) || // Lower corner within
							(selfPos.x + selfSize.x > otherPos.x - otherSize.x && selfPos.x + selfSize.x < otherPos.x + otherSize.x) || // Upper corner within 
							(selfPos.x - selfSize.x < otherPos.x - otherSize.x && selfPos.x + selfSize.x > otherPos.x + otherSize.x))   // AABB too big but overlapping 
						)
				{
					return other->getID();
				}
			}
		}
	}

	return "";
}

const string& FabiEngine3D::collision_checkEntitiesWithCamera(const string& ID)
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				auto direction = entity->getCollisionDirection(); // Calculate direction

				// True if collides
				if (direction != Direction::NONE)
				{
					return entity->getID();
				}
			}
		}
	}

	// No collision
	return "";
}

string FabiEngine3D::collision_checkCursorInAny()
{
	float closestDistance = (std::numeric_limits<float>::max)();
	string closestBoxID = "";

	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
	{
		if (entity->isResponsive())
		{
			// Calculate box left bottom (LB) and right top (RT)
			vec3 lb, rt;
			lb.x = (entity->getTranslation().x - entity->getScaling().x / 2.0f);
			lb.y = (entity->getTranslation().y);
			lb.z = (entity->getTranslation().z + entity->getScaling().z / 2.0f);
			rt.x = (entity->getTranslation().x + entity->getScaling().x / 2.0f);
			rt.y = (entity->getTranslation().y + entity->getScaling().y);
			rt.z = (entity->getTranslation().z - entity->getScaling().z / 2.0f);

			// Check intersection
			float distance = _core->_mousePicker.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition());

			// Check if closest to camera
			if (distance != -1.0f && distance < closestDistance)
			{
				closestDistance = distance;
				closestBoxID = entity->getID();
			}
		}
	}

	// No intersection
	return closestBoxID;
}

bool FabiEngine3D::collision_checkCursorInEntity(const string& ID)
{
	auto entity = _core->_aabbEntityManager.getEntity(ID);

	if (entity->isResponsive())
	{
		vec3 lb, rt;
		lb.x = (entity->getTranslation().x - entity->getScaling().x / 2.0f);
		lb.y = (entity->getTranslation().y);
		lb.z = (entity->getTranslation().z + entity->getScaling().z / 2.0f);
		rt.x = (entity->getTranslation().x + entity->getScaling().x / 2.0f);
		rt.y = (entity->getTranslation().y + entity->getScaling().y);
		rt.z = (entity->getTranslation().z - entity->getScaling().z / 2.0f);
		
		return _core->_mousePicker.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition()) != -1.0f;
	}

	return false;
}

string FabiEngine3D::collision_checkCursorInEntities(const string& ID, const string& exception)
{
	float closestDistance = (std::numeric_limits<float>::max)();
	string closestBoxID = "";

	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
	{
		if (entity->isResponsive())
		{
			if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
			{
				auto subString = entity->getID().substr(0, ID.size());
				if (subString == ID && entity->getID() != exception) // If entity matches ID
				{
					// Calculate box left bottom (LB) and right top (RT)
					vec3 lb, rt;
					lb.x = (entity->getTranslation().x - entity->getScaling().x / 2.0f);
					lb.y = (entity->getTranslation().y);
					lb.z = (entity->getTranslation().z + entity->getScaling().z / 2.0f);
					rt.x = (entity->getTranslation().x + entity->getScaling().x / 2.0f);
					rt.y = (entity->getTranslation().y + entity->getScaling().y);
					rt.z = (entity->getTranslation().z - entity->getScaling().z / 2.0f);

					// Check intersection
					float distance = _core->_mousePicker.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition());

					// Check if closest to camera
					if (distance != -1.0f && distance < closestDistance)
					{
						closestDistance = distance;
						closestBoxID = entity->getID();
					}
				}
			}
		}
	}

	// No intersection
	return closestBoxID;
}

ivec3 FabiEngine3D::collision_checkEntityWithCameraDirection(const string& ID)
{
	// Calculate direction
	auto state = _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection();

	// Return collision
	return ivec3(state == Direction::X, state == Direction::Y, state == Direction::Z);
}

ivec3 FabiEngine3D::collision_checkEntitiesWithCameraDirection(const string& ID)
{
	for (auto entity : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				auto direction = entity->getCollisionDirection(); // Calculate direction

				// Return direction if collides
				if (direction != Direction::NONE)
				{
					return ivec3(direction == Direction::X, direction == Direction::Y, direction == Direction::Z);
				}
			}
		}
	}

	// No collision
	return ivec3(0);
}