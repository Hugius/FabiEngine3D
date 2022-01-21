#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::pointlight_create(const string& ID)
{
	if(_core->getPointlightEntityManager()->getEntities().size() == PointlightEntityManager::MAX_LIGHT_COUNT)
	{
		Logger::throwWarning("Tried to create pointlight entity: maximum reached!");
		return;
	}

	_core->getPointlightEntityManager()->createEntity(ID);
}

void EngineInterface::pointlight_deleteAll()
{
	_core->getPointlightEntityManager()->deleteEntities();
}

void EngineInterface::pointlight_delete(const string& ID)
{
	_core->getPointlightEntityManager()->deleteEntity(ID);
}

void EngineInterface::pointlight_setVisible(const string& ID, bool value)
{
	_core->getPointlightEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::pointlight_setPosition(const string& ID, const fvec3& value)
{
	_core->getPointlightEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::pointlight_move(const string& ID, const fvec3& change)
{
	_core->getPointlightEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::pointlight_moveTo(const string& ID, const fvec3& target, float speed)
{
	_core->getPointlightEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::pointlight_setRadius(const string& ID, const fvec3& value)
{
	_core->getPointlightEntityManager()->getEntity(ID)->setRadius(value);
}

void EngineInterface::pointlight_setColor(const string& ID, const fvec3& value)
{
	_core->getPointlightEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::pointlight_setIntensity(const string& ID, float value)
{
	_core->getPointlightEntityManager()->getEntity(ID)->setIntensity(value);
}

void EngineInterface::pointlight_setShape(const string& ID, PointlightShape value)
{
	return _core->getPointlightEntityManager()->getEntity(ID)->setShape(value);
}

const bool EngineInterface::pointlight_isExisting(const string& ID) const
{
	return _core->getPointlightEntityManager()->isEntityExisting(ID);
}

const  bool EngineInterface::pointlight_isVisible(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->isVisible();
}

const PointlightShape EngineInterface::pointlight_getShape(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getShape();
}

const fvec3& EngineInterface::pointlight_getPosition(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getPosition();
}

const fvec3& EngineInterface::pointlight_getRadius(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getRadius();
}

const fvec3& EngineInterface::pointlight_getColor(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getColor();
}

const float EngineInterface::pointlight_getIntensity(const string& ID) const
{
	return _core->getPointlightEntityManager()->getEntity(ID)->getIntensity();
}

const vector<string> EngineInterface::pointlight_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getPointlightEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}