#include "bottom_viewport_controller.hpp"

void BottomViewportController::initialize()
{
	// Bottom-viewport: mainWindow
	_gui->getViewport("bottom")->addWindow("main", vec2(0.0f), vec2(1.975f, 1.8f), BottomViewportController::frameColor);
	_gui->getViewport("bottom")->getWindow("main")->addScreen("main");
	_gui->getViewport("bottom")->getWindow("main")->getScreen("main")->addRectangle("logo", vec2(0.0f), vec2(1.0f, 2.0f), "logo.png");
	_gui->getViewport("bottom")->getWindow("main")->setActiveScreen("main");
}

void BottomViewportController::update()
{

}