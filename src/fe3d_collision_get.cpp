#include "fe3d.hpp"
#include "core.hpp"

const string FabiEngine3D::collision_checkCameraWithAny() const
{
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
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
	if(!_core->_aabbEntityManager.isEntityExisting(selfID))
	{
		return "";
	}

	auto self = _core->_aabbEntityManager.getEntity(selfID);
	fvec3 selfPosition = self->getPosition();
	fvec3 selfSize = self->getSize() / 2.0f;

	if(!self->isCollisionResponsive() || !self->isVisible())
	{
		return "";
	}

	for(const auto& [keyID, other] : _core->_aabbEntityManager.getEntities())
	{
		if(other->getID().size() >= otherID.size())
		{
			if(other->getID().substr(0, otherID.size()) != otherID)
			{
				continue;
			}

			if(other->getParentEntityID() == self->getParentEntityID())
			{
				continue;
			}

			if(!other->isCollisionResponsive() || !other->isVisible())
			{
				continue;
			}

			fvec3 otherPosition = other->getPosition();
			fvec3 otherSize = other->getSize() / 2.0f;
			if
				(
				((selfPosition.x > otherPosition.x - otherSize.x && selfPosition.x < otherPosition.x + otherSize.x) ||
				(selfPosition.x - selfSize.x > otherPosition.x - otherSize.x && selfPosition.x - selfSize.x < otherPosition.x + otherSize.x) ||
				(selfPosition.x + selfSize.x > otherPosition.x - otherSize.x && selfPosition.x + selfSize.x < otherPosition.x + otherSize.x) ||
				(selfPosition.x - selfSize.x <= otherPosition.x - otherSize.x && selfPosition.x + selfSize.x >= otherPosition.x + otherSize.x))

				&&

				((selfPosition.y + selfSize.y > otherPosition.y && selfPosition.y + selfSize.y < otherPosition.y + (otherSize.y * 2.0f)) ||
				(selfPosition.y > otherPosition.y && selfPosition.y < otherPosition.y + (otherSize.y * 2.0f)) ||
				(selfPosition.y + (selfSize.y * 2.0f) > otherPosition.y && selfPosition.y + (selfSize.y * 2.0f) < otherPosition.y + (otherSize.y * 2.0f)) ||
				(selfPosition.y <= otherPosition.y && selfPosition.y + (selfSize.y * 2.0f) >= otherPosition.y + (otherSize.y * 2.0f)))

				&&

				((selfPosition.z > otherPosition.z - otherSize.z && selfPosition.z < otherPosition.z + otherSize.z) ||
				(selfPosition.z - selfSize.z > otherPosition.z - otherSize.z && selfPosition.z - selfSize.z < otherPosition.z + otherSize.z) ||
				(selfPosition.z + selfSize.z > otherPosition.z - otherSize.z && selfPosition.z + selfSize.z < otherPosition.z + otherSize.z) ||
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
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		if(entity->hasCollided())
		{
			if(entity->getID().size() >= ID.size())
			{
				if(entity->getID().substr(0, ID.size()) == ID)
				{
					return entity->getID();
				}
			}
		}
	}

	return "";
}

const bool FabiEngine3D::collision_checkCameraWithEntityDirection(const string& ID, Direction direction) const
{
	if(_core->_aabbEntityManager.getEntity(ID)->hasCollided())
	{
		if(direction == _core->_aabbEntityManager.getEntity(ID)->getCollisionDirection())
		{
			return true;
		}
	}

	return false;
}

const bool FabiEngine3D::collision_checkCameraWithAnyDirection(Direction direction) const
{
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		if(entity->hasCollided())
		{
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
	for(const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		if(entity->hasCollided())
		{
			if(direction == entity->getCollisionDirection())
			{
				if(entity->getID().size() >= ID.size())
				{
					if(entity->getID().substr(0, ID.size()) == ID)
					{
						return true;
					}
				}
			}
		}
	}

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