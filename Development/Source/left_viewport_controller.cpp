#include "left_viewport_controller.hpp"

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	ViewportController(fe3d, gui),
	_modelEditor(fe3d, gui)
{

}

void LeftViewportController::update(float delta)
{
	_modelEditor.update(delta);
}