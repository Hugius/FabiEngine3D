#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "sound3d_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Sound3dEditor::_load()
{
	_fe3d->model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d->model_setDiffuseMap("@@box", "", "engine\\assets\\image\\diffuse_map\\box.tga");
	_fe3d->model_setFaceCulled("@@box", "", true);
	_fe3d->model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d->model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.tga");
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha("@@grid", "", 0.1f);
	_fe3d->model_setLightness("@@grid", "", 0.25f);
	_fe3d->model_setShadowed("@@grid", false);
	_fe3d->model_create(SOUND3D_MODEL_ID, SOUND3D_MODEL_PATH);
	_fe3d->model_setBasePosition(SOUND3D_MODEL_ID, SOUND3D_POSITION);
	_fe3d->model_setBaseSize(SOUND3D_MODEL_ID, fvec3(0.5f));
	_fe3d->model_setShadowed(SOUND3D_MODEL_ID, false);
	_fe3d->model_setBright(SOUND3D_MODEL_ID, "", true);
	_fe3d->model_setVisible(SOUND3D_MODEL_ID, false);

	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->graphics_setAmbientLightingIntensity(1.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(3.0f);
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(0.25f);
	_fe3d->graphics_setShadowQuality(16384);
	_fe3d->graphics_setShadowPositionOffset(fvec3(5.0f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(5.0f)));

	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField("sound3dId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void Sound3dEditor::_unload()
{
	for(const auto & sound3dId : _loadedSound3dIds)
	{
		_fe3d->sound3d_delete(sound3dId);
	}

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");
	_fe3d->model_delete(SOUND3D_MODEL_ID);

	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField("sound3dId");

	_loadedSound3dIds.clear();
}

void Sound3dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	rightWindow->createScreen("sound3dEditorMenuMain");
	rightWindow->getScreen("sound3dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Sound3d"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Sound3d", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Sound3d"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sound3d", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Sound3d"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sound3d", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(3, CH, false);
	rightWindow->createScreen("sound3dEditorMenuChoice");
	rightWindow->getScreen("sound3dEditorMenuChoice")->createButton("maxVolume", fvec2(0.0f, positions[0]), TEXT_SIZE("Max Volume"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Volume", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuChoice")->createButton("maxDistance", fvec2(0.0f, positions[1]), TEXT_SIZE("Max Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Max Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound3dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

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