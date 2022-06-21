#include "engine_interface.hpp"
#include "engine_core.hpp"
#include "tools.hpp"

void EngineInterface::inject(shared_ptr<EngineCore> core)
{
	_core = core;
}

void EngineInterface::application_start()
{
	_core->start();
}

void EngineInterface::application_stop()
{
	_core->stop();
}