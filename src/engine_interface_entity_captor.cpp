#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::captor_create(const string & id)
{
	_core->getCaptorEntityManager()->createEntity(id);
}

void EngineInterface::captor_delete(const string & id)
{
	_core->getCaptorEntityManager()->deleteEntity(id);
}

void EngineInterface::captor_setVisible(const string & id, bool value)
{
	_core->getCaptorEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::captor_setPosition(const string & id, const fvec3 & value)
{
	_core->getCaptorEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::captor_move(const string & id, const fvec3 & change)
{
	_core->getCaptorEntityManager()->getEntity(id)->move(change);
}

void EngineInterface::captor_moveTo(const string & id, const fvec3 & target, float speed)
{
	_core->getCaptorEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::captor_capture(const string & id)
{
	_core->getCaptorEntityManager()->getEntity(id)->capture();
}

void EngineInterface::captor_setExceptionEntityId(const string & id, const string & value)
{
	_core->getCaptorEntityManager()->getEntity(id)->setExceptionEntityId(value);
}

const vector<string> EngineInterface::captor_getIds() const
{
	vector<string> result;

	for(const auto & [entityId, entity] : _core->getCaptorEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const string & EngineInterface::captor_getExceptionEntityId(const string & id) const
{
	return _core->getCaptorEntityManager()->getEntity(id)->getExceptionEntityId();
}

const fvec3 & EngineInterface::captor_getPosition(const string & id) const
{
	return _core->getCaptorEntityManager()->getEntity(id)->getPosition();
}

const bool EngineInterface::captor_isExisting(const string & id) const
{
	return _core->getCaptorEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::captor_isVisible(const string & id) const
{
	return _core->getCaptorEntityManager()->getEntity(id)->isVisible();
}