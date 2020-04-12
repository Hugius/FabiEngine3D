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
	_gui->load();
	camera_load(90.0f, 1.0f, 1000.0f, vec3(0.0f));
	skyEntity_add("sky", 0.01f);
	skyEntity_select("sky");
}

void EngineController::FE3D_CONTROLLER_UPDATE(float delta)
{
	_delta = delta;

	_gui->update(delta);

	_updateGuiInteraction();
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{
	_gui->unload();
}

void EngineController::_updateGuiInteraction()
{
	_topViewportController.update(_delta);
	_leftViewportController.update(_delta);
	_rightViewportController.update(_delta);
	_bottomViewportController.update(_delta);
}