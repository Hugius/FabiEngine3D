#include "engine_interface.hpp"
#include "engine_core.hpp"
#include "configuration.hpp"

void EngineInterface::inject(shared_ptr<EngineCore> core)
{
	_core = core;
}

void EngineInterface::application_start()
{
	_core->start();
}

void EngineInterface::application_pause()
{
	_core->pause();
}

void EngineInterface::application_resume()
{
	_core->resume();
}

void EngineInterface::application_stop()
{
	_core->stop();
}

const bool EngineInterface::application_isPaused() const
{
	return _core->isPaused();
}