#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::aabbEntity_deleteAll()
{
	_core->_aabbEntityManager.deleteAllEntities();
}

void FabiEngine3D::aabbEntity_add(const string& ID, Vec3 position, Vec3 size, bool responsive, bool visible)
{
	_core->_aabbEntityManager.addAabbEntity(ID, position, size, responsive);
	_core->_aabbEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::aabbEntity_bindToGameEntity(const string& parentID, Vec3 position, Vec3 size, bool responsive, const string& customAabbID)
{
	if (customAabbID.empty()) // Use parent ID
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
	if (customAabbID.empty()) // Use parent ID
	{
		if (_core->_billboardEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(parentID, parentID, AabbParentType::BILLBOARD_ENTITY, Vec3(0.0f), Vec3(0.0f), responsive);
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
			_core->_aabbEntityManager.bindAabbEntity(customAabbID, parentID, AabbParentType::BILLBOARD_ENTITY, Vec3(0.0f), Vec3(0.0f), responsive);
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

void FabiEngine3D::aabbEntity_setResponsive(const string& ID, bool responsive)
{
	_core->_aabbEntityManager.getEntity(ID)->setResponsive(responsive);
}

void FabiEngine3D::aabbEntity_setVisible(const string& ID, bool visible)
{
	_core->_aabbEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::aabbEntity_setPosition(const string& ID, Vec3 position, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setTranslation(position);
	}
	else // Bound entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setLocalTranslation(position);
	}
}

void FabiEngine3D::aabbEntity_setSize(const string& ID, Vec3 size, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setScaling(size);
	}
	else // Bound entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setLocalScaling(size);
	}
}

Vec3 FabiEngine3D::aabbEntity_getPosition(const string& ID, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getTranslation();
	}
	else // Bound entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalTranslation();
	}
}

