#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "animation3d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Animation3dEditor::_load()
{
	_fe3d->camera_reset();
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d->camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	_fe3d->gfx_setAntiAliasingEnabled(true);
	_fe3d->gfx_setAnisotropicFilteringQuality(16);
	_fe3d->gfx_setAmbientLightingEnabled(true);
	_fe3d->gfx_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->gfx_setAmbientLightingIntensity(1.0f);
	_fe3d->gfx_setDirectionalLightingEnabled(true);
	_fe3d->gfx_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->gfx_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d->gfx_setDirectionalLightingIntensity(3.0f);
	_fe3d->gfx_setBloomEnabled(true);
	_fe3d->gfx_setBloomType(BloomType::PARTS);
	_fe3d->gfx_setBloomIntensity(1.0f);
	_fe3d->gfx_setBloomBlurCount(5);
	_fe3d->gfx_setBloomQuality(5);
	_fe3d->gfx_setShadowsEnabled(true);
	_fe3d->gfx_setShadowLightness(0.25f);
	_fe3d->gfx_setShadowQuality(16384);
	_fe3d->gfx_setCubeReflectionQuality(1024);
	_fe3d->gfx_setPlanarReflectionQuality(1024);
	_fe3d->gfx_setPlanarRefractionQuality(1024);

	_fe3d->model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d->model_setBasePosition("@@box", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d->model_setDiffuseMap("@@box", "", "engine\\assets\\image\\diffuse_map\\box.tga");
	_fe3d->model_setFaceCulled("@@box", "", true);
	_fe3d->model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d->model_setBasePosition("@@grid", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d->model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.tga");
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha("@@grid", "", 0.1f);
	_fe3d->model_setShadowed("@@grid", false);

	_fe3d->reflection_create("@@reflection");
	_fe3d->reflection_capture("@@reflection");

	_gui->getOverlay()->createTextField("animationId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("animationFrame", fvec2(0.0f, 0.75f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void Animation3dEditor::_unload()
{
	for(const auto& id : _modelEditor->getLoadedEntityIds())
	{
		_fe3d->model_delete(id);
	}

	for(const auto& id : _loadedAnimationIds)
	{
		_fe3d->animation3d_delete(id);
	}

	_fe3d->camera_setThirdPersonEnabled(false);

	_fe3d->gfx_setAntiAliasingEnabled(false);
	_fe3d->gfx_setAnisotropicFilteringQuality(16);
	_fe3d->gfx_setAmbientLightingEnabled(false);
	_fe3d->gfx_setAmbientLightingColor(fvec3(0.0f));
	_fe3d->gfx_setAmbientLightingIntensity(0.0f);
	_fe3d->gfx_setDirectionalLightingEnabled(false);
	_fe3d->gfx_setDirectionalLightingColor(fvec3(0.0f));
	_fe3d->gfx_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->gfx_setDirectionalLightingIntensity(0.0f);
	_fe3d->gfx_setBloomEnabled(false);
	_fe3d->gfx_setBloomType(BloomType::EVERYTHING);
	_fe3d->gfx_setBloomIntensity(0.0f);
	_fe3d->gfx_setBloomBlurCount(0);
	_fe3d->gfx_setBloomQuality(0);
	_fe3d->gfx_setShadowsEnabled(false);
	_fe3d->gfx_setShadowLightness(0.0f);
	_fe3d->gfx_setShadowQuality(0);
	_fe3d->gfx_setCubeReflectionQuality(0);
	_fe3d->gfx_setPlanarReflectionQuality(0);
	_fe3d->gfx_setPlanarRefractionQuality(0);

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");

	_fe3d->reflection_delete("@@reflection");

	_gui->getOverlay()->deleteTextField("animationId");
	_gui->getOverlay()->deleteTextField("animationFrame");

	_loadedAnimationIds.clear();
	_currentAnimationId = "";
	_currentPartId = "";
	_hoveredModelId = "";
	_hoveredPartId = "";
	_cameraLookatPosition = fvec3(0.0f);
	_originalPartOpacity = 0.0f;
	_selectedPartHighlightDirection = 1;
	_currentFrameIndex = 0;
	_mustUpdateCurrentFramePreview = true;
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isDeletingAnimation = false;
	_isChoosingModel = false;
	_isChoosingPart = false;
}

void Animation3dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("animation3dEditorMenuMain");
	leftWindow->getScreen("animation3dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Animation"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Animation"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Animation"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Animation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(7, CH);
	leftWindow->createScreen("animation3dEditorMenuChoice");
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("preview", fvec2(0.0f, positions[0]), TEXT_SIZE("Preview Model"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Preview Model", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("create", fvec2(0.0f, positions[1]), TEXT_SIZE("Create Frame"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("edit", fvec2(0.0f, positions[2]), TEXT_SIZE("Edit Frame"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("delete", fvec2(0.0f, positions[3]), TEXT_SIZE("Delete Frame"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Frame", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("prev", fvec2(-0.5f, positions[4]), TEXT_SIZE("Prev"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Prev", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("next", fvec2(0.5f, positions[4]), TEXT_SIZE("Next"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Next", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("start", fvec2(-0.5f, positions[5]), TEXT_SIZE("Start"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Start", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("stop", fvec2(0.5f, positions[5]), TEXT_SIZE("Stop"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Stop", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[6]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(7, CH);
	leftWindow->createScreen("animation3dEditorMenuFrame");
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("part", fvec2(0.0f, positions[0]), TEXT_SIZE("Select Part"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Select Part", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("transformation", fvec2(0.0f, positions[1]), TEXT_SIZE("Transformation"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Transformation", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("transformationType", fvec2(0.0f, positions[2]), TEXT_SIZE("Type: MOVE"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: MOVE", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("speed", fvec2(0.0f, positions[3]), TEXT_SIZE("Speed"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Speed", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("speedType", fvec2(0.0f, positions[4]), TEXT_SIZE("Type: LINEAR"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Type: LINEAR", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("rotationOrigin", fvec2(0.0f, positions[5]), TEXT_SIZE("Rotation Origin"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rotation Origin", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("back", fvec2(0.0f, positions[6]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void Animation3dEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("animation3dEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("animation3dEditorMenuChoice");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("animation3dEditorMenuFrame");
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
		_updateAnimationCreating();
	}
	if(isLoaded())
	{
		_updateAnimationChoosing();
	}
	if(isLoaded())
	{
		_updateAnimationDeleting();
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