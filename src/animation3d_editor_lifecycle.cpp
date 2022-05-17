#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "animation3d_editor.hpp"
#include "configuration.hpp"

void Animation3dEditor::_load()
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
	_fe3d->model_setVisible(BOX_ID, false);
	_fe3d->captor_create(CAPTOR_ID);
	_fe3d->captor_setPosition(CAPTOR_ID, CAPTOR_POSITION);
	_fe3d->captor_capture(CAPTOR_ID);
	_fe3d->model_setVisible(BOX_ID, true);
	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingIntensity(AMBIENT_LIGHTING_INTENSITY);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingPosition(DIRECTIONAL_LIGHTING_POSITION);
	_fe3d->graphics_setDirectionalLightingIntensity(DIRECTIONAL_LIGHTING_INTENSITY);
	_fe3d->graphics_setBloomEnabled(true);
	_fe3d->graphics_setBloomType(BLOOM_TYPE);
	_fe3d->graphics_setBloomIntensity(BLOOM_INTENSITY);
	_fe3d->graphics_setBloomBlurCount(BLOOM_BLUR_COUNT);
	_fe3d->graphics_setBloomQuality(BLOOM_QUALITY);
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(SHADOW_LIGHTNESS);
	_fe3d->graphics_setShadowQuality(SHADOW_QUALITY);
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE * 0.5f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE * 0.5f)));
	_fe3d->graphics_setCubeReflectionQuality(CUBE_REFLECTION_QUALITY);
	_fe3d->graphics_setCubeRefractionQuality(CUBE_REFRACTION_QUALITY);
	_fe3d->graphics_setPlanarReflectionQuality(PLANAR_REFLECTION_QUALITY);
	_fe3d->graphics_setPlanarRefractionQuality(PLANAR_REFRACTION_QUALITY);
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField(ANIMATION3D_TITLE_ID, ANIMATION3D_TITLE_POSITION, ANIMATION3D_TITLE_SIZE, "", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField(FRAME_TITLE_ID, FRAME_TITLE_POSITION, FRAME_TITLE_SIZE, "", fvec3(1.0f), true);
}

void Animation3dEditor::_unload()
{
	_modelEditor->deleteLoadedModels();

	for(const auto & animation3dId : _loadedAnimation3dIds)
	{
		_fe3d->animation3d_delete(animation3dId);
	}

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(BOX_ID);
	_fe3d->captor_delete(CAPTOR_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setBloomEnabled(false);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomIntensity(0.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomQuality(0);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->graphics_setCubeReflectionQuality(0);
	_fe3d->graphics_setCubeRefractionQuality(0);
	_fe3d->graphics_setPlanarReflectionQuality(0);
	_fe3d->graphics_setPlanarRefractionQuality(0);
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(ANIMATION3D_TITLE_ID);
	_gui->getOverlay()->deleteTextField(FRAME_TITLE_ID);

	_loadedAnimation3dIds.clear();
}

void Animation3dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("animation3dEditorMenuMain");
	rightWindow->getScreen("animation3dEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Animation3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Animation3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Animation3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("animation3dEditorMenuChoice");
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("preview", fvec2(0.0f, POSITIONS(7)[0]), TEXT_SIZE("Preview Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Preview Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("create", fvec2(0.0f, POSITIONS(7)[1]), TEXT_SIZE("Create Frame"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("edit", fvec2(0.0f, POSITIONS(7)[2]), TEXT_SIZE("Edit Frame"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("delete", fvec2(0.0f, POSITIONS(7)[3]), TEXT_SIZE("Delete Frame"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("prev", fvec2(-0.5f, POSITIONS(7)[4]), TEXT_SIZE("Prev"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Prev", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("next", fvec2(0.5f, POSITIONS(7)[4]), TEXT_SIZE("Next"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Next", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("start", fvec2(-0.5f, POSITIONS(7)[5]), TEXT_SIZE("Start"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Start", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("stop", fvec2(0.5f, POSITIONS(7)[5]), TEXT_SIZE("Stop"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Stop", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(7)[6]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("animation3dEditorMenuFrame");
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("part", fvec2(0.0f, POSITIONS(7)[0]), TEXT_SIZE("Select Part"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Select Part", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("transformation", fvec2(0.0f, POSITIONS(7)[1]), TEXT_SIZE("Transformation"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Transformation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("transformationType", fvec2(0.0f, POSITIONS(7)[2]), TEXT_SIZE("Type: MOVE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: MOVE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("speed", fvec2(0.0f, POSITIONS(7)[3]), TEXT_SIZE("Speed"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("speedType", fvec2(0.0f, POSITIONS(7)[4]), TEXT_SIZE("Type: LINEAR"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: LINEAR", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("rotationOrigin", fvec2(0.0f, POSITIONS(7)[5]), TEXT_SIZE("Rotation Origin"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation Origin", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("back", fvec2(0.0f, POSITIONS(7)[6]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("animation3dEditorMenuMain");
}

void Animation3dEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->deleteScreen("animation3dEditorMenuMain");
	rightWindow->deleteScreen("animation3dEditorMenuChoice");
	rightWindow->deleteScreen("animation3dEditorMenuFrame");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void Animation3dEditor::update()
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
		_updateFrameMenu();
	}

	if(isLoaded())
	{
		_updateAnimation3dCreating();
	}

	if(isLoaded())
	{
		_updateAnimation3dChoosing();
	}

	if(isLoaded())
	{
		_updateAnimation3dDeleting();
	}

	if(isLoaded())
	{
		_updateModelChoosing();
	}

	if(isLoaded())
	{
		_updatePartChoosing();
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