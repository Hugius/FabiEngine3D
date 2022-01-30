#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "animation2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Animation2dEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_fe3d->gfx_enableAntiAliasing();

	_fe3d->quad3d_create(PREVIEW_QUAD_ID, true);
	_fe3d->quad3d_setPosition(PREVIEW_QUAD_ID, PREVIEW_QUAD_POSITION);
	_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, false);

	_gui->getOverlay()->createTextField("animationId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_isEditorLoaded = true;
}

void Animation2dEditor::unload()
{
	_unloadGUI();

	_fe3d->gfx_disableAntiAliasing(true);

	_fe3d->quad3d_delete(PREVIEW_QUAD_ID);

	_gui->getOverlay()->deleteTextField("animationId");

	_startedQuad3dAnimations.clear();
	_startedQuad2dAnimations.clear();
	_animations.clear();
	_quad3dAnimationsToStop.clear();
	_quad3dAnimationsToStart.clear();
	_quad2dAnimationsToStop.clear();
	_quad2dAnimationsToStart.clear();
	_hoveredAnimationId = "";
	_currentAnimationId = "";
	_currentProjectId = "";
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isDeletingAnimation = false;
	_isEditorLoaded = false;
}

void Animation2dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("animation2dEditorMenuMain");
	leftWindow->getScreen("animation2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Animation"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Animation"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Animation"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(6, CH);
	leftWindow->createScreen("animation2dEditorMenuChoice");
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("preview", fvec2(0.0f, positions[0]), TEXT_SIZE("Preview Texture"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Preview Texture", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("rowCount", fvec2(0.0f, positions[1]), TEXT_SIZE("Rows"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rows", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("columnCount", fvec2(0.0f, positions[2]), TEXT_SIZE("Columns"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Columns", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("interval", fvec2(0.0f, positions[3]), TEXT_SIZE("Interval"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Interval", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("start", fvec2(-0.5f, positions[4]), TEXT_SIZE("Start"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Start", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("stop", fvec2(0.5f, positions[4]), TEXT_SIZE("Stop"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Stop", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[5]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void Animation2dEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("animation2dEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("animation2dEditorMenuChoice");
}

void Animation2dEditor::update()
{
	_updateQuad3dAnimationExecution();
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