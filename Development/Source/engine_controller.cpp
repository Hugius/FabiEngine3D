#include "engine_controller.hpp"

EngineController::EngineController() :
	_gui(make_shared<EngineGuiManager>(*this)),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui, _leftViewportController.getModelEditor(), _leftViewportController.getWorldEditor()),
	_bottomViewportController(*this, _gui)
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	misc_setMainRenderingColor(vec3(0.5f, 0.5f, 1.0f));
	_topViewportController.initialize();
	_leftViewportController.initialize();
	_rightViewportController.initialize();
	_bottomViewportController.initialize();
}

void EngineController::FE3D_CONTROLLER_UPDATE()
{
	_gui->update();
	_topViewportController.update();
	_leftViewportController.update();
	_rightViewportController.update();
	_bottomViewportController.update();
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{

}