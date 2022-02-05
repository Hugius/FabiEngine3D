#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::raycast_setTerrainPointingEnabled(bool value)
{
	_core->getRaycastIntersector()->setTerrainPointingEnabled(value);
}

void EngineInterface::raycast_setTerrainPointingDistance(float value)
{
	_core->getRaycastIntersector()->setTerrainPointingDistance(value);
}

void EngineInterface::raycast_setTerrainPointingPrecision(float value)
{
	_core->getRaycastIntersector()->setTerrainPointingPrecision(value);
}

const string& EngineInterface::raycast_getClosestAabbId() const
{
	return _core->getRaycastIntersector()->getClosestAabbId();
}

const fvec3& EngineInterface::raycast_getCursorRayPosition() const
{
	return _core->getRaycastCalculator()->getCursorRay()->getPosition();
}

const fvec3& EngineInterface::raycast_getPointOnTerrain() const
{
	return _core->getRaycastIntersector()->getTerrainPoint();
}

const fvec3& EngineInterface::raycast_getCursorRayDirection() const
{
	return _core->getRaycastCalculator()->getCursorRay()->getDirection();
}

const float EngineInterface::raycast_getTerrainPointingDistance() const
{
	return _core->getRaycastIntersector()->getTerrainPointingDistance();
}

const float EngineInterface::raycast_getTerrainPointingPrecision() const
{
	return _core->getRaycastIntersector()->getTerrainPointingPrecision();
}

const float EngineInterface::raycast_getDistanceToTerrain()
{
	return _core->getRaycastIntersector()->getDistanceToTerrain();
}

const float EngineInterface::raycast_getDistanceToAabb(const string& id)
{
	return _core->getRaycastIntersector()->getDistanceToAabb(id);
}

const bool EngineInterface::raycast_isPointOnTerrainValid() const
{
	return (_core->getRaycastIntersector()->getTerrainPoint() != fvec3(-1.0f));
}

const bool EngineInterface::raycast_isTerrainPointingEnabled() const
{
	return _core->getRaycastIntersector()->isTerrainPointingEnabled();
}