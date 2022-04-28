#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::collision_setCameraBox(float left, float right, float bottom, float top, float back, float front)
{
	_core->getCameraCollisionResponder()->setCameraBox(make_shared<Box>(left, right, bottom, top, back, front));
}

void EngineInterface::collision_setCameraAabbResponseEnabled(bool x, bool y, bool z)
{
	_core->getCameraCollisionResponder()->setCameraAabbResponseEnabled(x, y, z);
}

void EngineInterface::collision_setCameraTerrainResponseEnabled(bool value)
{
	_core->getCameraCollisionResponder()->setCameraTerrainResponseEnabled(value);
}

void EngineInterface::collision_setCameraTerrainResponseHeight(float value)
{
	_core->getCameraCollisionResponder()->setCameraTerrainResponseHeight(value);
}

void EngineInterface::collision_setCameraTerrainResponseSpeed(float value)
{
	_core->getCameraCollisionResponder()->setCameraTerrainResponseSpeed(value);
}

const vector<string> EngineInterface::collision_checkCameraWithAabbs() const
{
	vector<string> result;

	for(const auto & [aabbId, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasCollided())
		{
			result.push_back(entity->getId());
		}
	}

	return result;
}

const vector<string> EngineInterface::collision_checkCameraWithAabbs(DirectionType direction) const
{
	vector<string> result;

	for(const auto & [aabbId, entity] : _core->getAabbEntityManager()->getEntities())
	{
		if(entity->hasCollided())
		{
			if(direction == entity->getCollisionDirection())
			{
				result.push_back(entity->getId());
			}
		}
	}

	return result;
}

const bool EngineInterface::collision_checkCameraWithTerrain() const
{
	return _core->getCameraCollisionResponder()->isCameraUnderTerrain();
}

const bool EngineInterface::collision_checkCameraWithAabb(const string & aabbId) const
{
	return _core->getAabbEntityManager()->getEntity(aabbId)->hasCollided();
}

const float EngineInterface::collision_getCameraTerrainResponseHeight() const
{
	return _core->getCameraCollisionResponder()->getCameraTerrainResponseHeight();
}

const float EngineInterface::collision_getCameraTerrainResponseSpeed() const
{
	return _core->getCameraCollisionResponder()->getCameraTerrainResponseSpeed();
}

const bool EngineInterface::collision_isCameraAabbResponseEnabledX() const
{
	return _core->getCameraCollisionResponder()->isCameraAabbResponseEnabledX();
}

const bool EngineInterface::collision_isCameraAabbResponseEnabledY() const
{
	return _core->getCameraCollisionResponder()->isCameraAabbResponseEnabledY();
}

const bool EngineInterface::collision_isCameraAabbResponseEnabledZ() const
{
	return _core->getCameraCollisionResponder()->isCameraAabbResponseEnabledZ();
}

const bool EngineInterface::collision_checkCameraWithAabb(const string & aabbId, DirectionType direction) const
{
	if(_core->getAabbEntityManager()->getEntity(aabbId)->hasCollided())
	{
		if(direction == _core->getAabbEntityManager()->getEntity(aabbId)->getCollisionDirection())
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::collision_isCameraTerrainResponseEnabled() const
{
	return _core->getCameraCollisionResponder()->isCameraTerrainResponseEnabled();
}