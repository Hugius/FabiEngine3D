#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::pointlight_create(const string & pointlightId)
{
	_core->getPointlightManager()->createEntity(pointlightId);
}

void EngineInterface::pointlight_delete(const string & pointlightId)
{
	_core->getPointlightManager()->deleteEntity(pointlightId);
}

void EngineInterface::pointlight_setVisible(const string & pointlightId, bool value)
{
	_core->getPointlightManager()->getEntity(pointlightId)->setVisible(value);
}

void EngineInterface::pointlight_setPosition(const string & pointlightId, const fvec3 & value)
{
	_core->getPointlightManager()->getEntity(pointlightId)->setPosition(value);
}

void EngineInterface::pointlight_move(const string & pointlightId, const fvec3 & change)
{
	_core->getPointlightManager()->getEntity(pointlightId)->move(change);
}

void EngineInterface::pointlight_moveTo(const string & pointlightId, const fvec3 & target, float speed)
{
	_core->getPointlightManager()->getEntity(pointlightId)->moveTo(target, speed);
}

void EngineInterface::pointlight_setRadius(const string & pointlightId, const fvec3 & value)
{
	_core->getPointlightManager()->getEntity(pointlightId)->setRadius(value);
}

void EngineInterface::pointlight_setColor(const string & pointlightId, const fvec3 & value)
{
	_core->getPointlightManager()->getEntity(pointlightId)->setColor(value);
}

void EngineInterface::pointlight_setIntensity(const string & pointlightId, float value)
{
	_core->getPointlightManager()->getEntity(pointlightId)->setIntensity(value);
}

void EngineInterface::pointlight_setShape(const string & pointlightId, PointlightType value)
{
	return _core->getPointlightManager()->getEntity(pointlightId)->setShape(value);
}

const bool EngineInterface::pointlight_isExisting(const string & pointlightId) const
{
	return _core->getPointlightManager()->isEntityExisting(pointlightId);
}

const bool EngineInterface::pointlight_isVisible(const string & pointlightId) const
{
	return _core->getPointlightManager()->getEntity(pointlightId)->isVisible();
}

const PointlightType EngineInterface::pointlight_getShape(const string & pointlightId) const
{
	return _core->getPointlightManager()->getEntity(pointlightId)->getShape();
}

const fvec3 & EngineInterface::pointlight_getPosition(const string & pointlightId) const
{
	return _core->getPointlightManager()->getEntity(pointlightId)->getPosition();
}

const fvec3 & EngineInterface::pointlight_getRadius(const string & pointlightId) const
{
	return _core->getPointlightManager()->getEntity(pointlightId)->getRadius();
}

const fvec3 & EngineInterface::pointlight_getColor(const string & pointlightId) const
{
	return _core->getPointlightManager()->getEntity(pointlightId)->getColor();
}

const float EngineInterface::pointlight_getIntensity(const string & pointlightId) const
{
	return _core->getPointlightManager()->getEntity(pointlightId)->getIntensity();
}

const int EngineInterface::pointlight_getMaxEntityCount() const
{
	return _core->getPointlightManager()->getMaxEntityCount();
}

const vector<string> EngineInterface::pointlight_getIds() const
{
	vector<string> result;

	for(const auto & [pointlightId, pointlight] : _core->getPointlightManager()->getEntities())
	{
		result.push_back(pointlight->getId());
	}

	return result;
}