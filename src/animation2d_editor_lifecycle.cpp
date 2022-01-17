#define TW(text) VPC::calculateTextWidth(text, CW)

#include "animation2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

void Animation2dEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_fe3d->gfx_enableAntiAliasing();

	_fe3d->quad3d_create(PREVIEW_BILLBOARD_ID, true);
	_fe3d->quad3d_setPosition(PREVIEW_BILLBOARD_ID, PREVIEW_BILLBOARD_POSITION);
	_fe3d->quad3d_setVisible(PREVIEW_BILLBOARD_ID, false);

	_gui->getOverlay()->createTextField("animationID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);

	_isEditorLoaded = true;
}

void Animation2dEditor::unload()
{
	_unloadGUI();

	_fe3d->gfx_disableAntiAliasing(true);

	_fe3d->quad3d_delete(PREVIEW_BILLBOARD_ID);

	_gui->getOverlay()->deleteTextField("animationID");

	_animations.clear();
	_startedBillboardAnimations.clear();
	_startedQuad2dAnimations.clear();
	_billboardAnimationsToStop.clear();
	_billboardAnimationsToStart.clear();
	_quad2dAnimationsToStop.clear();
	_quad2dAnimationsToStart.clear();
	_hoveredAnimationID = "";
	_currentAnimationID = "";
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isDeletingAnimation = false;
	_isEditorLoaded = false;
}

void Animation2dEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("animation2dEditorMenuMain");
	leftWindow->getScreen("animation2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("animation2dEditorMenuChoice");
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("preview", fvec2(0.0f, positions[0]), fvec2(TW("Preview Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Preview Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("rows", fvec2(0.0f, positions[1]), fvec2(TW("Rows"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("columns", fvec2(0.0f, positions[2]), fvec2(TW("Columns"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Columns", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("framestep", fvec2(0.0f, positions[3]), fvec2(TW("Framestep"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Framestep", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("start", fvec2(-0.5f, positions[4]), fvec2(TW("Start"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Start", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("stop", fvec2(0.5f, positions[4]), fvec2(TW("Stop"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
}

void Animation2dEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("animation2dEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("animation2dEditorMenuChoice");
}

void Animation2dEditor::update()
{
	_updateBillboardAnimationExecution();
	_updateQuad2dAnimationExecution();

	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateAnimationCreating();
	}
	if(_isEditorLoaded)
	{
		_updateAnimationChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateAnimationDeleting();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}