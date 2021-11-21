#include "right_viewport_controller.hpp"

#define TW(text) calculateTextWidth(text, CW)

using RVPC = RightViewportController;

void RightViewportController::initialize()
{
	// Window
	_gui.getViewport("right")->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), RightViewportController::FRAME_COLOR);
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Right-viewport: mainMenuControls
	rightWindow->createScreen("mainMenuControls");
	rightWindow->getScreen("mainMenuControls")->createRectangle("mouse", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("mainMenuControls")->createRectangle("mouseLeft", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->getScreen("mainMenuControls")->createRectangle("esc", fvec2(-0.975f, 0.25f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("mainMenuControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("General Controls"), CH), "General Controls", WHITE, true, false);
	rightWindow->getScreen("mainMenuControls")->createTextField("mouse", fvec2(-0.5f, 0.675f), fvec2(TW("Move Cursor"), CH), "Move Cursor", BLACK, false, false);
	rightWindow->getScreen("mainMenuControls")->createTextField("mouseLeft", fvec2(-0.5f, 0.475f), fvec2(TW("Confirm"), CH), "Confirm", BLACK, false, false);
	rightWindow->getScreen("mainMenuControls")->createTextField("esc", fvec2(-0.5f, 0.275f), fvec2(TW("Exit"), CH), "Exit", BLACK, false, false);

	// Right-viewport: skyEditorControls
	rightWindow->createScreen("skyEditorControls");
	rightWindow->getScreen("skyEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("h", fvec2(-0.975f, 0.25f), fvec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("f", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("skyEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("skyEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.475f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("h", fvec2(-0.5f, 0.275f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("f", fvec2(-0.5f, 0.075f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("skyEditorControls")->createTextField("esc", fvec2(-0.5f, -0.125f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: terrainEditorControls
	rightWindow->createScreen("terrainEditorControls");
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("terrainEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("terrainEditorControls")->createTextField("esc", fvec2(-0.5f, -0.525f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: waterEditorControls
	rightWindow->createScreen("waterEditorControls");
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("waterEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("waterEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("waterEditorControls")->createTextField("esc", fvec2(-0.5f, -0.525f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: modelEditorControls
	rightWindow->createScreen("modelEditorControls");
	rightWindow->getScreen("modelEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("space", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("shift", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("modelEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("modelEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("space", fvec2(-0.5f, -0.525f), fvec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("shift", fvec2(-0.5f, -0.725f), fvec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	rightWindow->getScreen("modelEditorControls")->createTextField("esc", fvec2(-0.5f, -0.925f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: animationEditorControls
	rightWindow->createScreen("animationEditorControls");
	rightWindow->getScreen("animationEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("space", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("shift", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("animationEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("animationEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("space", fvec2(-0.5f, -0.525f), fvec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("shift", fvec2(-0.5f, -0.725f), fvec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	rightWindow->getScreen("animationEditorControls")->createTextField("esc", fvec2(-0.5f, -0.925f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: billboardEditorControls
	rightWindow->createScreen("billboardEditorControls");
	rightWindow->getScreen("billboardEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("space", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("shift", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("billboardEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("space", fvec2(-0.5f, -0.525f), fvec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("shift", fvec2(-0.5f, -0.725f), fvec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	rightWindow->getScreen("billboardEditorControls")->createTextField("esc", fvec2(-0.5f, -0.925f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: audioEditorControls
	rightWindow->createScreen("audioEditorControls");
	rightWindow->getScreen("audioEditorControls")->createRectangle("space", fvec2(-0.975f, 0.65f), fvec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("r", fvec2(-0.975f, 0.45f), fvec2(0.45f, 0.15f), "r.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("p", fvec2(-0.975f, 0.25f), fvec2(0.45f, 0.15f), "p.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("s", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "s.png", false);
	rightWindow->getScreen("audioEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("audioEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("space", fvec2(-0.5f, 0.675f), fvec2(TW("Play"), CH), "Play", BLACK, false, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("r", fvec2(-0.5f, 0.475f), fvec2(TW("Resume"), CH), "Resume", BLACK, false, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("p", fvec2(-0.5f, 0.275f), fvec2(TW("Pause"), CH), "Pause", BLACK, false, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("s", fvec2(-0.5f, 0.075f), fvec2(TW("Stop"), CH), "Stop", BLACK, false, false);
	rightWindow->getScreen("audioEditorControls")->createTextField("esc", fvec2(-0.5f, -0.125f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: worldEditorControls
	rightWindow->createScreen("worldEditorControls");
	rightWindow->getScreen("worldEditorControls")->createRectangle("mouseLeft", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.05f), fvec2(0.6f, 0.15f), "mouse.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("h", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "h.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("b", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "b.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("w", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "w.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("a", fvec2(-0.475f, -0.75f), fvec2(0.45f, 0.15f), "a.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("s", fvec2(0.025f, -0.75f), fvec2(0.45f, 0.15f), "s.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("d", fvec2(0.525f, -0.75f), fvec2(0.45f, 0.15f), "d.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("space", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "space.png", false);
	rightWindow->getScreen("worldEditorControls")->createRectangle("shift", fvec2(-0.475f, -0.95f), fvec2(0.45f, 0.15f), "shift.png", false);
	rightWindow->getScreen("worldEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("worldEditorControls")->createTextField("mouseLeft", fvec2(-0.5f, 0.675f), fvec2(TW("Place"), CH), "Place", BLACK, false, false);
	rightWindow->getScreen("worldEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Cancel"), CH), "Cancel", BLACK, false, false);
	rightWindow->getScreen("worldEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.275f), fvec2(TW("Enable Camera"), CH), "Enable Camera", BLACK, false, false);
	rightWindow->getScreen("worldEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.075f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	rightWindow->getScreen("worldEditorControls")->createTextField("h", fvec2(-0.5f, -0.125f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	rightWindow->getScreen("worldEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	rightWindow->getScreen("worldEditorControls")->createTextField("b", fvec2(-0.5f, -0.525f), fvec2(TW("Toggle AABB"), CH), "Toggle AABB", BLACK, false, false);
	rightWindow->getScreen("worldEditorControls")->createTextField("wasd", fvec2(0.025f, -0.925f), fvec2(TW("Movement"), CH), "Movement", BLACK, false, false);

	// Right-viewport: scriptEditorControls
	rightWindow->createScreen("scriptEditorControls");
	rightWindow->getScreen("scriptEditorControls")->createRectangle("mouseLeft", fvec2(-1.1f, 0.7f), fvec2(0.6f, 0.15f), "mouse_left.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.5f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.3f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("enter", fvec2(-0.975f, 0.1f), fvec2(0.45f, 0.15f), "enter.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("backspace", fvec2(-0.975f, -0.1f), fvec2(0.45f, 0.15f), "backspace.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("left", fvec2(-0.975f, -0.3f), fvec2(0.45f, 0.15f), "left.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("right", fvec2(-0.475f, -0.3f), fvec2(0.45f, 0.15f), "right.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("up", fvec2(0.025f, -0.3f), fvec2(0.45f, 0.15f), "up.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("down", fvec2(0.525f, -0.3f), fvec2(0.45f, 0.15f), "down.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("ctrlC", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "ctrl.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("c", fvec2(-0.475f, -0.55f), fvec2(0.45f, 0.15f), "c.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("ctrlV", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "ctrl.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("v", fvec2(-0.475f, -0.75f), fvec2(0.45f, 0.15f), "v.png", false);
	rightWindow->getScreen("scriptEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "esc.png", false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("mouseLeft", fvec2(-0.5f, 0.725f), fvec2(TW("Place Cursor"), CH), "Place Cursor", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.525f), fvec2(TW("Select Line"), CH), "Select Line", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.325f), fvec2(TW("Scroll Lines"), CH), "Scroll Lines", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("enter", fvec2(-0.5f, 0.125f), fvec2(TW("Next Line"), CH), "Next Line", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("backspace", fvec2(-0.5f, -0.075f), fvec2(TW("Remove Char"), CH), "Remove Char", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("arrows", fvec2(-0.525f, -0.4f), fvec2(TW("Navigation"), CH), "Navigation", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("ctrlC", fvec2(0.0f, -0.525f), fvec2(TW("Copy"), CH), "Copy", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("ctrlV", fvec2(0.0f, -0.725f), fvec2(TW("Paste"), CH), "Paste", BLACK, false, false);
	rightWindow->getScreen("scriptEditorControls")->createTextField("esc", fvec2(-0.5f, -0.925f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Default screen
	rightWindow->setActiveScreen("mainMenuControls");
}

void RightViewportController::update()
{

}