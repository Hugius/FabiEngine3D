#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "animation3d_editor.hpp"
#include "configuration.hpp"

void Animation3dEditor::_load()
{
	_fe3d->model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d->model_setDiffuseMap("@@box", "", "engine\\assets\\image\\diffuse_map\\box.tga");
	_fe3d->model_setFaceCulled("@@box", "", true);
	_fe3d->model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d->model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.tga");
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha("@@grid", "", 0.1f);

	_fe3d->model_setVisible("@@box", false);
	_fe3d->captor_create("@@captor");
	_fe3d->captor_setPosition("@@captor", fvec3(0.0f, 0.5f, 0.0f));
	_fe3d->captor_capture("@@captor");
	_fe3d->model_setVisible("@@box", true);

	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->graphics_setAmbientLightingIntensity(1.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(3.0f);
	_fe3d->graphics_setBloomEnabled(true);
	_fe3d->graphics_setBloomType(BloomType::PARTS);
	_fe3d->graphics_setBloomIntensity(1.0f);
	_fe3d->graphics_setBloomBlurCount(5);
	_fe3d->graphics_setBloomQuality(5);
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(0.25f);
	_fe3d->graphics_setShadowQuality(16384);
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE / 2.0f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE / 2.0f)));
	_fe3d->graphics_setCubeReflectionQuality(1024);
	_fe3d->graphics_setCubeRefractionQuality(1024);
	_fe3d->graphics_setPlanarReflectionQuality(1024);
	_fe3d->graphics_setPlanarRefractionQuality(1024);

	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField("animation3dId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("animation3dFrame", fvec2(0.0f, 0.75f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void Animation3dEditor::_unload()
{
	_modelEditor->deleteLoadedModels();

	for(const auto & animation3dId : _loadedAnimation3dIds)
	{
		_fe3d->animation3d_delete(animation3dId);
	}

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");

	_fe3d->captor_delete("@@captor");

	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingColor(fvec3(0.0f));
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
	_fe3d->graphics_setCubeReflectionQuality(0);
	_fe3d->graphics_setCubeRefractionQuality(0);
	_fe3d->graphics_setPlanarReflectionQuality(0);
	_fe3d->graphics_setPlanarRefractionQuality(0);

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField("animation3dId");
	_gui->getOverlay()->deleteTextField("animation3dFrame");

	_loadedAnimation3dIds.clear();
}

void Animation3dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	rightWindow->createScreen("animation3dEditorMenuMain");
	rightWindow->getScreen("animation3dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Animation3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Animation3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Animation3D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Animation3D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(7, CH, false);
	rightWindow->createScreen("animation3dEditorMenuChoice");
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("preview", fvec2(0.0f, positions[0]), TEXT_SIZE("Preview Model"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Preview Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("create", fvec2(0.0f, positions[1]), TEXT_SIZE("Create Frame"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("edit", fvec2(0.0f, positions[2]), TEXT_SIZE("Edit Frame"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("delete", fvec2(0.0f, positions[3]), TEXT_SIZE("Delete Frame"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("prev", fvec2(-0.5f, positions[4]), TEXT_SIZE("Prev"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Prev", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("next", fvec2(0.5f, positions[4]), TEXT_SIZE("Next"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Next", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("start", fvec2(-0.5f, positions[5]), TEXT_SIZE("Start"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Start", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("stop", fvec2(0.5f, positions[5]), TEXT_SIZE("Stop"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Stop", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[6]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(7, CH, false);
	rightWindow->createScreen("animation3dEditorMenuFrame");
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("part", fvec2(0.0f, positions[0]), TEXT_SIZE("Select Part"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Select Part", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("transformation", fvec2(0.0f, positions[1]), TEXT_SIZE("Transformation"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Transformation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("transformationType", fvec2(0.0f, positions[2]), TEXT_SIZE("Type: MOVE"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: MOVE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("speed", fvec2(0.0f, positions[3]), TEXT_SIZE("Speed"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("speedType", fvec2(0.0f, positions[4]), TEXT_SIZE("Type: LINEAR"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: LINEAR", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("rotationOrigin", fvec2(0.0f, positions[5]), TEXT_SIZE("Rotation Origin"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation Origin", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation3dEditorMenuFrame")->createButton("back", fvec2(0.0f, positions[6]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

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