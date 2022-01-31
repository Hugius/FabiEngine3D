#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::collision_setCameraBox(float left, float right, float bottom, float top, float back, float front)
{
	_core->getCameraCollisionHandler()->setCameraBox(Box(left, right, bottom, top, back, front));
}

void EngineInterface::collision_enableCameraAabbResponse(bool x, bool y, bool z)
{
	_core->getCameraCollisionHandler()->enableCameraAabbResponse(x, y, z);
}

void EngineInterface::collision_disableCameraAabbResponse()
{
	_core->getCameraCollisionHandler()->disableCameraAabbResponse();
}

void EngineInterface::collision_enableCameraTerrainResponse(float cameraHeight, float cameraSpeed)
{
	_core->getCameraCollisionHandler()->enableCameraTerrainResponse(cameraHeight, cameraSpeed);
}

void EngineInterface::collision_disableCameraTerrainResponse()
{
	_core->getCameraCollisionHandler()->disableCameraTerrainResponse();
}

const string EngineInterface::collision_checkCameraWithAny() const
{
	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasCollided())
		{
			return entity->getId();
		}
	}

	return "";
}

const bool EngineInterface::collision_checkCameraWithTerrain() const
{
	return _core->getCameraCollisionHandler()->isCameraUnderTerrain();
}

const bool EngineInterface::collision_checkCameraWithEntity(const string& id) const
{
	return _core->getAabbEntityManager()->getEntity(id)->hasCollided();
}

const string EngineInterface::collision_checkEntityWithEntities(const string& selfId, const string& otherId) const
{
	if(!_core->getAabbEntityManager()->isEntityExisting(selfId))
	{
		return "";
	}

	auto self = _core->getAabbEntityManager()->getEntity(selfId);
	fvec3 selfPosition = self->getPosition();
	fvec3 selfSize = self->getSize() * 0.5f;

	if(!self->isCollisionResponsive())
	{
		return "";
	}

	for(const auto& [key, other] : _core->getAabbEntityManager()->getEntities())
	{
		if(other->getId().substr(0, otherId.size()) != otherId)
		{
			continue;
		}

		if(other->getParentEntityId() == self->getParentEntityId())
		{
			continue;
		}

		if(!other->isCollisionResponsive())
		{
			continue;
		}

		fvec3 otherPosition = other->getPosition();
		fvec3 otherSize = other->getSize() * 0.5f;
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
			return other->getId();
		}
	}

	return "";
}

const string EngineInterface::collision_checkCameraWithEntities(const string& id) const
{
	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasCollided())
		{
			if(entity->getId().substr(0, id.size()) == id)
			{
				return entity->getId();
			}
		}
	}

	return "";
}

const bool EngineInterface::collision_checkCameraWithEntityDirection(const string& id, Direction direction) const
{
	if(_core->getAabbEntityManager()->getEntity(id)->hasCollided())
	{
		if(direction == _core->getAabbEntityManager()->getEntity(id)->getCollisionDirection())
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::collision_checkCameraWithAnyDirection(Direction direction) const
{
	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
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

const bool EngineInterface::collision_checkCameraWithEntitiesDirection(const string& id, Direction direction) const
{
	for(const auto& [key, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasCollided())
		{
			if(direction == entity->getCollisionDirection())
			{
				if(entity->getId().substr(0, id.size()) == id)
				{
					return true;
				}
			}
		}
	}

	return false;
}

const bool EngineInterface::collision_isCameraResponseEnabled() const
{
	return _core->getCameraCollisionHandler()->isCameraAabbResponseEnabled();
}

const bool EngineInterface::collision_isTerrainResponseEnabled() const
{
	return _core->getCameraCollisionHandler()->isCameraTerrainResponseEnabled();
}