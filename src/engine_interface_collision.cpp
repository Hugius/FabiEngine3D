#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::collision_setCameraBox(float left, float right, float bottom, float top, float back, float front)
{
	_core->getCameraCollisionHandler()->setCameraBox(make_shared<Box>(left, right, bottom, top, back, front));
}

void EngineInterface::collision_calculateCameraWithTerrain(bool mustRespondY, float responseSpeed)
{
	_core->getCameraCollisionHandler()->calculateCollisionWithTerrain(mustRespondY, responseSpeed);
}

void EngineInterface::collision_calculateCameraWithAabbs(bool mustRespondX, bool mustRespondY, bool mustRespondZ)
{
	_core->getCameraCollisionHandler()->calculateCollisionWithAabbs(mustRespondX, mustRespondY, mustRespondZ);
}

void EngineInterface::collision_calculateAabbWithAabbs(const string & aabbId)
{
	_core->getAabbCollisionHandler()->calculateCollisionWithAabbs(aabbId);
}

void EngineInterface::collision_clearCameraWithTerrain()
{
	_core->getCameraCollisionHandler()->clearCollisionWithTerrain();
}

void EngineInterface::collision_clearCameraWithAabbs()
{
	_core->getCameraCollisionHandler()->clearCollisionWithAabbs();
}

void EngineInterface::collision_clearAabbWithAabbs()
{
	_core->getAabbCollisionHandler()->clearCollisionWithAabbs();
}

void EngineInterface::collision_clearAabbWithAabbs(const string & aabbId)
{
	_core->getAabbCollisionHandler()->clearCollisionWithAabbs(aabbId);
}

const vector<string> EngineInterface::collision_checkCameraWithAabbs() const
{
	vector<string> result = {};

	for(const auto & [collidedAabbId, collidedDirection] : _core->getCameraCollisionHandler()->getAabbCollisions())
	{
		result.push_back(collidedAabbId);
	}

	return result;
}

const vector<string> EngineInterface::collision_checkCameraWithAabbs(DirectionType direction) const
{
	vector<string> result = {};

	for(const auto & [collidedAabbId, collidedDirection] : _core->getCameraCollisionHandler()->getAabbCollisions())
	{
		if(direction == collidedDirection)
		{
			result.push_back(collidedAabbId);
		}
	}

	return result;
}

const vector<string> EngineInterface::collision_checkAabbWithAabbs(const string & aabbId) const
{
	return _core->getAabbCollisionHandler()->getAabbCollisions(aabbId);
}

const bool EngineInterface::collision_checkCameraWithTerrain() const
{
	return _core->getCameraCollisionHandler()->isCameraUnderTerrain();
}

const bool EngineInterface::collision_checkCameraWithAabb(const string & aabbId) const
{
	for(const auto & [collidedAabbId, direction] : _core->getCameraCollisionHandler()->getAabbCollisions())
	{
		if(aabbId == collidedAabbId)
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::collision_checkCameraWithAabb(const string & aabbId, DirectionType direction) const
{
	for(const auto & [collidedAabbId, collidedDirection] : _core->getCameraCollisionHandler()->getAabbCollisions())
	{
		if((aabbId == collidedAabbId) && (direction == collidedDirection))
		{
			return true;
		}
	}

	return false;
}

const bool EngineInterface::collision_checkAabbWithAabb(const string & firstAabbId, const string & secondAabbId) const
{
	for(const auto & collidedAabbId : _core->getAabbCollisionHandler()->getAabbCollisions(firstAabbId))
	{
		if(secondAabbId == collidedAabbId)
		{
			return true;
		}
	}

	return false;
}