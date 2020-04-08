#include "EngineControllerGUI.hpp"

EngineControllerGUI::EngineControllerGUI() :
	_guiManager(*this)
{

}

EngineControllerGUI::~EngineControllerGUI()
{

}

void EngineControllerGUI::FE3D_CONTROLLER_INIT()
{
	_guiManager.load();
}

void EngineControllerGUI::FE3D_CONTROLLER_UPDATE(float delta)
{
	_guiManager.update(delta);
}

void EngineControllerGUI::FE3D_CONTROLLER_DESTROY()
{
	_guiManager.unload();
}