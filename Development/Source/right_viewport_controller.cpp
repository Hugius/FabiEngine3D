#include "right_viewport_controller.hpp"

#define TW(text) calculateTextWidth(text, CW)

void RightViewportController::initialize()
{
	// Window
	_gui.getViewport("right")->createWindow("main", Vec2(0.0f), Vec2(1.9f, 2.0f), RightViewportController::FRAME_COLOR);
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Right-viewport: mainMenuControls
	rightWindow->createScreen("mainMenuControls");
	rightWindow->getScreen("mainMenuControls")->createRectangle("mouse", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("mainMenuControls")->createRectangle("mouseLeft", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->getScreen("mainMenuControls")->createRectangle("esc", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("mainMenuControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("General Controls"), CH), "General Controls", WHITE);
	rightWindow->getScreen("mainMenuControls")->createTextfield("mouse", Vec2(-0.5f, 0.675f), Vec2(TW("Move Cursor"), CH), "Move Cursor", BLACK, false);
	rightWindow->getScreen("mainMenuControls")->createTextfield("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(TW("Confirm"), CH), "Confirm", BLACK, false);
	rightWindow->getScreen("mainMenuControls")->createTextfield("esc", Vec2(-0.5f, 0.275f), Vec2(TW("Exit"), CH), "Exit", BLACK, false);

	// Right-viewport: skyEditorControls
	rightWindow->createScreen("skyEditorControls");
	rightWindow->getScreen("skyEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("skyEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("skyEditorControls")->createTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false);
	rightWindow->getScreen("skyEditorControls")->createTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Scroll Camera"), CH), "Scroll Camera", BLACK, false);
	rightWindow->getScreen("skyEditorControls")->createTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false);
	rightWindow->getScreen("skyEditorControls")->createTextfield("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false);
	rightWindow->getScreen("skyEditorControls")->createTextfield("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false);
	rightWindow->getScreen("skyEditorControls")->createTextfield("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wire Frame"), CH), "Wire Frame", BLACK, false);
	rightWindow->getScreen("skyEditorControls")->createTextfield("esc", Vec2(-0.5f, -0.525f), Vec2(TW("Back"), CH), "Back", BLACK, false);

	// Right-viewport: terrainEditorControls
	rightWindow->createScreen("terrainEditorControls");
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("terrainEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("terrainEditorControls")->createTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false);
	rightWindow->getScreen("terrainEditorControls")->createTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Scroll Camera"), CH), "Scroll Camera", BLACK, false);
	rightWindow->getScreen("terrainEditorControls")->createTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false);
	rightWindow->getScreen("terrainEditorControls")->createTextfield("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false);
	rightWindow->getScreen("terrainEditorControls")->createTextfield("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false);
	rightWindow->getScreen("terrainEditorControls")->createTextfield("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wire Frame"), CH), "Wire Frame", BLACK, false);
	rightWindow->getScreen("terrainEditorControls")->createTextfield("esc", Vec2(-0.5f, -0.525f), Vec2(TW("Back"), CH), "Back", BLACK, false);

	// Right-viewport: waterEditorControls
	rightWindow->createScreen("waterEditorControls");
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("waterEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("waterEditorControls")->createTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false);
	rightWindow->getScreen("waterEditorControls")->createTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Scroll Camera"), CH), "Scroll Camera", BLACK, false);
	rightWindow->getScreen("waterEditorControls")->createTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false);
	rightWindow->getScreen("waterEditorControls")->createTextfield("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false);
	rightWindow->getScreen("waterEditorControls")->createTextfield("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false);
	rightWindow->getScreen("waterEditorControls")->createTextfield("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wire Frame"), CH), "Wire Frame", BLACK, false);
	rightWindow->getScreen("waterEditorControls")->createTextfield("esc", Vec2(-0.5f, -0.525f), Vec2(TW("Back"), CH), "Back", BLACK, false);

	// Right-viewport: modelEditorControls
	rightWindow->createScreen("modelEditorControls");
	rightWindow->getScreen("modelEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("space", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("shift", Vec2(-0.975f, -0.75f), Vec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.95f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("modelEditorControls")->createTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Scroll Camera"), CH), "Scroll Camera", BLACK, false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wire Frame"), CH), "Wire Frame", BLACK, false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("space", Vec2(-0.5f, -0.525f), Vec2(TW("Move Up"), CH), "Move Up", BLACK, false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("shift", Vec2(-0.5f, -0.725f), Vec2(TW("Move Down"), CH), "Move Down", BLACK, false);
	rightWindow->getScreen("modelEditorControls")->createTextfield("esc", Vec2(-0.5f, -0.925f), Vec2(TW("Back"), CH), "Back", BLACK, false);

	// Right-viewport: animationEditorControls
	rightWindow->createScreen("animationEditorControls");
	rightWindow->getScreen("animationEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("space", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("shift", Vec2(-0.975f, -0.75f), Vec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.95f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("animationEditorControls")->createTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Scroll Camera"), CH), "Scroll Camera", BLACK, false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wire Frame"), CH), "Wire Frame", BLACK, false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("space", Vec2(-0.5f, -0.525f), Vec2(TW("Move Up"), CH), "Move Up", BLACK, false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("shift", Vec2(-0.5f, -0.725f), Vec2(TW("Move Down"), CH), "Move Down", BLACK, false);
	rightWindow->getScreen("animationEditorControls")->createTextfield("esc", Vec2(-0.5f, -0.925f), Vec2(TW("Back"), CH), "Back", BLACK, false);

	// Right-viewport: billboardEditorControls
	rightWindow->createScreen("billboardEditorControls");
	rightWindow->getScreen("billboardEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("space", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("shift", Vec2(-0.975f, -0.75f), Vec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.95f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Scroll Camera"), CH), "Scroll Camera", BLACK, false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wire Frame"), CH), "Wire Frame", BLACK, false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("space", Vec2(-0.5f, -0.525f), Vec2(TW("Move Up"), CH), "Move Up", BLACK, false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("shift", Vec2(-0.5f, -0.725f), Vec2(TW("Move Down"), CH), "Move Down", BLACK, false);
	rightWindow->getScreen("billboardEditorControls")->createTextfield("esc", Vec2(-0.5f, -0.925f), Vec2(TW("Back"), CH), "Back", BLACK, false);

	// Right-viewport: audioEditorControls
	rightWindow->createScreen("audioEditorControls");
	rightWindow->getScreen("audioEditorControls")->createRectangle("space", Vec2(-0.975f, 0.65f), Vec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("r", Vec2(-0.975f, 0.45f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("p", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "p.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("s", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "s.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("audioEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("audioEditorControls")->createTextfield("space", Vec2(-0.5f, 0.675f), Vec2(TW("Play"), CH), "Play", BLACK, false);
	rightWindow->getScreen("audioEditorControls")->createTextfield("r", Vec2(-0.5f, 0.475f), Vec2(TW("Resume"), CH), "Resume", BLACK, false);
	rightWindow->getScreen("audioEditorControls")->createTextfield("p", Vec2(-0.5f, 0.275f), Vec2(TW("Pause"), CH), "Pause", BLACK, false);
	rightWindow->getScreen("audioEditorControls")->createTextfield("s", Vec2(-0.5f, 0.075f), Vec2(TW("Stop"), CH), "Stop", BLACK, false);
	rightWindow->getScreen("audioEditorControls")->createTextfield("esc", Vec2(-0.5f, -0.125f), Vec2(TW("Back"), CH), "Back", BLACK, false);

	// Right-viewport: sceneEditorControls
	rightWindow->createScreen("sceneEditorControls");
	rightWindow->getScreen("sceneEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("mouseLeft", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("f", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("b", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "b.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("w", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "w.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("a", Vec2(-0.475f, -0.55f), Vec2(0.45f, 0.15f), "a.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("s", Vec2(0.025f, -0.55f), Vec2(0.45f, 0.15f), "s.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("d", Vec2(0.525f, -0.55f), Vec2(0.45f, 0.15f), "d.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("space", Vec2(-0.975f, -0.825f), Vec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("shift", Vec2(-0.975f, -1.0f), Vec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(TW("Place"), CH), "Place", BLACK, false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("f", Vec2(-0.5f, -0.125f), Vec2(TW("Wire Frame"), CH), "Wire Frame", BLACK, false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("b", Vec2(-0.5f, -0.325f), Vec2(TW("Toggle AABB"), CH), "Toggle AABB", BLACK, false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("wasd", Vec2(-0.6f, -0.67f), Vec2(TW("XZ Movement"), CH), "XZ Movement", BLACK, false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("space", Vec2(-0.5f, -0.8f), Vec2(TW("Move Up"), CH), "Move Up", BLACK, false);
	rightWindow->getScreen("sceneEditorControls")->createTextfield("shift", Vec2(-0.5f, -0.975f), Vec2(TW("Move Down"), CH), "Move Down", BLACK, false);

	// Right-viewport: scriptEditorControls
	rightWindow->createScreen("scriptEditorControls");
	rightWindow->getScreen("scriptEditorControls")->createRectangle("mouseLeft", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("enter", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "enter.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("backspace", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "backspace.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("left", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "left.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("right", Vec2(-0.475f, -0.35f), Vec2(0.45f, 0.15f), "right.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("up", Vec2(0.025f, -0.35f), Vec2(0.45f, 0.15f), "up.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("down", Vec2(0.525f, -0.35f), Vec2(0.45f, 0.15f), "down.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("ctrlC", Vec2(-0.975f, -0.65f), Vec2(0.45f, 0.15f), "ctrl.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("c", Vec2(-0.475f, -0.65f), Vec2(0.45f, 0.15f), "c.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("ctrlV", Vec2(-0.975f, -0.825f), Vec2(0.45f, 0.15f), "ctrl.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("v", Vec2(-0.475f, -0.825f), Vec2(0.45f, 0.15f), "v.png", false);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("mouseLeft", Vec2(-0.5f, 0.675f), Vec2(TW("Place Cursor"), CH), "Place Cursor", BLACK, false);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("mouseRight", Vec2(-0.5f, 0.475f), Vec2(TW("Choose Line"), CH), "Choose Line", BLACK, false);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("enter", Vec2(-0.5f, 0.275f), Vec2(TW("Next Line"), CH), "Next Line", BLACK, false);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("backspace", Vec2(-0.5f, 0.075f), Vec2(TW("Remove Char"), CH), "Remove Char", BLACK, false);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("esc", Vec2(-0.5f, -0.125f), Vec2(TW("Back"), CH), "Back", BLACK, false);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("arrows", Vec2(-0.525f, -0.47f), Vec2(TW("Navigation"), CH), "Navigation", BLACK, false);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("ctrlC", Vec2(0.0f, -0.625f), Vec2(TW("Copy"), CH), "Copy", BLACK, false);
	rightWindow->getScreen("scriptEditorControls")->createTextfield("ctrlV", Vec2(0.0f, -0.8f), Vec2(TW("Paste"), CH), "Paste", BLACK, false);

	// Default screen
	rightWindow->setActiveScreen("mainMenuControls");
}

void RightViewportController::update()
{

}