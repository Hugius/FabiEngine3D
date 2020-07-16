#include "right_viewport_controller.hpp"

void RightViewportController::initialize()
{
	// Right-viewport: mainWindow
	_gui->getViewport("right")->addWindow("main", vec2(0.0f), vec2(1.9f, 2.0f), RightViewportController::frameColor);
	_gui->getViewport("right")->getWindow("main")->addScreen("main");
	_gui->getViewport("right")->getWindow("main")->setActiveScreen("main");
}

void RightViewportController::update()
{

}