#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "captor_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void CaptorEditor::_load()
{
	_fe3d->model_create(GRID_ID, GRID_MESH_PATH);
	_fe3d->model_setBaseSize(GRID_ID, fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap(GRID_ID, "", GRID_TEXTURE_PATH);
	_fe3d->model_setTextureRepeat(GRID_ID, "", GRID_REPEAT);
	_fe3d->model_setMinAlpha(GRID_ID, "", GRID_MIN_ALPHA);
	_fe3d->model_setLightness(GRID_ID, "", GRID_LIGHTNESS);
	_fe3d->model_setShadowed(GRID_ID, false);
	_fe3d->model_create(BOX_ID, BOX_MESH_PATH);
	_fe3d->model_setDiffuseMap(BOX_ID, "", BOX_TEXTURE_PATH);
	_fe3d->model_setFaceCulled(BOX_ID, "", true);
	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingIntensity(AMBIENT_LIGHTING_INTENSITY);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingPosition(DIRECTIONAL_LIGHTING_POSITION);
	_fe3d->graphics_setDirectionalLightingIntensity(DIRECTIONAL_LIGHTING_INTENSITY);
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(SHADOW_LIGHTNESS);
	_fe3d->graphics_setShadowQuality(SHADOW_QUALITY);
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE * 0.5f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE * 0.5f)));
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField(CAPTOR_TITLE_ID, CAPTOR_TITLE_POSITION, CAPTOR_TITLE_SIZE, "", fvec3(1.0f), true);
}

void CaptorEditor::_unload()
{
	for(const auto & captorId : _loadedCaptorIds)
	{
		_fe3d->captor_delete(captorId);
	}

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(BOX_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(CAPTOR_TITLE_ID);

	_loadedCaptorIds.clear();
}

void CaptorEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("captorEditorMenuMain");
	rightWindow->getScreen("captorEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("captorEditorMenuChoice");
	rightWindow->getScreen("captorEditorMenuChoice")->createButton("reflectionQuality", fvec2(0.0f, POSITIONS(3)[0]), TEXT_SIZE("Reflect Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflect Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuChoice")->createButton("refractionQuality", fvec2(0.0f, POSITIONS(3)[1]), TEXT_SIZE("Refract Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refract Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(3)[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("captorEditorMenuMain");
}

void CaptorEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("captorEditorMenuMain");
	leftWindow->deleteScreen("captorEditorMenuChoice");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void CaptorEditor::update()
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
		_updateCaptorCreating();
	}

	if(isLoaded())
	{
		_updateCaptorChoosing();
	}

	if(isLoaded())
	{
		_updateCaptorDeleting();
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