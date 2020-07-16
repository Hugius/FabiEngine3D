#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

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

void FabiEngine3D::engine_stop()
{
	_core->_stop();
}