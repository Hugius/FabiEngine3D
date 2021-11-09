#include "fe3d.hpp"
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

void FabiEngine3D::application_start()
{
	_core->_start();
}

void FabiEngine3D::application_pause()
{
	_core->_pause();
}

void FabiEngine3D::application_resume()
{
	_core->_resume();
}

void FabiEngine3D::application_stop()
{
	_core->_stop();
}

const bool FabiEngine3D::application_isPaused() const
{
	return _core->_isPaused;
}