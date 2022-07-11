#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::collision_setCameraBox(float left, float right, float bottom, float top, float back, float front)
{
	_core->getCameraCollisionHandler()->setCameraBox(make_shared<Box>(left, right, bottom, top, back, front));
}

void EngineInterface::collision_setCameraTerrainResponseHeight(float value)
{
	_core->getCameraCollisionHandler()->setCameraTerrainResponseHeight(value);
}

void EngineInterface::collision_setCameraTerrainResponseSpeed(float value)
{
	_core->getCameraCollisionHandler()->setCameraTerrainResponseSpeed(value);
}

void EngineInterface::collision_calculateCameraWithTerrain(bool mustRespondY)
{
	_core->getCameraCollisionHandler()->calculateTerrainCollision(mustRespondY);
}

void EngineInterface::collision_calculateCameraWithAabb(bool mustRespondX, bool mustRespondY, bool mustRespondZ)
{
	_core->getCameraCollisionHandler()->calculateAabbCollision(mustRespondX, mustRespondY, mustRespondZ);
}

const vector<string> EngineInterface::collision_checkCameraWithAabbs() const
{
	vector<string> result = {};

	for(const auto & [aabbId, aabb] : _core->getAabbManager()->getAabbs())
	{
		if(_core->getCameraCollisionHandler()->getAabbCollision(aabbId).first)
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
		const auto collision = _core->getCameraCollisionHandler()->getAabbCollision(aabbId);

		if(collision.first && (direction == collision.second))
		{
			result.push_back(aabb->getId());
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
	return _core->getCameraCollisionHandler()->getAabbCollision(aabbId).first;
}

const float EngineInterface::collision_getCameraTerrainResponseHeight() const
{
	return _core->getCameraCollisionHandler()->getCameraTerrainResponseHeight();
}

const float EngineInterface::collision_getCameraTerrainResponseSpeed() const
{
	return _core->getCameraCollisionHandler()->getCameraTerrainResponseSpeed();
}

const bool EngineInterface::collision_checkCameraWithAabb(const string & aabbId, DirectionType direction) const
{
	const auto collision = _core->getCameraCollisionHandler()->getAabbCollision(aabbId);

	return (collision.first && (direction == collision.second));
}