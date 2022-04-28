#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::raycast_setTerrainIntersectionEnabled(bool value)
{
	_core->getRaycastIntersector()->setTerrainIntersectionEnabled(value);
}

void EngineInterface::raycast_setTerrainIntersectionDistance(float value)
{
	_core->getRaycastIntersector()->setTerrainIntersectionDistance(value);
}

void EngineInterface::raycast_setTerrainIntersectionPrecision(float value)
{
	_core->getRaycastIntersector()->setTerrainIntersectionPrecision(value);
}

void EngineInterface::raycast_setAabbIntersectionEnabled(bool value)
{
	_core->getRaycastIntersector()->setAabbIntersectionEnabled(value);
}

const string & EngineInterface::raycast_getClosestAabbId() const
{
	return _core->getRaycastIntersector()->getClosestAabbId();
}

const fvec3 & EngineInterface::raycast_getCursorRayPosition() const
{
	return _core->getRaycastCalculator()->getCursorRay()->getPosition();
}

const fvec3 & EngineInterface::raycast_getPointOnTerrain() const
{
	return _core->getRaycastIntersector()->getPointOnTerrain();
}

const fvec3 & EngineInterface::raycast_getCursorRayDirection() const
{
	return _core->getRaycastCalculator()->getCursorRay()->getDirection();
}

const float EngineInterface::raycast_getTerrainIntersectionDistance() const
{
	return _core->getRaycastIntersector()->getTerrainIntersectionDistance();
}

const float EngineInterface::raycast_getTerrainIntersectionPrecision() const
{
	return _core->getRaycastIntersector()->getTerrainIntersectionPrecision();
}

const float EngineInterface::raycast_getDistanceToTerrain()
{
	return _core->getRaycastIntersector()->getDistanceToTerrain();
}

const float EngineInterface::raycast_getDistanceToAabb(const string & aabbId)
{
	return _core->getRaycastIntersector()->getDistanceToAabb(aabbId);
}

const bool EngineInterface::raycast_isPointOnTerrainValid() const
{
	return (_core->getRaycastIntersector()->getPointOnTerrain() != fvec3(-1.0f));
}

const bool EngineInterface::raycast_isTerrainIntersectionEnabled() const
{
	return _core->getRaycastIntersector()->isTerrainIntersectionEnabled();
}

const bool EngineInterface::raycast_isAabbIntersectionEnabled() const
{
	return _core->getRaycastIntersector()->isAabbIntersectionEnabled();
}