#include "right_viewport_controller.hpp"

#define TW(text) calculateTextWidth(text, CW)

using RVPC = RightViewportController;

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
	rightWindow->getScreen("mainMenuControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("General Controls"), CH), "General Controls", WHITE, true, false);
	rightWindow->getScreen("mainMenuControls")->createTextField("mouse", Vec2(-0.5f, 0.675f), Vec2(TW("Move Cursor"), CH), "Move Cursor", BLACK, false, false);
	rightWindow->getScreen("mainMenuControls")->createTextField("mouseLeft", Vec2(-0.5f, 0.475f), Vec2(TW("Confirm"), CH), "Confirm", BLACK, false, false);
	rightWindow->getScreen("mainMenuControls")->createTextField("esc", Vec2(-0.5f, 0.275f), Vec2(TW("Exit"), CH), "Exit", BLACK, false, false);

	// Right-viewport: skyEditorControls
	rightWindow->createScreen("skyEditorControls");
	rightWindow->getScreen("skyEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("h", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("f", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("skyEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("mouse", Vec2(-0.5f, 0.475f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("h", Vec2(-0.5f, 0.275f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("f", Vec2(-0.5f, 0.075f), Vec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("esc", Vec2(-0.5f, -0.125f), Vec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: terrainEditorControls
	rightWindow->createScreen("terrainEditorControls");
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("esc", Vec2(-0.5f, -0.525f), Vec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: waterEditorControls
	rightWindow->createScreen("waterEditorControls");
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("h", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("r", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("waterEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("esc", Vec2(-0.5f, -0.525f), Vec2(TW("Back"), CH), "Back", BLACK, false, false);

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
	rightWindow->getScreen("modelEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("space", Vec2(-0.5f, -0.525f), Vec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("shift", Vec2(-0.5f, -0.725f), Vec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("esc", Vec2(-0.5f, -0.925f), Vec2(TW("Back"), CH), "Back", BLACK, false, false);

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
	rightWindow->getScreen("animationEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("space", Vec2(-0.5f, -0.525f), Vec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("shift", Vec2(-0.5f, -0.725f), Vec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("esc", Vec2(-0.5f, -0.925f), Vec2(TW("Back"), CH), "Back", BLACK, false, false);

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
	rightWindow->getScreen("billboardEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("mouseRight", Vec2(-0.5f, 0.675f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("mouse", Vec2(-0.5f, 0.275f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("h", Vec2(-0.5f, 0.075f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("r", Vec2(-0.5f, -0.125f), Vec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("space", Vec2(-0.5f, -0.525f), Vec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("shift", Vec2(-0.5f, -0.725f), Vec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("esc", Vec2(-0.5f, -0.925f), Vec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: audioEditorControls
	rightWindow->createScreen("audioEditorControls");
	rightWindow->getScreen("audioEditorControls")->createRectangle("space", Vec2(-0.975f, 0.65f), Vec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("r", Vec2(-0.975f, 0.45f), Vec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("p", Vec2(-0.975f, 0.25f), Vec2(0.45f, 0.15f), "p.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("s", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "s.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("audioEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("space", Vec2(-0.5f, 0.675f), Vec2(TW("Play"), CH), "Play", BLACK, false, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("r", Vec2(-0.5f, 0.475f), Vec2(TW("Resume"), CH), "Resume", BLACK, false, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("p", Vec2(-0.5f, 0.275f), Vec2(TW("Pause"), CH), "Pause", BLACK, false, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("s", Vec2(-0.5f, 0.075f), Vec2(TW("Stop"), CH), "Stop", BLACK, false, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("esc", Vec2(-0.5f, -0.125f), Vec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: sceneEditorControls
	rightWindow->createScreen("sceneEditorControls");
	rightWindow->getScreen("sceneEditorControls")->createRectangle("mouseLeft", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("mouse", Vec2(-1.1f, 0.05f), Vec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("h", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("f", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("b", Vec2(-0.975f, -0.55f), Vec2(0.45f, 0.15f), "b.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("w", Vec2(-0.975f, -0.75f), Vec2(0.45f, 0.15f), "w.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("a", Vec2(-0.475f, -0.75f), Vec2(0.45f, 0.15f), "a.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("s", Vec2(0.025f, -0.75f), Vec2(0.45f, 0.15f), "s.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("d", Vec2(0.525f, -0.75f), Vec2(0.45f, 0.15f), "d.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("space", Vec2(-0.975f, -0.95f), Vec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("sceneEditorControls")->createRectangle("shift", Vec2(-0.475f, -0.95f), Vec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("mouseLeft", Vec2(-0.5f, 0.675f), Vec2(TW("Place"), CH), "Place", BLACK, false, false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("mouseMiddle", Vec2(-0.5f, 0.475f), Vec2(TW("Cancel"), CH), "Cancel", BLACK, false, false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("mouseRight", Vec2(-0.5f, 0.275f), Vec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("mouse", Vec2(-0.5f, 0.075f), Vec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("h", Vec2(-0.5f, -0.125f), Vec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("f", Vec2(-0.5f, -0.325f), Vec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("b", Vec2(-0.5f, -0.525f), Vec2(TW("Toggle AABB"), CH), "Toggle AABB", BLACK, false, false);
	rightWindow->getScreen("sceneEditorControls")->createTextField("wasd", Vec2(0.025f, -0.925f), Vec2(TW("Movement"), CH), "Movement", BLACK, false, false);

	// Right-viewport: scriptEditorControls
	rightWindow->createScreen("scriptEditorControls");
	rightWindow->getScreen("scriptEditorControls")->createRectangle("mouseLeft", Vec2(-1.1f, 0.65f), Vec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("mouseRight", Vec2(-1.1f, 0.45f), Vec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("mouseMiddle", Vec2(-1.1f, 0.25f), Vec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("enter", Vec2(-0.975f, 0.05f), Vec2(0.45f, 0.15f), "enter.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("backspace", Vec2(-0.975f, -0.15f), Vec2(0.45f, 0.15f), "backspace.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("left", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "left.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("right", Vec2(-0.475f, -0.35f), Vec2(0.45f, 0.15f), "right.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("up", Vec2(0.025f, -0.35f), Vec2(0.45f, 0.15f), "up.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("down", Vec2(0.525f, -0.35f), Vec2(0.45f, 0.15f), "down.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("ctrlC", Vec2(-0.975f, -0.65f), Vec2(0.45f, 0.15f), "ctrl.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("c", Vec2(-0.475f, -0.65f), Vec2(0.45f, 0.15f), "c.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("ctrlV", Vec2(-0.975f, -0.825f), Vec2(0.45f, 0.15f), "ctrl.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("v", Vec2(-0.475f, -0.825f), Vec2(0.45f, 0.15f), "v.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("esc", Vec2(-0.975f, -0.35f), Vec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("title", Vec2(0.0f, 0.9f), Vec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("mouseLeft", Vec2(-0.5f, 0.675f), Vec2(TW("Place Cursor"), CH), "Place Cursor", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("mouseRight", Vec2(-0.5f, 0.475f), Vec2(TW("Select Line"), CH), "Select Line", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("enter", Vec2(-0.5f, 0.275f), Vec2(TW("Next Line"), CH), "Next Line", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("backspace", Vec2(-0.5f, 0.075f), Vec2(TW("Remove Char"), CH), "Remove Char", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("esc", Vec2(-0.5f, -0.125f), Vec2(TW("Back"), CH), "Back", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("arrows", Vec2(-0.525f, -0.47f), Vec2(TW("Navigation"), CH), "Navigation", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("ctrlC", Vec2(0.0f, -0.625f), Vec2(TW("Copy"), CH), "Copy", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("ctrlV", Vec2(0.0f, -0.8f), Vec2(TW("Paste"), CH), "Paste", BLACK, false, false);

	// Default screen
	rightWindow->setActiveScreen("mainMenuControls");
}

void RightViewportController::update()
{

}