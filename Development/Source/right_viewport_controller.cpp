#include "right_viewport_controller.hpp"

void RightViewportController::initialize()
{
	// Right-viewport: mainWindow
	_gui->getViewport("rightViewport")->addWindow("mainWindow", vec2(0.0f), vec2(1.9f, 2.0f), vec3(0.5f));
	_gui->getViewport("rightViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	_gui->getViewport("rightViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
}

void RightViewportController::update(float delta)
{

}