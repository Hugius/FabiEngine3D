#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::collision_setCameraBoxSize(float bottom, float top, float left, float right, float front, float back)
{
	_core->_collisionResolver.setCameraBoxSize(bottom, top, left, right, front, back);
}

void FabiEngine3D::collision_enableCameraResponse(bool x, bool y, bool z)
{
	_core->_collisionResolver.enableCameraResponse(x, y, z);
}

void FabiEngine3D::collision_disableCameraResponse()
{
	_core->_collisionResolver.disableAabbResponse();
}

void FabiEngine3D::collision_enableTerrainResponse(float cameraHeight, float cameraSpeed)
{
	_core->_collisionResolver.enableTerrainResponse(cameraHeight, cameraSpeed);
}

void FabiEngine3D::collision_disableTerrainResponse()
{
	_core->_collisionResolver.disableTerrainResponse();
}

const string FabiEngine3D::collision_checkCameraWithAny()
{
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities()) // Iterate through AABB entities
	{
		// Check if collided
		if (entity->hasCollided())
		{
			return entity->getID();
		}
	}

	return "";
}

const bool FabiEngine3D::collision_checkCameraWithTerrain()
{
	return _core->_collisionResolver.isCameraUnderTerrain();
}

const bool FabiEngine3D::collision_checkCameraWithEntity(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->hasCollided();
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
	Vec3 selfPos = self->getPosition();
	Vec3 selfSize = self->getSize() / 2.0f;

	// Check if self entity is responsive and visible
	if (!self->isCollisionResponsive() || !self->isVisible())
	{
		return "";
	}

	// Iterate through AABB entities
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
			Vec3 otherPos = other->getPosition();
			Vec3 otherSize = other->getSize() / 2.0f;
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
	// Iterate through AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if collided
		if (entity->hasCollided())
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

const bool FabiEngine3D::collision_checkCameraWithEntityDirection(const string& ID, Direction direction)
{
	// Check if collided
	if (_core->_aabbEntityManager.getEntity(ID)->hasCollided())
	{
		// Check if direction is the same
		if (direction == _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection())
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::collision_checkCameraWithAnyDirection(Direction direction)
{
	// Iterate through AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if collided
		if (entity->hasCollided())
		{
			// Check if direction is the same
			if (direction == entity->getCollisionDirection())
			{
				return true;
			}
		}
	}

	return false;
}

const bool FabiEngine3D::collision_checkCameraWithEntitiesDirection(const string& ID, Direction direction)
{
	// Iterate through AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if collided
		if (entity->hasCollided())
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
	}

	// No collision
	return false;
}

const bool FabiEngine3D::collision_isCameraResponseEnabled()
{
	return _core->_collisionResolver.isCameraResponseEnabled();
}

const bool FabiEngine3D::collision_isTerrainResponseEnabled()
{
	return _core->_collisionResolver.isTerrainResponseEnabled();
}