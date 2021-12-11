#include "sprite_animation_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

SpriteAnimationEditor::SpriteAnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void SpriteAnimationEditor::load()
{
	// GUI
	_loadGUI();

	_fe3d.camera_reset();
	_fe3d.camera_setYaw(270.0f);

	// Preview image
	_fe3d.billboard_create(PREVIEW_BILLBOARD_ID);
	_fe3d.billboard_setPosition(PREVIEW_BILLBOARD_ID, PREVIEW_BILLBOARD_POSITION);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("animationID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_isEditorLoaded = true;
}

void SpriteAnimationEditor::unload()
{
	// GUI
	_unloadGUI();

	// Delete billboards
	_fe3d.billboard_deleteAll();

	// Delete textfields
	_gui.getGlobalScreen()->deleteTextField("animationID");

	// Reset editor properties
	_animations.clear();
	_startedAnimations.clear();
	_hoveredAnimationID = "";
	_currentAnimationID = "";
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isDeletingAnimation = false;
	_isEditorLoaded = false;

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if(_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
}

void SpriteAnimationEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: spriteAnimationEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("spriteAnimationEditorMenuMain");
	leftWindow->getScreen("spriteAnimationEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: spriteAnimationEditorMenuChoice
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("spriteAnimationEditorMenuChoice");
	leftWindow->getScreen("spriteAnimationEditorMenuChoice")->createButton("preview", fvec2(0.0f, positions[0]), fvec2(TW("Preview Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Preview Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuChoice")->createButton("rows", fvec2(0.0f, positions[1]), fvec2(TW("Rows"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuChoice")->createButton("columns", fvec2(0.0f, positions[2]), fvec2(TW("Columns"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Columns", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuChoice")->createButton("framestep", fvec2(0.0f, positions[3]), fvec2(TW("Framestep"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Framestep", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuChoice")->createButton("start", fvec2(-0.5f, positions[4]), fvec2(TW("Start"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Start", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuChoice")->createButton("stop", fvec2(0.5f, positions[4]), fvec2(TW("Stop"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("spriteAnimationEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void SpriteAnimationEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("spriteAnimationEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("spriteAnimationEditorMenuChoice");
}