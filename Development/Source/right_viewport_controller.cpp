#include "right_viewport_controller.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

void RightViewportController::initialize()
{
	// Temporary values
	Vec3 black = Vec3(0.0f);
	Vec3 white = Vec3(1.0f);

	// Right-viewport: mainWindow
	_gui.getViewport("right")->addWindow("main", Vec2(0.0f), Vec2(1.9f, 2.0f), RightViewportController::FRAME_COLOR);

	// Private window instance of right viewport
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	rightWindow->addScreen("mainMenuControls");
	rightWindow->addScreen("environmentEditorControls");
	rightWindow->addScreen("modelEditorControls");
	rightWindow->addScreen("billboardEditorControls");
	rightWindow->addScreen("sceneEditorControls");
	rightWindow->addScreen("animationEditorControls");
	rightWindow->addScreen("scriptEditorControls");
	rightWindow->addScreen("audioEditorControls");

	// Main menu
	auto mainMenuScreen = rightWindow->getScreen("mainMenuControls");
	mainMenuScreen->addRectangle("mouse", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	mainMenuScreen->addRectangle("mouseLeft", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	mainMenuScreen->addRectangle("esc", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "esc.png", false);
	mainMenuScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("General Controls"), TH), "General Controls", white);
	mainMenuScreen->addTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(CW("Move Cursor"), TH), "Move Cursor", black, false);
	mainMenuScreen->addTextfield("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(CW("Confirm"), TH), "Confirm", black, false);
	mainMenuScreen->addTextfield("esc", Vec2(-0.5f, 0.275f), Vec2(CW("Exit"), TH), "Exit", black, false);

	// Environment editor
	auto environmentditorScreen = rightWindow->getScreen("environmentEditorControls");
	environmentditorScreen->addRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	environmentditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse.png", false);
	environmentditorScreen->addRectangle("h", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "h.png", false);
	environmentditorScreen->addRectangle("f", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "f.png", false);
	environmentditorScreen->addRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);
	environmentditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Editor Controls"), TH), "Editor Controls", white);
	environmentditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(CW("Toggle Camera"), TH), "Toggle Camera", black, false);
	environmentditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.475f), Vec2(CW("Move Camera"), TH), "Move Camera", black, false);
	environmentditorScreen->addTextfield("h", Vec2(-0.5f, 0.275f), Vec2(CW("Debug Render"), TH), "Debug Render", black, false);
	environmentditorScreen->addTextfield("f", Vec2(-0.5f, 0.075f), Vec2(CW("Wireframe"), TH), "Wireframe", black, false);
	environmentditorScreen->addTextfield("esc", Vec2(-0.5f, -0.125f), Vec2(CW("Back"), TH), "Back", black, false);

	// Model editor
	auto modelEditorScreen = rightWindow->getScreen("modelEditorControls");
	modelEditorScreen->addRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	modelEditorScreen->addRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	modelEditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	modelEditorScreen->addRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	modelEditorScreen->addRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	modelEditorScreen->addRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	modelEditorScreen->addRectangle("space", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "space.png", false);
	modelEditorScreen->addRectangle("shift", Vec2(-0.975f, -0.75f), Vec2(0.45f, 0.15f), "shift.png", false);
	modelEditorScreen->addRectangle("esc", Vec2(-0.975f, -0.95f), Vec2(0.45f, 0.15f), "esc.png", false);
	modelEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Editor Controls"), TH), "Editor Controls", white);
	modelEditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(CW("Toggle Camera"), TH), "Toggle Camera", black, false);
	modelEditorScreen->addTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(CW("Scroll Camera"), TH), "Scroll Camera", black, false);
	modelEditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(CW("Move Camera"), TH), "Move Camera", black, false);
	modelEditorScreen->addTextfield("h", Vec2(-0.5f, 0.075f), Vec2(CW("Debug Render"), TH), "Debug Render", black, false);
	modelEditorScreen->addTextfield("r", Vec2(-0.5f, -0.125f), Vec2(CW("Reference Box"), TH), "Reference Box", black, false);
	modelEditorScreen->addTextfield("f", Vec2(-0.5f, -0.325f), Vec2(CW("Wireframe"), TH), "Wireframe", black, false);
	modelEditorScreen->addTextfield("space", Vec2(-0.5f, -0.525f), Vec2(CW("Move Up"), TH), "Move Up", black, false);
	modelEditorScreen->addTextfield("shift", Vec2(-0.5f, -0.725f), Vec2(CW("Move Down"), TH), "Move Down", black, false);
	modelEditorScreen->addTextfield("esc", Vec2(-0.5f, -0.925f), Vec2(CW("Back"), TH), "Back", black, false);

	// Animation editor
	auto animationEditorScreen = rightWindow->getScreen("animationEditorControls");
	animationEditorScreen->addRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	animationEditorScreen->addRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	animationEditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	animationEditorScreen->addRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	animationEditorScreen->addRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	animationEditorScreen->addRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	animationEditorScreen->addRectangle("space", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "space.png", false);
	animationEditorScreen->addRectangle("shift", Vec2(-0.975f, -0.75f), Vec2(0.45f, 0.15f), "shift.png", false);
	animationEditorScreen->addRectangle("esc", Vec2(-0.975f, -0.95f), Vec2(0.45f, 0.15f), "esc.png", false);
	animationEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Editor Controls"), TH), "Editor Controls", white);
	animationEditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(CW("Toggle Camera"), TH), "Toggle Camera", black, false);
	animationEditorScreen->addTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(CW("Scroll Camera"), TH), "Scroll Camera", black, false);
	animationEditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(CW("Move Camera"), TH), "Move Camera", black, false);
	animationEditorScreen->addTextfield("h", Vec2(-0.5f, 0.075f), Vec2(CW("Debug Render"), TH), "Debug Render", black, false);
	animationEditorScreen->addTextfield("r", Vec2(-0.5f, -0.125f), Vec2(CW("Reference Box"), TH), "Reference Box", black, false);
	animationEditorScreen->addTextfield("f", Vec2(-0.5f, -0.325f), Vec2(CW("Wireframe"), TH), "Wireframe", black, false);
	animationEditorScreen->addTextfield("space", Vec2(-0.5f, -0.525f), Vec2(CW("Move Up"), TH), "Move Up", black, false);
	animationEditorScreen->addTextfield("shift", Vec2(-0.5f, -0.725f), Vec2(CW("Move Down"), TH), "Move Down", black, false);
	animationEditorScreen->addTextfield("esc", Vec2(-0.5f, -0.925f), Vec2(CW("Back"), TH), "Back", black, false);

	// Billboard editor
	auto billboardEditorScreen = rightWindow->getScreen("billboardEditorControls");
	billboardEditorScreen->addRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	billboardEditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse.png", false);
	billboardEditorScreen->addRectangle("h", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "h.png", false);
	billboardEditorScreen->addRectangle("r", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "r.png", false);
	billboardEditorScreen->addRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);
	billboardEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Editor Controls"), TH), "Editor Controls", white);
	billboardEditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(CW("Toggle Camera"), TH), "Toggle Camera", black, false);
	billboardEditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.475f), Vec2(CW("Move Camera"), TH), "Move Camera", black, false);
	billboardEditorScreen->addTextfield("h", Vec2(-0.5f, 0.275f), Vec2(CW("Debug Render"), TH), "Debug Render", black, false);
	billboardEditorScreen->addTextfield("r", Vec2(-0.5f, 0.075f), Vec2(CW("Ref Box"), TH), "Ref Box", black, false);
	billboardEditorScreen->addTextfield("esc", Vec2(-0.5f, -0.125f), Vec2(CW("Back"), TH), "Back", black, false);

	// Scene editor
	auto sceneEditorScreen = rightWindow->getScreen("sceneEditorControls");
	sceneEditorScreen->addRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	sceneEditorScreen->addRectangle("mouseLeft", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	sceneEditorScreen->addRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	sceneEditorScreen->addRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	sceneEditorScreen->addRectangle("f", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "f.png", false);
	sceneEditorScreen->addRectangle("b", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "b.png", false);
	sceneEditorScreen->addRectangle("w", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "w.png", false);
	sceneEditorScreen->addRectangle("a", Vec2(-0.475f, -0.55f), Vec2(0.45f, 0.15f), "a.png", false);
	sceneEditorScreen->addRectangle("s", Vec2(0.025f, -0.55f), Vec2(0.45f, 0.15f), "s.png", false);
	sceneEditorScreen->addRectangle("d", Vec2(0.525f, -0.55f), Vec2(0.45f, 0.15f), "d.png", false);
	sceneEditorScreen->addRectangle("space", Vec2(-0.975f, -0.825f), Vec2(0.45f, 0.15f), "space.png", false);
	sceneEditorScreen->addRectangle("shift", Vec2(-0.975f, -1.0f), Vec2(0.45f, 0.15f), "shift.png", false);
	sceneEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Editor Controls"), TH), "Editor Controls", white);
	sceneEditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(CW("Toggle Camera"), TH), "Toggle Camera", black, false);
	sceneEditorScreen->addTextfield("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(CW("Place"), TH), "Place", black, false);
	sceneEditorScreen->addTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(CW("Move Camera"), TH), "Move Camera", black, false);
	sceneEditorScreen->addTextfield("h", Vec2(-0.5f, 0.075f), Vec2(CW("Debug Render"), TH), "Debug Render", black, false);
	sceneEditorScreen->addTextfield("f", Vec2(-0.5f, -0.125f), Vec2(CW("Wireframe"), TH), "Wireframe", black, false);
	sceneEditorScreen->addTextfield("b", Vec2(-0.5f, -0.325f), Vec2(CW("Toggle AABB"), TH), "Toggle AABB", black, false);
	sceneEditorScreen->addTextfield("wasd", Vec2(-0.6f, -0.67f), Vec2(CW("XZ Movement"), TH), "XZ Movement", black, false);
	sceneEditorScreen->addTextfield("space", Vec2(-0.5f, -0.8f), Vec2(CW("Move Up"), TH), "Move Up", black, false);
	sceneEditorScreen->addTextfield("shift", Vec2(-0.5f, -0.975f), Vec2(CW("Move Down"), TH), "Move Down", black, false);

	// Script editor
	auto scriptEditorScreen = rightWindow->getScreen("scriptEditorControls");
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
	scriptEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Editor Controls"), TH), "Editor Controls", white);
	scriptEditorScreen->addTextfield("mouseLeft", Vec2(-0.5f, 0.675f), Vec2(CW("Place Cursor"), TH), "Place Cursor", black, false);
	scriptEditorScreen->addTextfield("mouseRight", Vec2(-0.5f, 0.475f), Vec2(CW("Select Line"), TH), "Select Line", black, false);
	scriptEditorScreen->addTextfield("enter", Vec2(-0.5f, 0.275f), Vec2(CW("Next Line"), TH), "Next Line", black, false);
	scriptEditorScreen->addTextfield("backspace", Vec2(-0.5f, 0.075f), Vec2(CW("Remove Char"), TH), "Remove Char", black, false);
	scriptEditorScreen->addTextfield("esc", Vec2(-0.5f, -0.125f), Vec2(CW("Back"), TH), "Back", black, false);
	scriptEditorScreen->addTextfield("arrows", Vec2(-0.525f, -0.47f), Vec2(CW("Navigation"), TH), "Navigation", black, false);
	scriptEditorScreen->addTextfield("ctrlC", Vec2(0.0f, -0.625f), Vec2(CW("Copy"), TH), "Copy", black, false);
	scriptEditorScreen->addTextfield("ctrlV", Vec2(0.0f, -0.8f), Vec2(CW("Paste"), TH), "Paste", black, false);

	// Audio editor
	auto audioEditorScreen = rightWindow->getScreen("audioEditorControls");
	audioEditorScreen->addRectangle("space", Vec2(-0.975f, 0.65f), Vec2(0.45f, 0.15f), "space.png", false);
	audioEditorScreen->addRectangle("r", Vec2(-0.975f, 0.45f), Vec2(0.45f, 0.15f), "r.png", false);
	audioEditorScreen->addRectangle("p", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "p.png", false);
	audioEditorScreen->addRectangle("s", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "s.png", false);
	audioEditorScreen->addRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);
	audioEditorScreen->addTextfield("title", Vec2(0.0f, 0.9f), Vec2(CW("Editor Controls"), TH), "Editor Controls", white);
	audioEditorScreen->addTextfield("space", Vec2(-0.5f, 0.675f), Vec2(CW("Play"), TH), "Play", black, false);
	audioEditorScreen->addTextfield("r", Vec2(-0.5f, 0.475f), Vec2(CW("Resume"), TH), "Resume", black, false);
	audioEditorScreen->addTextfield("p", Vec2(-0.5f, 0.275f), Vec2(CW("Pause"), TH), "Pause", black, false);
	audioEditorScreen->addTextfield("s", Vec2(-0.5f, 0.075f), Vec2(CW("Stop"), TH), "Stop", black, false);
	audioEditorScreen->addTextfield("esc", Vec2(-0.5f, -0.125f), Vec2(CW("Back"), TH), "Back", black, false);

	// Default screen
	rightWindow->setActiveScreen("mainMenuControls");
}

void RightViewportController::update()
{

}