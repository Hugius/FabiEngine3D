#include "right_viewport_controller.hpp"

#define TW(text) calculateTextWidth(text, CW)

using RVPC = RightViewportController;

void RightViewportController::initialize()
{
	_gui.getViewport("right")->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), RightViewportController::FRAME_COLOR);
	auto window = _gui.getViewport("right")->getWindow("main");

	window->createScreen("main");

	window->setActiveScreen("main");
}

void RightViewportController::update()
{

}