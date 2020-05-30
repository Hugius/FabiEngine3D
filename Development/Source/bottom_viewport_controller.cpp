#include "bottom_viewport_controller.hpp"

void BottomViewportController::initialize()
{
	// Bottom-viewport: mainWindow
	_gui->getViewport("bottom")->addWindow("main", vec2(0.0f), vec2(1.975f, 1.8f), vec3(0.05f));
	_gui->getViewport("bottom")->getWindow("main")->addScreen("main");
	_gui->getViewport("bottom")->getWindow("main")->setActiveScreen("main");
}

void BottomViewportController::update()
{

}