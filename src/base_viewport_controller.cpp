#include "base_viewport_controller.hpp"

void BaseViewportController::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void BaseViewportController::inject(shared_ptr<GuiManager> gui)
{
	_gui = gui;
}