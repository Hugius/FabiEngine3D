#include "right_viewport_controller.hpp"

void RightViewportController::load()
{
	_gui->getRightViewport()->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), FRAME_COLOR);
	auto window = _gui->getRightViewport()->getWindow("main");

	window->createScreen("main");

	window->setActiveScreen("main");
}

void RightViewportController::update()
{

}