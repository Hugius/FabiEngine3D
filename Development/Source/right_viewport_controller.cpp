#include "right_viewport_controller.hpp"

#define CW(text) RVPC::calcTextWidth(text, 0.1f, 1.8f)

void RightViewportController::initialize()
{
	// Right-viewport: mainWindow
	_gui.getViewport("right")->addWindow("main", vec2(0.0f), vec2(1.9f, 2.0f), RightViewportController::frameColor);

	// Private window instance of right viewport
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Main menu
	rightWindow->addScreen("mainMenuControls");
	auto mainMenuScreen = rightWindow->getScreen("mainMenuControls");
	mainMenuScreen->addTextfield("title", vec2(0.0f, 0.9f), vec2(CW("General controls"), 0.1f), "General controls", vec3(1.0f));
	mainMenuScreen->addTextfield("mouse", vec2(-0.5f, 0.675f), vec2(CW("Move cursor"), 0.1f), "Move cursor", vec3(1.0f), false);
	mainMenuScreen->addTextfield("mouseLeft", vec2(-0.5f, 0.475f), vec2(CW("Confirm"), 0.1f), "Confirm", vec3(1.0f), false);
	mainMenuScreen->addRectangle("mouse", vec2(-1.0f, 0.65f), vec2(0.6f, 0.15f), "mouse.png", false);
	mainMenuScreen->addRectangle("mouseLeft", vec2(-1.0f, 0.45f), vec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->setActiveScreen("mainMenuControls");

	rightWindow->addScreen("main");
	rightWindow->setActiveScreen("main");
}

void RightViewportController::update()
{

}