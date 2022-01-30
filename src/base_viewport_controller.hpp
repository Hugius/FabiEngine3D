#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"

class BaseViewportController
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<GuiManager> gui);

	virtual void initialize() = 0;
	virtual void update() = 0;

protected:
	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiManager> _gui = nullptr;
};