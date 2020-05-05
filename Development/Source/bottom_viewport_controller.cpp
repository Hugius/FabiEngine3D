#include "bottom_viewport_controller.hpp"

void BottomViewportController::initialize()
{
	// Bottom-viewport: mainWindow
	_gui->getViewport("bottomViewport")->addWindow("mainWindow", vec2(0.0f), vec2(1.975f, 1.8f), vec3(0.05f));
	_gui->getViewport("bottomViewport")->getWindow("mainWindow")->addScreen("mainScreen");
	_gui->getViewport("bottomViewport")->getWindow("mainWindow")->setActiveScreen("mainScreen");
}

void BottomViewportController::update(float delta)
{

}