#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::clock_create(const string & id)
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	_core->getTimer()->createClock(id);
}

void EngineInterface::clock_delete(const string & id)
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	_core->getTimer()->deleteClock(id);
}

void EngineInterface::clock_start(const string & id)
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	_core->getTimer()->startClock(id);
}

void EngineInterface::clock_pause(const string & id)
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	_core->getTimer()->pauseClock(id);
}

void EngineInterface::clock_resume(const string & id)
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	_core->getTimer()->resumeClock(id);
}

void EngineInterface::clock_stop(const string & id)
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	_core->getTimer()->stopClock(id);
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

const float EngineInterface::clock_getDeltaTime(const string & id) const
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	return _core->getTimer()->getClockDeltaTime(id);
}

const bool EngineInterface::clock_isExisting(const string & id) const
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	return _core->getTimer()->isClockExisting(id);
}

const bool EngineInterface::clock_isStarted(const string & id) const
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	return _core->getTimer()->isClockStarted(id);
}

const bool EngineInterface::clock_isPaused(const string & id) const
{
	if(clock_isIdReserved(id))
	{
		abort();
	}

	return _core->getTimer()->isClockPaused(id);
}

const bool EngineInterface::clock_isIdReserved(const string & id) const
{
	return
		(
		id == "total" ||
		id == "mainUpdate" ||
		id == "physicsUpdate" ||
		id == "3dEntityUpdate" ||
		id == "2dEntityUpdate" ||
		id == "renderUpdate" ||
		id == "animationUpdate" ||
		id == "soundUpdate" ||
		id == "networkUpdate" ||
		id == "miscUpdate" ||
		id == "depthPreRender" ||
		id == "shadowPreRender" ||
		id == "reflectionPreRender" ||
		id == "refractionPreRender" ||
		id == "waterPreRender" ||
		id == "3dEntityRender" ||
		id == "antiAliasingPostRender" ||
		id == "bloomPreRender" ||
		id == "dofPreRender" ||
		id == "lensFlarePreRender" ||
		id == "motionBlurPreRender" ||
		id == "2dEntityRender" ||
		id == "bufferSwap"
		);
}