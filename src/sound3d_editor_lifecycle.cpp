#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "sound3d_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Sound3dEditor::_load()
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
	_fe3d->model_create(SPEAKER_ID, SPEAKER_MESH_PATH);
	_fe3d->model_setBasePosition(SPEAKER_ID, SPEAKER_POSITION);
	_fe3d->model_setBaseSize(SPEAKER_ID, SPEAKER_SIZE);
	_fe3d->model_setShadowed(SPEAKER_ID, false);
	_fe3d->model_setBright(SPEAKER_ID, "", true);
	_fe3d->model_setVisible(SPEAKER_ID, false);
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
	_fe3d->graphics_setShadowPcfCount(SHADOW_PCF_COUNT);
	_fe3d->graphics_setShadowBias(SHADOW_BIAS);
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE * 0.5f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE * 0.5f)));
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField(SOUND3D_TITLE_ID, SOUND3D_TITLE_POSITION, SOUND3D_TITLE_SIZE, "", fvec3(1.0f), true);
}

void Sound3dEditor::_unload()
{
	for(const auto & sound3dId : _loadedSound3dIds)
	{
		_fe3d->sound3d_delete(sound3dId);
	}

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(BOX_ID);
	_fe3d->model_delete(SPEAKER_ID);
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

	_gui->getOverlay()->deleteTextField(SOUND3D_TITLE_ID);

	_loadedSound3dIds.clear();
}

void Sound3dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("sound3dEditorMenuMain");
	rightWindow->getScreen("sound3dEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Sound3d"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Sound3d", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Sound3d"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sound3d", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Sound3d"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sound3d", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("sound3dEditorMenuChoice");
	rightWindow->getScreen("sound3dEditorMenuChoice")->createButton("maxVolume", fvec2(0.0f, POSITIONS(3)[0]), TEXT_SIZE("Max Volume"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Volume", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuChoice")->createButton("maxDistance", fvec2(0.0f, POSITIONS(3)[1]), TEXT_SIZE("Max Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(3)[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("sound3dEditorMenuMain");
}

void Sound3dEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->deleteScreen("sound3dEditorMenuMain");
	rightWindow->deleteScreen("sound3dEditorMenuChoice");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void Sound3dEditor::update()
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
		_updateSound3dCreating();
	}

	if(isLoaded())
	{
		_updateSound3dChoosing();
	}

	if(isLoaded())
	{
		_updateSound3dDeleting();
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