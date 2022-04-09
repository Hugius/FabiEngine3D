#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::pointlight_create(const string & id)
{
	_core->getPointlightEntityManager()->createEntity(id);
}

void EngineInterface::pointlight_delete(const string & id)
{
	_core->getPointlightEntityManager()->deleteEntity(id);
}

void EngineInterface::pointlight_setVisible(const string & id, bool value)
{
	_core->getPointlightEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::pointlight_setPosition(const string & id, const fvec3 & value)
{
	_core->getPointlightEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::pointlight_move(const string & id, const fvec3 & change)
{
	_core->getPointlightEntityManager()->getEntity(id)->move(change);
}

void EngineInterface::pointlight_moveTo(const string & id, const fvec3 & target, float speed)
{
	_core->getPointlightEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::pointlight_setRadius(const string & id, const fvec3 & value)
{
	_core->getPointlightEntityManager()->getEntity(id)->setRadius(value);
}

void EngineInterface::pointlight_setColor(const string & id, const fvec3 & value)
{
	_core->getPointlightEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::pointlight_setIntensity(const string & id, float value)
{
	_core->getPointlightEntityManager()->getEntity(id)->setIntensity(value);
}

void EngineInterface::pointlight_setShape(const string & id, PointlightShape value)
{
	return _core->getPointlightEntityManager()->getEntity(id)->setShape(value);
}

const bool EngineInterface::pointlight_isExisting(const string & id) const
{
	return _core->getPointlightEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::pointlight_isVisible(const string & id) const
{
	return _core->getPointlightEntityManager()->getEntity(id)->isVisible();
}

const PointlightShape EngineInterface::pointlight_getShape(const string & id) const
{
	return _core->getPointlightEntityManager()->getEntity(id)->getShape();
}

const fvec3 & EngineInterface::pointlight_getPosition(const string & id) const
{
	return _core->getPointlightEntityManager()->getEntity(id)->getPosition();
}

const fvec3 & EngineInterface::pointlight_getRadius(const string & id) const
{
	return _core->getPointlightEntityManager()->getEntity(id)->getRadius();
}

const fvec3 & EngineInterface::pointlight_getColor(const string & id) const
{
	return _core->getPointlightEntityManager()->getEntity(id)->getColor();
}

const float EngineInterface::pointlight_getIntensity(const string & id) const
{
	return _core->getPointlightEntityManager()->getEntity(id)->getIntensity();
}

const unsigned int EngineInterface::pointlight_getMaxEntityCount() const
{
	return _core->getPointlightEntityManager()->getMaxEntityCount();
}

const vector<string> EngineInterface::pointlight_getIds() const
{
	vector<string> result;

	for(const auto & [key, entity] : _core->getPointlightEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}