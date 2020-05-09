#include "engine_controller.hpp"

EngineController::EngineController() :
	_gui(make_shared<EngineGuiManager>(*this)),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_topViewportController(*this, _gui, _leftViewportController.getModelEditor()),
	_bottomViewportController(*this, _gui)
{

}

EngineController::~EngineController()
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

void EngineController::FE3D_CONTROLLER_UPDATE(float delta)
{
	_delta = delta;

	_gui->update(delta);
	_topViewportController.update(_delta);
	_leftViewportController.update(_delta);
	_rightViewportController.update(_delta);
	_bottomViewportController.update(_delta);
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{

}