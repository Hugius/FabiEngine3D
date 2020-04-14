#include "EngineController.hpp"

EngineController::EngineController() :
	_gui(make_shared<EngineGuiManager>(*this)),
	_topViewportController(*this, _gui),
	_leftViewportController(*this, _gui),
	_rightViewportController(*this, _gui),
	_bottomViewportController(*this, _gui)
{

}

EngineController::~EngineController()
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	misc_setMainColor(vec3(0.5f, 0.5f, 1.0f));
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