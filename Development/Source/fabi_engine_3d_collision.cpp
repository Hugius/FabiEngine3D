#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

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
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if parent entity is not level of detailed
		if (!(entity->getParentType() == AabbParentType::MODEL_ENTITY &&
			_core->_modelEntityManager.getEntity(entity->getParentID())->isLevelOfDetailed()))
		{
			// Check if AABB is responsive
			if (entity->isRaycastResponsive() && entity->isVisible())
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

		if (entity->isRaycastResponsive() && entity->isVisible())
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

		// Check if hovered AABB is empty or non-existing
		if (_hoveredAabbID.empty() || !_core->_aabbEntityManager.isExisting(_hoveredAabbID))
		{
			return make_pair("", -1.0f);
		}

		// Check if ID matches (a part of) hovered AABB ID
		if (_hoveredAabbID.size() >= ID.size())
		{
			if (_hoveredAabbID.substr(0, ID.size()) == ID && _hoveredAabbID != exception)
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
		for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
		{
			if (entity->isRaycastResponsive() && entity->isVisible())
			{
				if (entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
				{
					if (entity->getID().substr(0, ID.size()) == ID && entity->getID() != exception) // If entity matches ID
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
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities()) // Loop over AABB entities
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
	if (!self->isCollisionResponsive() || !self->isVisible())
	{
		return "";
	}

	// Loop over AABB entities
	for (const auto& [keyID, other] : _core->_aabbEntityManager.getEntities())
	{
		if (other->getID().size() >= otherID.size()) // Check if entity ID is at least the size of group ID
		{
			// Check if entity does not match ID
			if (other->getID().substr(0, otherID.size()) != otherID)
			{
				continue;
			}

			// Don't check own entity AABB('s)
			if (other->getParentID() == self->getParentID())
			{
				continue;
			}

			// Other entity must be responsive and visible
			if (!other->isCollisionResponsive() || !other->isVisible())
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
	// Loop over AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if collided
		if (entity->getCollisionDirection() != Direction::NONE)
		{
			// Check if entity ID is at least the size of group ID
			if (entity->getID().size() >= ID.size())
			{
				// Check if entity matches ID
				if (entity->getID().substr(0, ID.size()) == ID)
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
	// Loop over AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
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
	// Loop over AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if direction is the same
		if (direction == entity->getCollisionDirection())
		{
			// Check if entity ID is at least the size of group ID
			if (entity->getID().size() >= ID.size())
			{
				// If entity matches ID
				if (entity->getID().substr(0, ID.size()) == ID)
				{
					return true;
				}
			}
		}
	}

	// No collision
	return false;
}