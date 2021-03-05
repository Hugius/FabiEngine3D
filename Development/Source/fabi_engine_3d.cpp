#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"
#include "configuration.hpp"

FabiEngine3D::FabiEngine3D()
{
	_core = new CoreEngine(*this);
}

FabiEngine3D::~FabiEngine3D()
{
	delete _core;
}

void FabiEngine3D::engine_start()
{
	_core->_start();
}

void FabiEngine3D::engine_pause()
{
	_core->_pause();
}

void FabiEngine3D::engine_resume()
{
	_core->_resume();
}

void FabiEngine3D::engine_stop()
{
	_core->_stop();
}

bool FabiEngine3D::engine_isPaused()
{
	return _core->_isPaused;
}

bool FabiEngine3D::engine_isGameExported()
{
	return Config::getInst().isGameExported();
}

string FabiEngine3D::engine_getGameTitle()
{
	return Config::getInst().getGameTitle();
}