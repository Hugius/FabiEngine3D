#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::clock_create(const string& id)
{
	_core->getTimer()->createClock(id);
}

void EngineInterface::clock_delete(const string& id)
{
	_core->getTimer()->deleteClock(id);
}

void EngineInterface::clock_start(const string& id)
{
	_core->getTimer()->startClock(id);
}

void EngineInterface::clock_pause(const string& id)
{
	_core->getTimer()->pauseClock(id);
}

void EngineInterface::clock_resume(const string& id)
{
	_core->getTimer()->resumeClock(id);
}

void EngineInterface::clock_stop(const string& id)
{
	_core->getTimer()->stopClock(id);
}

const vector<string> EngineInterface::clock_getIds() const
{
	return _core->getTimer()->getClockIds();
}

const float EngineInterface::clock_getDeltaTime(const string& id) const
{
	return _core->getTimer()->getClockDeltaTime(id);
}

const bool EngineInterface::clock_isExisting(const string& id) const
{
	return _core->getTimer()->isClockExisting(id);
}

const bool EngineInterface::clock_isStarted(const string& id) const
{
	return _core->getTimer()->isClockStarted(id);
}

const bool EngineInterface::clock_isPaused(const string& id) const
{
	return _core->getTimer()->isClockPaused(id);
}