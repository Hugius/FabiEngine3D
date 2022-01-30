#define TW(text) (static_cast<float>(string(text).size()) * CW)

#include "sky_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void SkyEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);

	_fe3d->gfx_enableMotionBlur();
	_fe3d->gfx_setMotionBlurIntensity(0.1f);
	_fe3d->gfx_setMotionBlurQuality(Config::MAX_MOTION_BLUR_QUALITY);

	_gui->getOverlay()->createTextField("skyId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_isEditorLoaded = true;
}

void SkyEditor::unload()
{
	for(const auto& id : _loadedSkyIds)
	{
		_fe3d->sky_delete(id);
	}

	_unloadGUI();

	_fe3d->gfx_disableMotionBlur(true);

	_gui->getOverlay()->deleteTextField("skyId");

	_loadedSkyIds.clear();
	_currentSkyId = "";
	_isEditorLoaded = false;
	_isCreatingSky = false;
	_isChoosingSky = false;
	_isDeletingSky = false;

	if(_fe3d->camera_isThirdPersonViewEnabled())
	{
		_fe3d->camera_disableThirdPersonView();
	}
}

void SkyEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuMain");
	leftWindow->getScreen("skyEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Sky"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Sky"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Sky"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sky", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(3, CH);
	leftWindow->createScreen("skyEditorMenuChoice");
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("texturing", fvec2(0.0f, positions[0]), fvec2(TW("Texturing"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texturing", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[1]), fvec2(TW("Miscellaneous"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Miscellaneous", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(8, CH);
	leftWindow->createScreen("skyEditorMenuTexturing");
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("leftMap", fvec2(0.0f, positions[0]), fvec2(TW("Left Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Left Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("rightMap", fvec2(0.0f, positions[1]), fvec2(TW("Right Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Right Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("bottomMap", fvec2(0.0f, positions[2]), fvec2(TW("Bottom Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Bottom Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("topMap", fvec2(0.0f, positions[3]), fvec2(TW("Top Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Top Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("backMap", fvec2(0.0f, positions[4]), fvec2(TW("Back Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Back Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("frontMap", fvec2(0.0f, positions[5]), fvec2(TW("Front Map"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Front Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, positions[6]), fvec2(TW("Clear Maps"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Maps", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuTexturing")->createButton("back", fvec2(0.0f, positions[7]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuMiscellaneous");
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("rotation", fvec2(0.0f, positions[0]), fvec2(TW("Rotation"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("lightness", fvec2(0.0f, positions[1]), fvec2(TW("Lightness"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Lightness", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("color", fvec2(0.0f, positions[2]), fvec2(TW("Color"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("skyEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
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
		_updateTexturingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneousMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSkyCreating();
	}
	if(_isEditorLoaded)
	{
		_updateSkyChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateSkyDeleting();
	}
	if(_isEditorLoaded)
	{
		_updateCamera();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}