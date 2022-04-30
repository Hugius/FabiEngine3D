#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::clock_create(const string & clockId)
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	_core->getTimer()->createClock(clockId);
}

void EngineInterface::clock_delete(const string & clockId)
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	_core->getTimer()->deleteClock(clockId);
}

void EngineInterface::clock_start(const string & clockId)
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	_core->getTimer()->startClock(clockId);
}

void EngineInterface::clock_pause(const string & clockId)
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	_core->getTimer()->pauseClock(clockId);
}

void EngineInterface::clock_resume(const string & clockId)
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	_core->getTimer()->resumeClock(clockId);
}

void EngineInterface::clock_stop(const string & clockId)
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	_core->getTimer()->stopClock(clockId);
}

const vector<string> EngineInterface::clock_getIds() const
{
	vector<string> result;

	for(const auto & clockId : _core->getTimer()->getClockIds())
	{
		if(!clock_isIdReserved(clockId))
		{
			result.push_back(clockId);
		}
	}

	return result;
}

const float EngineInterface::clock_getDeltaTime(const string & clockId) const
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	return _core->getTimer()->getClockDeltaTime(clockId);
}

const bool EngineInterface::clock_isExisting(const string & clockId) const
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	return _core->getTimer()->isClockExisting(clockId);
}

const bool EngineInterface::clock_isStarted(const string & clockId) const
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	return _core->getTimer()->isClockStarted(clockId);
}

const bool EngineInterface::clock_isPaused(const string & clockId) const
{
	if(clock_isIdReserved(clockId))
	{
		abort();
	}

	return _core->getTimer()->isClockPaused(clockId);
}

const bool EngineInterface::clock_isIdReserved(const string & clockId) const
{
	return
		(
		clockId == "total" ||
		clockId == "mainUpdate" ||
		clockId == "physicsUpdate" ||
		clockId == "3dEntityUpdate" ||
		clockId == "2dEntityUpdate" ||
		clockId == "renderUpdate" ||
		clockId == "animationUpdate" ||
		clockId == "soundUpdate" ||
		clockId == "networkUpdate" ||
		clockId == "depthPreRender" ||
		clockId == "shadowPreRender" ||
		clockId == "reflectionPreRender" ||
		clockId == "refractionPreRender" ||
		clockId == "waterPreRender" ||
		clockId == "3dRender" ||
		clockId == "antiAliasingPostRender" ||
		clockId == "bloomPreRender" ||
		clockId == "dofPreRender" ||
		clockId == "lensFlarePreRender" ||
		clockId == "motionBlurPreRender" ||
		clockId == "2dRender" ||
		clockId == "bufferSwap"
		);
}