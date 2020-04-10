#include "EngineController.hpp"

EngineController::EngineController() :
	_guiManager(*this)
{

}

EngineController::~EngineController()
{

}

void EngineController::FE3D_CONTROLLER_INIT()
{
	_guiManager.load();
}

void EngineController::FE3D_CONTROLLER_UPDATE(float delta)
{
	_guiManager.update(delta);
}

void EngineController::FE3D_CONTROLLER_DESTROY()
{
	_guiManager.unload();
}