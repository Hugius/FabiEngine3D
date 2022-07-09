#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::collision_setCameraBox(float left, float right, float bottom, float top, float back, float front)
{
	_core->getCameraCollisionHandler()->setCameraBox(make_shared<Box>(left, right, bottom, top, back, front));
}

void EngineInterface::collision_setCameraAabbResponseEnabled(bool x, bool y, bool z)
{
	_core->getCameraCollisionHandler()->setCameraAabbResponseEnabled(x, y, z);
}

void EngineInterface::collision_setCameraTerrainResponseEnabled(bool value)
{
	_core->getCameraCollisionHandler()->setCameraTerrainResponseEnabled(value);
}

void EngineInterface::collision_setCameraTerrainResponseHeight(float value)
{
	_core->getCameraCollisionHandler()->setCameraTerrainResponseHeight(value);
}

void EngineInterface::collision_setCameraTerrainResponseSpeed(float value)
{
	_core->getCameraCollisionHandler()->setCameraTerrainResponseSpeed(value);
}

const vector<string> EngineInterface::collision_checkCameraWithAabbs() const
{
	vector<string> result = {};

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(aabb->hasCollided())
		{
			result.push_back(aabb->getId());
		}
	}

	return result;
}

const vector<string> EngineInterface::collision_checkCameraWithAabbs(DirectionType direction) const
{
	vector<string> result = {};

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(aabb->hasCollided())
		{
			if(direction == aabb->getCollisionDirection())
			{
				result.push_back(aabb->getId());
			}
		}
	}

	return result;
}

const bool EngineInterface::collision_checkCameraWithTerrain() const
{
	return _core->getCameraCollisionHandler()->isCameraUnderTerrain();
}

const bool EngineInterface::collision_checkCameraWithAabb(const string & aabbId) const
{
	return _core->getAabbManager()->getAabb(aabbId)->hasCollided();
}

const float EngineInterface::collision_getCameraTerrainResponseHeight() const
{
	return _core->getCameraCollisionHandler()->getCameraTerrainResponseHeight();
}

const float EngineInterface::collision_getCameraTerrainResponseSpeed() const
{
	return _core->getCameraCollisionHandler()->getCameraTerrainResponseSpeed();
}

const bool EngineInterface::collision_isCameraAabbResponseEnabledX() const
{
	return _core->getCameraCollisionHandler()->isCameraAabbResponseEnabledX();
}

const bool EngineInterface::collision_isCameraAabbResponseEnabledY() const
{
	return _core->getCameraCollisionHandler()->isCameraAabbResponseEnabledY();
}

const bool EngineInterface::collision_isCameraAabbResponseEnabledZ() const
{
	return _core->getCameraCollisionHandler()->isCameraAabbResponseEnabledZ();
}

const bool EngineInterface::collision_checkCameraWithAabb(const string & aabbId, DirectionType direction) const
{
	if(_core->getAabbManager()->getAabb(aabbId)->hasCollided())
	{
		if(direction == _core->getAabbManager()->getAabb(aabbId)->getCollisionDirection())
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::collision_checkAabbWithAabb(const string & firstAabbId, const string & secondAabbId) const
{
	return false;
}

const bool EngineInterface::collision_isCameraTerrainResponseEnabled() const
{
	return _core->getCameraCollisionHandler()->isCameraTerrainResponseEnabled();
}