#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "sky_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void SkyEditor::_load()
{
	_fe3d->camera_reset();
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);

	_fe3d->gfx_setMotionBlurEnabled(true);
	_fe3d->gfx_setMotionBlurIntensity(0.1f);
	_fe3d->gfx_setMotionBlurQuality(Config::MAX_MOTION_BLUR_QUALITY);

	_gui->getOverlay()->createTextField("skyId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);
}

void SkyEditor::_unload()
{
	for(const auto& id : _loadedSkyIds)
	{
		_fe3d->sky_delete(id);
	}

	_fe3d->gfx_setMotionBlurEnabled(false);
	_fe3d->gfx_setMotionBlurIntensity(0.0f);
	_fe3d->gfx_setMotionBlurQuality(Config::MIN_MOTION_BLUR_QUALITY);

	_gui->getOverlay()->deleteTextField("skyId");

	_fe3d->camera_setThirdPersonEnabled(false);

	_loadedSkyIds.clear();
	_currentSkyId = "";
	_isCreatingSky = false;
	_isChoosingSky = false;
	_isDeletingSky = false;
}

void SkyEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuMain");
	leftWindow->getScreen("skyEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Sky"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Sky"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Sky"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("skyEditorMenuChoice");
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("texturing", fvec2(0.0f, positions[0]), TEXT_SIZE("Texturing"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[1]), TEXT_SIZE("Miscellaneous"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(8, CH);
	leftWindow->createScreen("skyEditorMenuTexturing");
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("leftMap", fvec2(0.0f, positions[0]), TEXT_SIZE("Left Map"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Left Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("rightMap", fvec2(0.0f, positions[1]), TEXT_SIZE("Right Map"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Right Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("bottomMap", fvec2(0.0f, positions[2]), TEXT_SIZE("Bottom Map"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bottom Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("topMap", fvec2(0.0f, positions[3]), TEXT_SIZE("Top Map"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Top Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("backMap", fvec2(0.0f, positions[4]), TEXT_SIZE("Back Map"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Back Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("frontMap", fvec2(0.0f, positions[5]), TEXT_SIZE("Front Map"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Front Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, positions[6]), TEXT_SIZE("Clear Maps"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("back", fvec2(0.0f, positions[7]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuMiscellaneous");
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("rotation", fvec2(0.0f, positions[0]), TEXT_SIZE("Rotation"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("lightness", fvec2(0.0f, positions[1]), TEXT_SIZE("Lightness"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("color", fvec2(0.0f, positions[2]), TEXT_SIZE("Color"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void SkyEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("skyEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("skyEditorMenuChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("skyEditorMenuTexturing");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("skyEditorMenuMiscellaneous");
}

void SkyEditor::update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}
	if(isLoaded())
	{
		_updateChoiceMenu();
	}
	if(isLoaded())
	{
		_updateTexturingMenu();
	}
	if(isLoaded())
	{
		_updateMiscellaneousMenu();
	}
	if(isLoaded())
	{
		_updateSkyCreating();
	}
	if(isLoaded())
	{
		_updateSkyChoosing();
	}
	if(isLoaded())
	{
		_updateSkyDeleting();
	}
	if(isLoaded())
	{
		_updateCamera();
	}
	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}