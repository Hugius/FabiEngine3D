#include "fe3d.hpp"
#include "core_engine.hpp"

const string FabiEngine3D::collision_checkCameraWithAny() const
{
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities()) // Iterate through AABB entities
	{
		// Check if collided
		if(entity->hasCollided())
		{
			return entity->getID();
		}
	}

	return "";
}

const bool FabiEngine3D::collision_checkCameraWithTerrain() const
{
	return _core->_cameraCollisionHandler.isCameraUnderTerrain();
}

const bool FabiEngine3D::collision_checkCameraWithEntity(const string& ID) const
{
	return _core->_aabbEntityManager.getEntity(ID)->hasCollided();
}

const string FabiEngine3D::collision_checkEntityWithEntities(const string& selfID, const string& otherID) const
{
	// Check if self entity does not exist
	if(!_core->_aabbEntityManager.isExisting(selfID))
	{
		return "";
	}

	// Temporary values
	auto self = _core->_aabbEntityManager.getEntity(selfID);
	fvec3 selfPosition = self->getPosition();
	fvec3 selfSize = self->getSize() / 2.0f;

	// Check if self entity is responsive and visible
	if(!self->isCollisionResponsive() || !self->isVisible())
	{
		return "";
	}

	// Iterate through AABB entities
	for(const auto& [keyID, other] : _core->_aabbEntityManager.getEntities())
	{
		if(other->getID().size() >= otherID.size()) // Check if entity ID is at least the size of group ID
		{
			// Check if entity does not match ID
			if(other->getID().substr(0, otherID.size()) != otherID)
			{
				continue;
			}

			// Do not check own entity AABBs
			if(other->getParentEntityID() == self->getParentEntityID())
			{
				continue;
			}

			// Other entity must be responsive and visible
			if(!other->isCollisionResponsive() || !other->isVisible())
			{
				continue;
			}

			// Temporary values
			fvec3 otherPosition = other->getPosition();
			fvec3 otherSize = other->getSize() / 2.0f;
			// Check XYZ collision between 2 entities
			if
				(
				// Middle coordinate within
				((selfPosition.x > otherPosition.x - otherSize.x && selfPosition.x < otherPosition.x + otherSize.x) ||
				// Lower corner within
				(selfPosition.x - selfSize.x > otherPosition.x - otherSize.x && selfPosition.x - selfSize.x < otherPosition.x + otherSize.x) ||
				// Upper corner within 
				(selfPosition.x + selfSize.x > otherPosition.x - otherSize.x && selfPosition.x + selfSize.x < otherPosition.x + otherSize.x) ||
				// AABB too big but overlapping
				(selfPosition.x - selfSize.x <= otherPosition.x - otherSize.x && selfPosition.x + selfSize.x >= otherPosition.x + otherSize.x))

				&&

				// Middle coordinate within
				((selfPosition.y + selfSize.y > otherPosition.y && selfPosition.y + selfSize.y < otherPosition.y + (otherSize.y * 2.0f)) ||
				// Lower corner within
				(selfPosition.y > otherPosition.y && selfPosition.y < otherPosition.y + (otherSize.y * 2.0f)) ||
				// Upper corner within 
				(selfPosition.y + (selfSize.y * 2.0f) > otherPosition.y && selfPosition.y + (selfSize.y * 2.0f) < otherPosition.y + (otherSize.y * 2.0f)) ||
				// AABB too big but overlapping 
				(selfPosition.y <= otherPosition.y && selfPosition.y + (selfSize.y * 2.0f) >= otherPosition.y + (otherSize.y * 2.0f)))

				&&

				// Middle coordinate within
				((selfPosition.z > otherPosition.z - otherSize.z && selfPosition.z < otherPosition.z + otherSize.z) ||
				// Lower corner within
				(selfPosition.z - selfSize.z > otherPosition.z - otherSize.z && selfPosition.z - selfSize.z < otherPosition.z + otherSize.z) ||
				// Upper corner within 
				(selfPosition.z + selfSize.z > otherPosition.z - otherSize.z && selfPosition.z + selfSize.z < otherPosition.z + otherSize.z) ||
				// AABB too big but overlapping 
				(selfPosition.z - selfSize.z <= otherPosition.z - otherSize.z && selfPosition.z + selfSize.z >= otherPosition.z + otherSize.z))
				)
			{
				return other->getID();
			}
		}
	}

	return "";
}

const string FabiEngine3D::collision_checkCameraWithEntities(const string& ID) const
{
	// Iterate through AABB entities
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if collided
		if(entity->hasCollided())
		{
			// Check if entity ID is at least the size of group ID
			if(entity->getID().size() >= ID.size())
			{
				// Check if entity matches ID
				if(entity->getID().substr(0, ID.size()) == ID)
				{
					return entity->getID();
				}
			}
		}
	}

	// No collision
	return "";
}

const bool FabiEngine3D::collision_checkCameraWithEntityDirection(const string& ID, Direction direction) const
{
	// Check if collided
	if(_core->_aabbEntityManager.getEntity(ID)->hasCollided())
	{
		// Check if direction is the same
		if(direction == _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection())
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::collision_checkCameraWithAnyDirection(Direction direction) const
{
	// Iterate through AABB entities
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if collided
		if(entity->hasCollided())
		{
			// Check if direction is the same
			if(direction == entity->getCollisionDirection())
			{
				return true;
			}
		}
	}

	return false;
}

const bool FabiEngine3D::collision_checkCameraWithEntitiesDirection(const string& ID, Direction direction) const
{
	// Iterate through AABB entities
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if collided
		if(entity->hasCollided())
		{
			// Check if direction is the same
			if(direction == entity->getCollisionDirection())
			{
				// Check if entity ID is at least the size of group ID
				if(entity->getID().size() >= ID.size())
				{
					// If entity matches ID
					if(entity->getID().substr(0, ID.size()) == ID)
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

const bool FabiEngine3D::collision_isCameraResponseEnabled() const
{
	return _core->_cameraCollisionHandler.isCameraAabbResponseEnabled();
}

const bool FabiEngine3D::collision_isTerrainResponseEnabled() const
{
	return _core->_cameraCollisionHandler.isCameraTerrainResponseEnabled();
}