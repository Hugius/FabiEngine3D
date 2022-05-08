#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::pointlight_create(const string & pointlightId)
{
	_core->getPointlightManager()->createPointlight(pointlightId);
}

void EngineInterface::pointlight_delete(const string & pointlightId)
{
	_core->getPointlightManager()->deletePointlight(pointlightId);
}

void EngineInterface::pointlight_setVisible(const string & pointlightId, bool value)
{
	_core->getPointlightManager()->getPointlight(pointlightId)->setVisible(value);
}

void EngineInterface::pointlight_setPosition(const string & pointlightId, const fvec3 & value)
{
	_core->getPointlightManager()->getPointlight(pointlightId)->setPosition(value);
}

void EngineInterface::pointlight_move(const string & pointlightId, const fvec3 & change)
{
	_core->getPointlightManager()->getPointlight(pointlightId)->move(change);
}

void EngineInterface::pointlight_moveTo(const string & pointlightId, const fvec3 & target, float speed)
{
	_core->getPointlightManager()->getPointlight(pointlightId)->moveTo(target, speed);
}

void EngineInterface::pointlight_setRadius(const string & pointlightId, const fvec3 & value)
{
	_core->getPointlightManager()->getPointlight(pointlightId)->setRadius(value);
}

void EngineInterface::pointlight_setColor(const string & pointlightId, const fvec3 & value)
{
	_core->getPointlightManager()->getPointlight(pointlightId)->setColor(value);
}

void EngineInterface::pointlight_setIntensity(const string & pointlightId, float value)
{
	_core->getPointlightManager()->getPointlight(pointlightId)->setIntensity(value);
}

void EngineInterface::pointlight_setShape(const string & pointlightId, PointlightShapeType value)
{
	return _core->getPointlightManager()->getPointlight(pointlightId)->setShape(value);
}

const bool EngineInterface::pointlight_isExisting(const string & pointlightId) const
{
	return _core->getPointlightManager()->isPointlightExisting(pointlightId);
}

const bool EngineInterface::pointlight_isVisible(const string & pointlightId) const
{
	return _core->getPointlightManager()->getPointlight(pointlightId)->isVisible();
}

const PointlightShapeType EngineInterface::pointlight_getShape(const string & pointlightId) const
{
	return _core->getPointlightManager()->getPointlight(pointlightId)->getShape();
}

const fvec3 & EngineInterface::pointlight_getPosition(const string & pointlightId) const
{
	return _core->getPointlightManager()->getPointlight(pointlightId)->getPosition();
}

const fvec3 & EngineInterface::pointlight_getRadius(const string & pointlightId) const
{
	return _core->getPointlightManager()->getPointlight(pointlightId)->getRadius();
}

const fvec3 & EngineInterface::pointlight_getColor(const string & pointlightId) const
{
	return _core->getPointlightManager()->getPointlight(pointlightId)->getColor();
}

const float EngineInterface::pointlight_getIntensity(const string & pointlightId) const
{
	return _core->getPointlightManager()->getPointlight(pointlightId)->getIntensity();
}

const int EngineInterface::pointlight_getMaxCount() const
{
	return _core->getPointlightManager()->getMaxCount();
}

const vector<string> EngineInterface::pointlight_getIds() const
{
	vector<string> result;

	for(const auto & [pointlightId, pointlight] : _core->getPointlightManager()->getPointlights())
	{
		result.push_back(pointlight->getId());
	}

	return result;
}