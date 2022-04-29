#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::captor_create(const string & captorId)
{
	_core->getCaptorManager()->createCaptor(captorId);
}

void EngineInterface::captor_delete(const string & captorId)
{
	_core->getCaptorManager()->deleteCaptor(captorId);
}

void EngineInterface::captor_setVisible(const string & captorId, bool value)
{
	_core->getCaptorManager()->getCaptor(captorId)->setVisible(value);
}

void EngineInterface::captor_setPosition(const string & captorId, const fvec3 & value)
{
	_core->getCaptorManager()->getCaptor(captorId)->setPosition(value);
}

void EngineInterface::captor_move(const string & captorId, const fvec3 & change)
{
	_core->getCaptorManager()->getCaptor(captorId)->move(change);
}

void EngineInterface::captor_moveTo(const string & captorId, const fvec3 & target, float speed)
{
	_core->getCaptorManager()->getCaptor(captorId)->moveTo(target, speed);
}

void EngineInterface::captor_capture(const string & captorId)
{
	_core->getCaptorManager()->getCaptor(captorId)->capture();
}

void EngineInterface::captor_setExceptionId(const string & captorId, const string & value)
{
	_core->getCaptorManager()->getCaptor(captorId)->setExceptionId(value);
}

const vector<string> EngineInterface::captor_getIds() const
{
	vector<string> result;

	for(const auto & [captorId, captor] : _core->getCaptorManager()->getCaptors())
	{
		result.push_back(captor->getId());
	}

	return result;
}

const string & EngineInterface::captor_getExceptionId(const string & captorId) const
{
	return _core->getCaptorManager()->getCaptor(captorId)->getExceptionId();
}

const fvec3 & EngineInterface::captor_getPosition(const string & captorId) const
{
	return _core->getCaptorManager()->getCaptor(captorId)->getPosition();
}

const bool EngineInterface::captor_isExisting(const string & captorId) const
{
	return _core->getCaptorManager()->isCaptorExisting(captorId);
}

const bool EngineInterface::captor_isVisible(const string & captorId) const
{
	return _core->getCaptorManager()->getCaptor(captorId)->isVisible();
}