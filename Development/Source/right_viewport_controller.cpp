#include "right_viewport_controller.hpp"

#define CW(text) RVPC::calcTextWidth(text, 0.125f, 1.8f)

void RightViewportController::initialize()
{
	// Temporary values
	Vec3 color = Vec3(1.0f);
	float textHeight = 0.1f;

	// Right-viewport: mainWindow
	_gui.getViewport("right")->addWindow("main", Vec2(0.0f), Vec2(1.9f, 2.0f), RightViewportController::frameColor);

	// Private window instance of right viewport
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	rightWindow->addScreen("mainMenuControls");
	rightWindow->addScreen("modelEditorControls");

	// Main menu
	auto mainMenuScreen = rightWindow->getScreen("mainMenuControls");
	mainMenuScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Main Menu"), textHeight), "Main Menu", color);
	mainMenuScreen->addTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(CW("Move cursor"), textHeight), "Move cursor", color, false);
	mainMenuScreen->addTextfield("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(CW("Confirm"), textHeight), "Confirm", color, false);
	mainMenuScreen->addRectangle("mouse", Vec2(-1.0f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	mainMenuScreen->addRectangle("mouseLeft", Vec2(-1.0f, 0.45f), Vec2(0.6f, 0.15f), "mouse_left.png", false);

	// Main menu
	auto modelEditorScreen = rightWindow->getScreen("modelEditorControls");
	modelEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Model Editor"), textHeight), "Model Editor", color);
	modelEditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(CW("Move cursor"), textHeight), "Move cursor", color, false);
	modelEditorScreen->addTextfield("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(CW("Confirm"), textHeight), "Confirm", color, false);
	modelEditorScreen->addTextfield("r", Vec2(-0.5f, 0.275f), Vec2(CW("Ref box"), textHeight), "Ref box", color, false);
	modelEditorScreen->addRectangle("mouse", Vec2(-1.0f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	modelEditorScreen->addRectangle("mouseLeft", Vec2(-1.0f, 0.45f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	modelEditorScreen->addRectangle("r", Vec2(-1.0f, 0.25f), Vec2(0.6f, 0.15f), "r.png", false);

	// Default screen
	rightWindow->setActiveScreen("mainMenuControls");
}

void RightViewportController::update()
{

}