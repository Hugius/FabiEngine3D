#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::reflection_create(const string & id)
{
	_core->getReflectionEntityManager()->createEntity(id);
}

void EngineInterface::reflection_delete(const string & id)
{
	_core->getReflectionEntityManager()->deleteEntity(id);
}

void EngineInterface::reflection_setVisible(const string & id, bool value)
{
	_core->getReflectionEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::reflection_setPosition(const string & id, const fvec3 & value)
{
	_core->getReflectionEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::reflection_move(const string & id, const fvec3 & change)
{
	_core->getReflectionEntityManager()->getEntity(id)->move(change);
}

void EngineInterface::reflection_moveTo(const string & id, const fvec3 & target, float speed)
{
	_core->getReflectionEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::reflection_capture(const string & id)
{
	_core->getReflectionEntityManager()->getEntity(id)->capture();
}

void EngineInterface::reflection_setExceptionEntityId(const string & id, const string & value)
{
	_core->getReflectionEntityManager()->getEntity(id)->setExceptionEntityId(value);
}

const vector<string> EngineInterface::reflection_getIds() const
{
	vector<string> result;

	for(const auto & [key, entity] : _core->getReflectionEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const string & EngineInterface::reflection_getExceptionEntityId(const string & id) const
{
	return _core->getReflectionEntityManager()->getEntity(id)->getExceptionEntityId();
}

const fvec3 & EngineInterface::reflection_getPosition(const string & id) const
{
	return _core->getReflectionEntityManager()->getEntity(id)->getPosition();
}

const bool EngineInterface::reflection_isExisting(const string & id) const
{
	return _core->getReflectionEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::reflection_isVisible(const string & id) const
{
	return _core->getReflectionEntityManager()->getEntity(id)->isVisible();
}