Vec3 FabiEngine3D::aabbEntity_getSize(const string& ID, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
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

	for (auto [keyID, entity] : _core->_aabbEntityManager.getEntities())
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

	for (auto [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

string FabiEngine3D::aabbEntity_getParentID(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentID();
}

AabbParentType FabiEngine3D::aabbEntity_getParentType(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentType();
}

void FabiEngine3D::collision_setCameraBoxSize(float bottom, float top, float left, float right, float front, float back)
{
	_core->_collisionResolver.setCameraBoxSize(bottom, top, left, right, front, back);
}

void FabiEngine3D::collision_enableCameraResponse(bool x, bool y, bool z)
{
	_core->_collisionResolver.enableAabbResponse(x, y, z);
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

pair<const string, float> FabiEngine3D::collision_checkCursorInAny()
{
	// Temporary values
	float closestDistance = (std::numeric_limits<float>::max)();

	// Loop over AABB entities
	for (auto [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if parent entity is not level of detailed
		if (!(entity->getParentType() == AabbParentType::GAME_ENTITY &&
			_core->_gameEntityManager.getEntity(entity->getParentID())->isLevelOfDetailed()))
		{
			// Check if AABB is responsive
			if (entity->isResponsive() && entity->isVisible())
			{
				// Calculate box left bottom (LB) and right top (RT)
				Vec3 lb, rt;
				lb.x = (entity->getTranslation().x - entity->getScaling().x / 2.0f);
				lb.y = (entity->getTranslation().y);
				lb.z = (entity->getTranslation().z + entity->getScaling().z / 2.0f);
				rt.x = (entity->getTranslation().x + entity->getScaling().x / 2.0f);
				rt.y = (entity->getTranslation().y + entity->getScaling().y);
				rt.z = (entity->getTranslation().z - entity->getScaling().z / 2.0f);

				// Check intersection
				float distance = _core->_rayCaster.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition());

				// Check if closest to camera
				if (distance != -1.0f && distance < closestDistance)
				{
					closestDistance = distance;
					_hoveredAabbID = entity->getID();
					_hoveredAabbDistance = closestDistance;
				}
			}
		}
	}

	// Return
	_isRaycastUpdated = true;
	if (_hoveredAabbID.empty())
	{
		return make_pair("", -1.0f);
	}
	else
	{
		return make_pair(_hoveredAabbID, _hoveredAabbDistance);
	}
}

pair<bool, float> FabiEngine3D::collision_checkCursorInEntity(const string& ID, bool canBeOccluded)
{
	// Check whether the AABB can be raycasted if it's occluded by another AABB
	if (canBeOccluded)
	{
		// Check if raycasting needs to be updated
		if (!_isRaycastUpdated)
		{
			collision_checkCursorInAny();
		}

		// Check if hovered AABB still exists
		if (_core->_aabbEntityManager.isExisting(_hoveredAabbID))
		{
			auto result = (ID == _hoveredAabbID);
			return make_pair(result, _hoveredAabbDistance);
		}
		else
		{
			return make_pair(false, -1.0f);
		}
	}
	else
	{
		auto entity = _core->_aabbEntityManager.getEntity(ID);
		if (entity->isResponsive() && entity->isVisible())
		{
			// Prepare intersection box
			Vec3 lb, rt;
			lb.x = (entity->getTranslation().x - entity->getScaling().x / 2.0f);
			lb.y = (entity->getTranslation().y);
			lb.z = (entity->getTranslation().z + entity->getScaling().z / 2.0f);
			rt.x = (entity->getTranslation().x + entity->getScaling().x / 2.0f);
			rt.y = (entity->getTranslation().y + entity->getScaling().y);
			rt.z = (entity->getTranslation().z - entity->getScaling().z / 2.0f);

			// Calculate intersection & distance
			float distance = _core->_rayCaster.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition());
			bool result = (distance != -1.0f);

			// Return
			return make_pair(result, distance);
		}
	}
}

pair<const string, float> FabiEngine3D::collision_checkCursorInEntities(const string& ID, bool canBeOccluded, const string& exception)
{
	// Check whether the AABB can be raycasted if it's occluded by another AABB
	if (canBeOccluded)
	{
		// Check if raycasting needs to be updated
		if (!_isRaycastUpdated)
		{
			collision_checkCursorInAny();
		}

		// Check if hovered AABB is empty or nonexisting
		if (_hoveredAabbID.empty() || !_core->_aabbEntityManager.isExisting(_hoveredAabbID))
		{
			return make_pair("", -1.0f);
		}

		// Check if ID matches (a part of) hovered AABB ID
		if (_hoveredAabbID.size() >= ID.size())
		{
			auto subString = _hoveredAabbID.substr(0, ID.size());
			if (subString == ID && _hoveredAabbID != exception)
			{
				return make_pair(_hoveredAabbID, _hoveredAabbDistance);
			}
		}

		// ID not found
		return make_pair("", -1.0f);
	}
	else
	{
		// Temporary values
		float closestDistance = (std::numeric_limits<float>::max)();
		string closestBoxID = "";

		// Loop over AABB entities
		for (auto [keyID, entity] : _core->_aabbEntityManager.getEntities())
		{
			if (entity->isResponsive() && entity->isVisible())
			{
				if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
				{
					auto subString = entity->getID().substr(0, ID.size());
					if (subString == ID && entity->getID() != exception) // If entity matches ID
					{
						// Calculate box left bottom (LB) and right top (RT)
						Vec3 lb, rt;
						lb.x = (entity->getTranslation().x - entity->getScaling().x / 2.0f);
						lb.y = (entity->getTranslation().y);
						lb.z = (entity->getTranslation().z + entity->getScaling().z / 2.0f);
						rt.x = (entity->getTranslation().x + entity->getScaling().x / 2.0f);
						rt.y = (entity->getTranslation().y + entity->getScaling().y);
						rt.z = (entity->getTranslation().z - entity->getScaling().z / 2.0f);

						// Check intersection
						float distance = _core->_rayCaster.checkCursorInBox(lb, rt, _core->_cameraManager.getPosition());

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

		// Return
		if (closestBoxID.empty())
		{
			return make_pair("", -1.0f);
		}
		else
		{
			return make_pair(closestBoxID, closestDistance);
		}
	}
}

const string FabiEngine3D::collision_checkCameraWithAny()
{
	for (auto [keyID, entity] : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
	{
		if (entity->getCollisionDirection() != Direction::NONE)
		{
			return entity->getID();
		}
	}

	return "";
}

bool FabiEngine3D::collision_checkCameraWithTerrain()
{
	return _core->_collisionResolver.isCameraUnderTerrain();
}

bool FabiEngine3D::collision_checkCameraWithEntity(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection() != Direction::NONE;
}

const string FabiEngine3D::collision_checkEntityWithEntities(const string& selfID, const string& otherID)
{
	// Check if self entity does not exist
	if (!_core->_aabbEntityManager.isExisting(selfID))
	{
		return "";
	}

	// Temporary values
	auto self = _core->_aabbEntityManager.getEntity(selfID);
	Vec3 selfPos = self->getTranslation();
	Vec3 selfSize = self->getScaling() / 2.0f;

	// Check if self entity is responsive and visible
	if (!self->isResponsive() || !self->isVisible())
	{
		return "";
	}

	// Loop over AABB entities
	for (auto [keyID, other] : _core->_aabbEntityManager.getEntities())
	{
		if (other->getID().size() >= otherID.size()) // Check if entity ID is at least the size of group ID
		{
			// Check if entity does not match ID
			auto subString = other->getID().substr(0, otherID.size());
			if (subString != otherID)
			{
				continue;
			}

			// Don't check own entity AABB('s)
			if (other->getParentID() == self->getParentID())
			{
				continue;
			}

			// Other entity must be responsive and visible
			if (!other->isResponsive() || !other->isVisible())
			{
				continue;
			}

			// Temporary values
			Vec3 otherPos = other->getTranslation();
			Vec3 otherSize = other->getScaling() / 2.0f;
			// Check XYZ collision between 2 entities
			if
			(
				// Middle coordinate within
				((selfPos.x > otherPos.x - otherSize.x && selfPos.x < otherPos.x + otherSize.x) ||
				// Lower corner within
				(selfPos.x - selfSize.x > otherPos.x - otherSize.x && selfPos.x - selfSize.x < otherPos.x + otherSize.x) ||
				// Upper corner within 
				(selfPos.x + selfSize.x > otherPos.x - otherSize.x && selfPos.x + selfSize.x < otherPos.x + otherSize.x) ||
				// AABB too big but overlapping
				(selfPos.x - selfSize.x <= otherPos.x - otherSize.x && selfPos.x + selfSize.x >= otherPos.x + otherSize.x)) 

				&&

				// Middle coordinate within
				((selfPos.y + selfSize.y > otherPos.y && selfPos.y + selfSize.y < otherPos.y + (otherSize.y * 2.0f)) ||
				// Lower corner within
				(selfPos.y > otherPos.y && selfPos.y < otherPos.y + (otherSize.y * 2.0f)) ||
				// Upper corner within 
				(selfPos.y + (selfSize.y * 2.0f) > otherPos.y && selfPos.y + (selfSize.y * 2.0f) < otherPos.y + (otherSize.y * 2.0f)) ||
				// AABB too big but overlapping 
				(selfPos.y <= otherPos.y && selfPos.y + (selfSize.y * 2.0f) >= otherPos.y + (otherSize.y * 2.0f)))

				&&

				// Middle coordinate within
				((selfPos.z > otherPos.z - otherSize.z && selfPos.z < otherPos.z + otherSize.z) ||
				// Lower corner within
				(selfPos.z - selfSize.z > otherPos.z - otherSize.z && selfPos.z - selfSize.z < otherPos.z + otherSize.z) ||
				// Upper corner within 
				(selfPos.z + selfSize.z > otherPos.z - otherSize.z && selfPos.z + selfSize.z < otherPos.z + otherSize.z) || 
				// AABB too big but overlapping 
				(selfPos.z - selfSize.z <= otherPos.z - otherSize.z && selfPos.z + selfSize.z >= otherPos.z + otherSize.z))   
			)
			{
				return other->getID();
			}
		}
	}

	return "";
}

const string FabiEngine3D::collision_checkCameraWithEntities(const string& ID)
{
	for (auto [keyID, entity] : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
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

bool FabiEngine3D::collision_checkCameraWithEntityDirection(const string& ID, Direction direction)
{
	return (direction == _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection());
}

bool FabiEngine3D::collision_checkCameraWithAnyDirection(Direction direction)
{
	for (auto [keyID, entity] : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
	{
		if (direction == entity->getCollisionDirection())
		{
			return true;
		}
	}

	return false;
}

bool FabiEngine3D::collision_checkCameraWithEntitiesDirection(const string& ID, Direction direction)
{
	for (auto [keyID, entity] : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
	{
		if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());
			if (subString == ID) // If entity matches ID
			{
				// Return direction if collides
				if (direction == entity->getCollisionDirection())
				{
					return true;
				}
			}
		}
	}

	// No collision
	return false;
}