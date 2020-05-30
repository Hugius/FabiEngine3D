#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class ViewportController
{
public:
	ViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);

	virtual void initialize() = 0;
	virtual void update() = 0;

protected:
	FabiEngine3D& _fe3d;

	shared_ptr<EngineGuiManager> _gui;
};