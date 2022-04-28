#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::captor_create(const string & captorId)
{
	_core->getCaptorEntityManager()->createEntity(captorId);
}

void EngineInterface::captor_delete(const string & captorId)
{
	_core->getCaptorEntityManager()->deleteEntity(captorId);
}

void EngineInterface::captor_setVisible(const string & captorId, bool value)
{
	_core->getCaptorEntityManager()->getEntity(captorId)->setVisible(value);
}

void EngineInterface::captor_setPosition(const string & captorId, const fvec3 & value)
{
	_core->getCaptorEntityManager()->getEntity(captorId)->setPosition(value);
}

void EngineInterface::captor_move(const string & captorId, const fvec3 & change)
{
	_core->getCaptorEntityManager()->getEntity(captorId)->move(change);
}

void EngineInterface::captor_moveTo(const string & captorId, const fvec3 & target, float speed)
{
	_core->getCaptorEntityManager()->getEntity(captorId)->moveTo(target, speed);
}

void EngineInterface::captor_capture(const string & captorId)
{
	_core->getCaptorEntityManager()->getEntity(captorId)->capture();
}

void EngineInterface::captor_setExceptionEntityId(const string & captorId, const string & value)
{
	_core->getCaptorEntityManager()->getEntity(captorId)->setExceptionEntityId(value);
}

const vector<string> EngineInterface::captor_getIds() const
{
	vector<string> result;

	for(const auto & [captorId, captor] : _core->getCaptorEntityManager()->getEntities())
	{
		result.push_back(captor->getId());
	}

	return result;
}

const string & EngineInterface::captor_getExceptionEntityId(const string & captorId) const
{
	return _core->getCaptorEntityManager()->getEntity(captorId)->getExceptionEntityId();
}

const fvec3 & EngineInterface::captor_getPosition(const string & captorId) const
{
	return _core->getCaptorEntityManager()->getEntity(captorId)->getPosition();
}

const bool EngineInterface::captor_isExisting(const string & captorId) const
{
	return _core->getCaptorEntityManager()->isEntityExisting(captorId);
}

const bool EngineInterface::captor_isVisible(const string & captorId) const
{
	return _core->getCaptorEntityManager()->getEntity(captorId)->isVisible();
}