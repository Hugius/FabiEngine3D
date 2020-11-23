#include "right_viewport_controller.hpp"

#define CW(text) RVPC::calcTextWidth(text, 0.125f, 1.8f)

void RightViewportController::initialize()
{
	// Temporary values
	Vec3 black = Vec3(0.0f);
	Vec3 white = Vec3(1.0f);
	float textHeight = 0.1f;

	// Right-viewport: mainWindow
	_gui.getViewport("right")->addWindow("main", Vec2(0.0f), Vec2(1.9f, 2.0f), RightViewportController::frameColor);

	// Private window instance of right viewport
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	rightWindow->addScreen("mainMenuControls");
	rightWindow->addScreen("environmentEditorControls");
	rightWindow->addScreen("modelEditorControls");
	rightWindow->addScreen("billboardEditorControls");
	rightWindow->addScreen("sceneEditorControls");
	rightWindow->addScreen("scriptEditorControls");
	rightWindow->addScreen("audioEditorControls");

	// Environment editor
	auto environmentditorScreen = rightWindow->getScreen("environmentEditorControls");
	environmentditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Environment Editor"), textHeight), "Environment Editor", white);
	environmentditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(CW("Look"), textHeight), "Look", black, false);
	environmentditorScreen->addTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(CW("Rotate cam"), textHeight), "Rotate cam", black, false);
	environmentditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.275f), Vec2(CW("Toggle cam"), textHeight), "Toggle cam", black, false);
	environmentditorScreen->addTextfield("h", Vec2(-0.5f, 0.075f), Vec2(CW("Debug render"), textHeight), "Debug render", black, false);
	environmentditorScreen->addTextfield("f", Vec2(-0.5f, -0.125f), Vec2(CW("Wireframe"), textHeight), "Wireframe", black, false);
	environmentditorScreen->addTextfield("esc", Vec2(-0.5f, -0.325f), Vec2(CW("Back"), textHeight), "Back", black, false);
	environmentditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	environmentditorScreen->addRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	environmentditorScreen->addRectangle("mouseRight", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	environmentditorScreen->addRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	environmentditorScreen->addRectangle("f", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "f.png", false);
	environmentditorScreen->addRectangle("esc", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "esc.png", false);

	// Main menu
	auto mainMenuScreen = rightWindow->getScreen("mainMenuControls");
	mainMenuScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("General controls"), textHeight), "General controls", white);
	mainMenuScreen->addTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(CW("Move cursor"), textHeight), "Move cursor", black, false);
	mainMenuScreen->addTextfield("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(CW("Confirm"), textHeight), "Confirm", black, false);
	mainMenuScreen->addTextfield("esc", Vec2(-0.5f, 0.275f), Vec2(CW("Exit"), textHeight), "Exit", black, false);
	mainMenuScreen->addRectangle("mouse", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	mainMenuScreen->addRectangle("mouseLeft", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	mainMenuScreen->addRectangle("esc", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "esc.png", false);

	// Model editor
	auto modelEditorScreen = rightWindow->getScreen("modelEditorControls");
	modelEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Model Editor"), textHeight), "Model Editor", white);
	modelEditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(CW("Move cam"), textHeight), "Move cam", black, false);
	modelEditorScreen->addTextfield("h", Vec2(-0.5f, 0.475f), Vec2(CW("Debug render"), textHeight), "Debug render", black, false);
	modelEditorScreen->addTextfield("r", Vec2(-0.5f, 0.275f), Vec2(CW("Ref box"), textHeight), "Ref box", black, false);
	modelEditorScreen->addTextfield("esc", Vec2(-0.5f, 0.075f), Vec2(CW("Back"), textHeight), "Back", black, false);
	modelEditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	modelEditorScreen->addRectangle("h", Vec2(-0.975f, 0.45f), Vec2(0.45f, 0.15f), "h.png", false);
	modelEditorScreen->addRectangle("r", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "r.png", false);
	modelEditorScreen->addRectangle("esc", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "esc.png", false);

	// Billboard editor
	auto billboardEditorScreen = rightWindow->getScreen("billboardEditorControls");
	billboardEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Billboard Editor"), textHeight), "Billboard Editor", white);
	billboardEditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(CW("Rotate cam"), textHeight), "Rotate cam", black, false);
	billboardEditorScreen->addTextfield("h", Vec2(-0.5f, 0.475f), Vec2(CW("Debug render"), textHeight), "Debug render", black, false);
	billboardEditorScreen->addTextfield("r", Vec2(-0.5f, 0.275f), Vec2(CW("Ref box"), textHeight), "Ref box", black, false);
	billboardEditorScreen->addTextfield("esc", Vec2(-0.5f, 0.075f), Vec2(CW("Back"), textHeight), "Back", black, false);
	billboardEditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	billboardEditorScreen->addRectangle("h", Vec2(-0.975f, 0.45f), Vec2(0.45f, 0.15f), "h.png", false);
	billboardEditorScreen->addRectangle("r", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "r.png", false);
	billboardEditorScreen->addRectangle("esc", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "esc.png", false);

	// Scene editor
	auto sceneEditorScreen = rightWindow->getScreen("sceneEditorControls");
	sceneEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Scene Editor"), textHeight), "Scene Editor", white);
	sceneEditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(CW("Look/Move"), textHeight), "Look/Move", black, false);
	sceneEditorScreen->addTextfield("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(CW("Place"), textHeight), "Place", black, false);
	sceneEditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.275f), Vec2(CW("Toggle cam"), textHeight), "Toggle cam", black, false);
	sceneEditorScreen->addTextfield("h", Vec2(-0.5f, 0.075f), Vec2(CW("Debug render"), textHeight), "Debug render", black, false);
	sceneEditorScreen->addTextfield("f", Vec2(-0.5f, -0.125f), Vec2(CW("Wireframe"), textHeight), "Wireframe", black, false);
	sceneEditorScreen->addTextfield("esc", Vec2(-0.5f, -0.325f), Vec2(CW("Back"), textHeight), "Back", black, false);
	sceneEditorScreen->addTextfield("wasd", Vec2(-0.725f, -0.67f), Vec2(CW("XZ movement"), textHeight), "XZ movement", black, false);
	sceneEditorScreen->addTextfield("shift", Vec2(-0.5f, -0.8f), Vec2(CW("Move down"), textHeight), "Move down", black, false);
	sceneEditorScreen->addTextfield("space", Vec2(-0.5f, -0.975f), Vec2(CW("Move up"), textHeight), "Move up", black, false);
	sceneEditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	sceneEditorScreen->addRectangle("mouseLeft", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	sceneEditorScreen->addRectangle("mouseRight", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	sceneEditorScreen->addRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	sceneEditorScreen->addRectangle("f", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "f.png", false);
	sceneEditorScreen->addRectangle("esc", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "esc.png", false);
	sceneEditorScreen->addRectangle("w", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "w.png", false);
	sceneEditorScreen->addRectangle("a", Vec2(-0.475f, -0.55f), Vec2(0.45f, 0.15f), "a.png", false);
	sceneEditorScreen->addRectangle("s", Vec2(0.025f, -0.55f), Vec2(0.45f, 0.15f), "s.png", false);
	sceneEditorScreen->addRectangle("d", Vec2(0.525f, -0.55f), Vec2(0.45f, 0.15f), "d.png", false);
	sceneEditorScreen->addRectangle("shift", Vec2(-0.975f, -0.825f), Vec2(0.45f, 0.15f), "shift.png", false);
	sceneEditorScreen->addRectangle("space", Vec2(-0.975f, -1.0f), Vec2(0.45f, 0.15f), "space.png", false);

	// Script editor
	auto scriptEditorScreen = rightWindow->getScreen("scriptEditorControls");
	scriptEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Audio Editor"), textHeight), "Audio Editor", white);
	scriptEditorScreen->addTextfield("mouseLeft", Vec2(-0.5f, 0.675f), Vec2(CW("Place cursor"), textHeight), "Place cursor", black, false);
	scriptEditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.475f), Vec2(CW("Select line"), textHeight), "Select line", black, false);
	scriptEditorScreen->addTextfield("enter", Vec2(-0.5f, 0.275f), Vec2(CW("Next line"), textHeight), "Next line", black, false);
	scriptEditorScreen->addTextfield("backspace", Vec2(-0.5f, 0.075f), Vec2(CW("Remove char"), textHeight), "Remove char", black, false);
	scriptEditorScreen->addTextfield("esc", Vec2(-0.5f, -0.125f), Vec2(CW("Back"), textHeight), "Back", black, false);
	scriptEditorScreen->addTextfield("arrows", Vec2(-0.725f, -0.47f), Vec2(CW("Navigation"), textHeight), "Navigation", black, false);
	scriptEditorScreen->addTextfield("ctrlC", Vec2(0.0f, -0.6f), Vec2(CW("Copy"), textHeight), "Copy", black, false);
	scriptEditorScreen->addTextfield("ctrlV", Vec2(0.0f, -0.8f), Vec2(CW("Paste"), textHeight), "Paste", black, false);
	scriptEditorScreen->addRectangle("mouseLeft", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	scriptEditorScreen->addRectangle("mouseRight", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	scriptEditorScreen->addRectangle("enter", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "enter.png", false);
	scriptEditorScreen->addRectangle("backspace", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "backspace.png", false);
	scriptEditorScreen->addRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);
	scriptEditorScreen->addRectangle("left", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "left.png", false);
	scriptEditorScreen->addRectangle("right", Vec2(-0.475f, -0.35f), Vec2(0.45f, 0.15f), "right.png", false);
	scriptEditorScreen->addRectangle("up", Vec2(0.025f, -0.35f), Vec2(0.45f, 0.15f), "up.png", false);
	scriptEditorScreen->addRectangle("down", Vec2(0.525f, -0.35f), Vec2(0.45f, 0.15f), "down.png", false);
	scriptEditorScreen->addRectangle("ctrlC", Vec2(-0.975f, -0.65f), Vec2(0.45f, 0.15f), "ctrl.png", false);
	scriptEditorScreen->addRectangle("c", Vec2(-0.475f, -0.65f), Vec2(0.45f, 0.15f), "c.png", false);
	scriptEditorScreen->addRectangle("ctrlV", Vec2(-0.975f, -0.825f), Vec2(0.45f, 0.15f), "ctrl.png", false);
	scriptEditorScreen->addRectangle("v", Vec2(-0.475f, -0.825f), Vec2(0.45f, 0.15f), "v.png", false);

	// Audio editor
	auto audioEditorScreen = rightWindow->getScreen("audioEditorControls");
	audioEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Audio Editor"), textHeight), "Audio Editor", white);
	audioEditorScreen->addTextfield("space", Vec2(-0.5f, 0.675f), Vec2(CW("Play"), textHeight), "Play", black, false);
	audioEditorScreen->addTextfield("r", Vec2(-0.5f, 0.475f), Vec2(CW("Resume"), textHeight), "Resume", black, false);
	audioEditorScreen->addTextfield("p", Vec2(-0.5f, 0.275f), Vec2(CW("Pause"), textHeight), "Pause", black, false);
	audioEditorScreen->addTextfield("s", Vec2(-0.5f, 0.075f), Vec2(CW("Stop"), textHeight), "Stop", black, false);
	audioEditorScreen->addTextfield("esc", Vec2(-0.5f, -0.125f), Vec2(CW("Back"), textHeight), "Back", black, false);
	audioEditorScreen->addRectangle("space", Vec2(-0.975f, 0.65f), Vec2(0.45f, 0.15f), "space.png", false);
	audioEditorScreen->addRectangle("r", Vec2(-0.975f, 0.45f), Vec2(0.45f, 0.15f), "r.png", false);
	audioEditorScreen->addRectangle("p", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "p.png", false);
	audioEditorScreen->addRectangle("s", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "s.png", false);
	audioEditorScreen->addRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);

	// Default screen
	rightWindow->setActiveScreen("mainMenuControls");
}

void RightViewportController::update()
{

}