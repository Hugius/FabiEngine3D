#include "right_viewport_controller.hpp"

#define TW(text) calculateTextWidth(text, CW)

using RVPC = RightViewportController;

void RightViewportController::initialize()
{
	// Window
	_gui.getViewport("right")->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), RightViewportController::FRAME_COLOR);
	auto window = _gui.getViewport("right")->getWindow("main");

	// Right-viewport: mainMenuControls
	window->createScreen("mainMenuControls");
	window->getScreen("mainMenuControls")->createRectangle("mouse", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse.png", false);
	window->getScreen("mainMenuControls")->createRectangle("mouseLeft", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_left.png", false);
	window->getScreen("mainMenuControls")->createRectangle("esc", fvec2(-0.975f, 0.25f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("mainMenuControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("General Controls"), CH), "General Controls", WHITE, true, false);
	window->getScreen("mainMenuControls")->createTextField("mouse", fvec2(-0.5f, 0.675f), fvec2(TW("Move Cursor"), CH), "Move Cursor", BLACK, false, false);
	window->getScreen("mainMenuControls")->createTextField("mouseLeft", fvec2(-0.5f, 0.475f), fvec2(TW("Confirm"), CH), "Confirm", BLACK, false, false);
	window->getScreen("mainMenuControls")->createTextField("esc", fvec2(-0.5f, 0.275f), fvec2(TW("Exit"), CH), "Exit", BLACK, false, false);

	// Right-viewport: skyEditorControls
	window->createScreen("skyEditorControls");
	window->getScreen("skyEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	window->getScreen("skyEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse.png", false);
	window->getScreen("skyEditorControls")->createRectangle("h", fvec2(-0.975f, 0.25f), fvec2(0.45f, 0.15f), "h.png", false);
	window->getScreen("skyEditorControls")->createRectangle("f", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "f.png", false);
	window->getScreen("skyEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("skyEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("skyEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	window->getScreen("skyEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.475f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	window->getScreen("skyEditorControls")->createTextField("h", fvec2(-0.5f, 0.275f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	window->getScreen("skyEditorControls")->createTextField("f", fvec2(-0.5f, 0.075f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	window->getScreen("skyEditorControls")->createTextField("esc", fvec2(-0.5f, -0.125f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: terrainEditorControls
	window->createScreen("terrainEditorControls");
	window->getScreen("terrainEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	window->getScreen("terrainEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	window->getScreen("terrainEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	window->getScreen("terrainEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	window->getScreen("terrainEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	window->getScreen("terrainEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	window->getScreen("terrainEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("terrainEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("terrainEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	window->getScreen("terrainEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	window->getScreen("terrainEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	window->getScreen("terrainEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	window->getScreen("terrainEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	window->getScreen("terrainEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	window->getScreen("terrainEditorControls")->createTextField("esc", fvec2(-0.5f, -0.525f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: waterEditorControls
	window->createScreen("waterEditorControls");
	window->getScreen("waterEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	window->getScreen("waterEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	window->getScreen("waterEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	window->getScreen("waterEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	window->getScreen("waterEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	window->getScreen("waterEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	window->getScreen("waterEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("waterEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("waterEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	window->getScreen("waterEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	window->getScreen("waterEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	window->getScreen("waterEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	window->getScreen("waterEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	window->getScreen("waterEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	window->getScreen("waterEditorControls")->createTextField("esc", fvec2(-0.5f, -0.525f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: modelEditorControls
	window->createScreen("modelEditorControls");
	window->getScreen("modelEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	window->getScreen("modelEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	window->getScreen("modelEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	window->getScreen("modelEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	window->getScreen("modelEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	window->getScreen("modelEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	window->getScreen("modelEditorControls")->createRectangle("space", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "space.png", false);
	window->getScreen("modelEditorControls")->createRectangle("shift", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "shift.png", false);
	window->getScreen("modelEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("modelEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("modelEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	window->getScreen("modelEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	window->getScreen("modelEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	window->getScreen("modelEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	window->getScreen("modelEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	window->getScreen("modelEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	window->getScreen("modelEditorControls")->createTextField("space", fvec2(-0.5f, -0.525f), fvec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	window->getScreen("modelEditorControls")->createTextField("shift", fvec2(-0.5f, -0.725f), fvec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	window->getScreen("modelEditorControls")->createTextField("esc", fvec2(-0.5f, -0.925f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: animationEditorControls
	window->createScreen("animationEditorControls");
	window->getScreen("animationEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	window->getScreen("animationEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	window->getScreen("animationEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	window->getScreen("animationEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	window->getScreen("animationEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	window->getScreen("animationEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	window->getScreen("animationEditorControls")->createRectangle("space", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "space.png", false);
	window->getScreen("animationEditorControls")->createRectangle("shift", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "shift.png", false);
	window->getScreen("animationEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("animationEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("animationEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	window->getScreen("animationEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	window->getScreen("animationEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	window->getScreen("animationEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	window->getScreen("animationEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	window->getScreen("animationEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	window->getScreen("animationEditorControls")->createTextField("space", fvec2(-0.5f, -0.525f), fvec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	window->getScreen("animationEditorControls")->createTextField("shift", fvec2(-0.5f, -0.725f), fvec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	window->getScreen("animationEditorControls")->createTextField("esc", fvec2(-0.5f, -0.925f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: billboardEditorControls
	window->createScreen("billboardEditorControls");
	window->getScreen("billboardEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	window->getScreen("billboardEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	window->getScreen("billboardEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse.png", false);
	window->getScreen("billboardEditorControls")->createRectangle("h", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "h.png", false);
	window->getScreen("billboardEditorControls")->createRectangle("r", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "r.png", false);
	window->getScreen("billboardEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	window->getScreen("billboardEditorControls")->createRectangle("space", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "space.png", false);
	window->getScreen("billboardEditorControls")->createRectangle("shift", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "shift.png", false);
	window->getScreen("billboardEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("billboardEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("billboardEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.675f), fvec2(TW("Toggle Camera"), CH), "Toggle Camera", BLACK, false, false);
	window->getScreen("billboardEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Zoom Camera"), CH), "Zoom Camera", BLACK, false, false);
	window->getScreen("billboardEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.275f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	window->getScreen("billboardEditorControls")->createTextField("h", fvec2(-0.5f, 0.075f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	window->getScreen("billboardEditorControls")->createTextField("r", fvec2(-0.5f, -0.125f), fvec2(TW("Reference Box"), CH), "Reference Box", BLACK, false, false);
	window->getScreen("billboardEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	window->getScreen("billboardEditorControls")->createTextField("space", fvec2(-0.5f, -0.525f), fvec2(TW("Move Up"), CH), "Move Up", BLACK, false, false);
	window->getScreen("billboardEditorControls")->createTextField("shift", fvec2(-0.5f, -0.725f), fvec2(TW("Move Down"), CH), "Move Down", BLACK, false, false);
	window->getScreen("billboardEditorControls")->createTextField("esc", fvec2(-0.5f, -0.925f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: audioEditorControls
	window->createScreen("audioEditorControls");
	window->getScreen("audioEditorControls")->createRectangle("space", fvec2(-0.975f, 0.65f), fvec2(0.45f, 0.15f), "space.png", false);
	window->getScreen("audioEditorControls")->createRectangle("r", fvec2(-0.975f, 0.45f), fvec2(0.45f, 0.15f), "r.png", false);
	window->getScreen("audioEditorControls")->createRectangle("p", fvec2(-0.975f, 0.25f), fvec2(0.45f, 0.15f), "p.png", false);
	window->getScreen("audioEditorControls")->createRectangle("s", fvec2(-0.975f, 0.05f), fvec2(0.45f, 0.15f), "s.png", false);
	window->getScreen("audioEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("audioEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("audioEditorControls")->createTextField("space", fvec2(-0.5f, 0.675f), fvec2(TW("Play"), CH), "Play", BLACK, false, false);
	window->getScreen("audioEditorControls")->createTextField("r", fvec2(-0.5f, 0.475f), fvec2(TW("Resume"), CH), "Resume", BLACK, false, false);
	window->getScreen("audioEditorControls")->createTextField("p", fvec2(-0.5f, 0.275f), fvec2(TW("Pause"), CH), "Pause", BLACK, false, false);
	window->getScreen("audioEditorControls")->createTextField("s", fvec2(-0.5f, 0.075f), fvec2(TW("Stop"), CH), "Stop", BLACK, false, false);
	window->getScreen("audioEditorControls")->createTextField("esc", fvec2(-0.5f, -0.125f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Right-viewport: worldEditorControls
	window->createScreen("worldEditorControls");
	window->getScreen("worldEditorControls")->createRectangle("mouseLeft", fvec2(-1.1f, 0.65f), fvec2(0.6f, 0.15f), "mouse_left.png", false);
	window->getScreen("worldEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.45f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	window->getScreen("worldEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.25f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	window->getScreen("worldEditorControls")->createRectangle("mouse", fvec2(-1.1f, 0.05f), fvec2(0.6f, 0.15f), "mouse.png", false);
	window->getScreen("worldEditorControls")->createRectangle("h", fvec2(-0.975f, -0.15f), fvec2(0.45f, 0.15f), "h.png", false);
	window->getScreen("worldEditorControls")->createRectangle("f", fvec2(-0.975f, -0.35f), fvec2(0.45f, 0.15f), "f.png", false);
	window->getScreen("worldEditorControls")->createRectangle("b", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "b.png", false);
	window->getScreen("worldEditorControls")->createRectangle("w", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "w.png", false);
	window->getScreen("worldEditorControls")->createRectangle("a", fvec2(-0.475f, -0.75f), fvec2(0.45f, 0.15f), "a.png", false);
	window->getScreen("worldEditorControls")->createRectangle("s", fvec2(0.025f, -0.75f), fvec2(0.45f, 0.15f), "s.png", false);
	window->getScreen("worldEditorControls")->createRectangle("d", fvec2(0.525f, -0.75f), fvec2(0.45f, 0.15f), "d.png", false);
	window->getScreen("worldEditorControls")->createRectangle("space", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "space.png", false);
	window->getScreen("worldEditorControls")->createRectangle("shift", fvec2(-0.475f, -0.95f), fvec2(0.45f, 0.15f), "shift.png", false);
	window->getScreen("worldEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("worldEditorControls")->createTextField("mouseLeft", fvec2(-0.5f, 0.675f), fvec2(TW("Place"), CH), "Place", BLACK, false, false);
	window->getScreen("worldEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.475f), fvec2(TW("Cancel"), CH), "Cancel", BLACK, false, false);
	window->getScreen("worldEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.275f), fvec2(TW("Enable Camera"), CH), "Enable Camera", BLACK, false, false);
	window->getScreen("worldEditorControls")->createTextField("mouse", fvec2(-0.5f, 0.075f), fvec2(TW("Move Camera"), CH), "Move Camera", BLACK, false, false);
	window->getScreen("worldEditorControls")->createTextField("h", fvec2(-0.5f, -0.125f), fvec2(TW("Debug Render"), CH), "Debug Render", BLACK, false, false);
	window->getScreen("worldEditorControls")->createTextField("f", fvec2(-0.5f, -0.325f), fvec2(TW("Wireframe"), CH), "Wireframe", BLACK, false, false);
	window->getScreen("worldEditorControls")->createTextField("b", fvec2(-0.5f, -0.525f), fvec2(TW("Toggle AABB"), CH), "Toggle AABB", BLACK, false, false);
	window->getScreen("worldEditorControls")->createTextField("wasd", fvec2(0.025f, -0.925f), fvec2(TW("Movement"), CH), "Movement", BLACK, false, false);

	// Right-viewport: scriptEditorControls
	window->createScreen("scriptEditorControls");
	window->getScreen("scriptEditorControls")->createRectangle("mouseLeft", fvec2(-1.1f, 0.7f), fvec2(0.6f, 0.15f), "mouse_left.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("mouseRight", fvec2(-1.1f, 0.5f), fvec2(0.6f, 0.15f), "mouse_right.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("mouseMiddle", fvec2(-1.1f, 0.3f), fvec2(0.6f, 0.15f), "mouse_middle.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("enter", fvec2(-0.975f, 0.1f), fvec2(0.45f, 0.15f), "enter.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("backspace", fvec2(-0.975f, -0.1f), fvec2(0.45f, 0.15f), "backspace.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("left", fvec2(-0.975f, -0.3f), fvec2(0.45f, 0.15f), "left.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("right", fvec2(-0.475f, -0.3f), fvec2(0.45f, 0.15f), "right.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("up", fvec2(0.025f, -0.3f), fvec2(0.45f, 0.15f), "up.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("down", fvec2(0.525f, -0.3f), fvec2(0.45f, 0.15f), "down.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("ctrlC", fvec2(-0.975f, -0.55f), fvec2(0.45f, 0.15f), "ctrl.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("c", fvec2(-0.475f, -0.55f), fvec2(0.45f, 0.15f), "c.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("ctrlV", fvec2(-0.975f, -0.75f), fvec2(0.45f, 0.15f), "ctrl.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("v", fvec2(-0.475f, -0.75f), fvec2(0.45f, 0.15f), "v.png", false);
	window->getScreen("scriptEditorControls")->createRectangle("esc", fvec2(-0.975f, -0.95f), fvec2(0.45f, 0.15f), "esc.png", false);
	window->getScreen("scriptEditorControls")->createTextField("title", fvec2(0.0f, 0.9f), fvec2(TW("Editor Controls"), CH), "Editor Controls", WHITE, true, false);
	window->getScreen("scriptEditorControls")->createTextField("mouseLeft", fvec2(-0.5f, 0.725f), fvec2(TW("Place Cursor"), CH), "Place Cursor", BLACK, false, false);
	window->getScreen("scriptEditorControls")->createTextField("mouseRight", fvec2(-0.5f, 0.525f), fvec2(TW("Select Line"), CH), "Select Line", BLACK, false, false);
	window->getScreen("scriptEditorControls")->createTextField("mouseMiddle", fvec2(-0.5f, 0.325f), fvec2(TW("Scroll Lines"), CH), "Scroll Lines", BLACK, false, false);
	window->getScreen("scriptEditorControls")->createTextField("enter", fvec2(-0.5f, 0.125f), fvec2(TW("Next Line"), CH), "Next Line", BLACK, false, false);
	window->getScreen("scriptEditorControls")->createTextField("backspace", fvec2(-0.5f, -0.075f), fvec2(TW("Remove Char"), CH), "Remove Char", BLACK, false, false);
	window->getScreen("scriptEditorControls")->createTextField("arrows", fvec2(-0.525f, -0.4f), fvec2(TW("Navigation"), CH), "Navigation", BLACK, false, false);
	window->getScreen("scriptEditorControls")->createTextField("ctrlC", fvec2(0.0f, -0.525f), fvec2(TW("Copy"), CH), "Copy", BLACK, false, false);
	window->getScreen("scriptEditorControls")->createTextField("ctrlV", fvec2(0.0f, -0.725f), fvec2(TW("Paste"), CH), "Paste", BLACK, false, false);
	window->getScreen("scriptEditorControls")->createTextField("esc", fvec2(-0.5f, -0.925f), fvec2(TW("Back"), CH), "Back", BLACK, false, false);

	// Default screen
	window->setActiveScreen("mainMenuControls");
}

void RightViewportController::update()
{

}