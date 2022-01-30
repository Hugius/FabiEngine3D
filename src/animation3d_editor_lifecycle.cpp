#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "animation3d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Animation3dEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d->camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	_fe3d->gfx_enableAntiAliasing();
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->gfx_enableAmbientLighting();
	_fe3d->gfx_setAmbientLightingColor(fvec3(1.0f));
	_fe3d->gfx_setAmbientLightingIntensity(1.0f);
	_fe3d->gfx_enableDirectionalLighting();
	_fe3d->gfx_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d->gfx_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d->gfx_setDirectionalLightingIntensity(3.0f);
	_fe3d->gfx_enableBloom();
	_fe3d->gfx_setBloomType(BloomType::PARTS);
	_fe3d->gfx_setBloomIntensity(1.0f);
	_fe3d->gfx_setBloomBlurCount(5);
	_fe3d->gfx_setBloomQuality(Config::MAX_BLOOM_QUALITY);
	_fe3d->gfx_enableShadows();
	_fe3d->gfx_setShadowLightness(0.25f);
	_fe3d->gfx_setShadowQuality(Config::MAX_SHADOW_QUALITY);
	_fe3d->gfx_setCubeReflectionQuality(Config::MAX_REFLECTION_QUALITY);
	_fe3d->gfx_setPlanarReflectionQuality(Config::MAX_REFLECTION_QUALITY);
	_fe3d->gfx_setPlanarRefractionQuality(Config::MAX_REFRACTION_QUALITY);

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

	_gui->getOverlay()->createTextField("animationId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("animationFrame", fvec2(0.0f, 0.75f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_isEditorLoaded = true;
}

void Animation3dEditor::unload()
{
	for(const auto& animation : _animations)
	{
		if(_fe3d->model_isExisting(animation->getPreviewModelId()))
		{
			_fe3d->model_delete(animation->getPreviewModelId());
		}
	}

	_unloadGUI();

	if(_fe3d->camera_isThirdPersonViewEnabled())
	{
		_fe3d->camera_disableThirdPersonView();
	}

	_fe3d->gfx_disableAntiAliasing(true);
	_fe3d->gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->gfx_disableAmbientLighting(true);
	_fe3d->gfx_disableDirectionalLighting(true);
	_fe3d->gfx_disableBloom(true);
	_fe3d->gfx_disableShadows(true);
	_fe3d->gfx_setCubeReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d->gfx_setPlanarReflectionQuality(Config::MIN_REFLECTION_QUALITY);
	_fe3d->gfx_setPlanarRefractionQuality(Config::MIN_REFRACTION_QUALITY);

	_fe3d->model_delete("@@box");
	_fe3d->model_delete("@@grid");

	_fe3d->reflection_delete("@@reflection");

	_gui->getOverlay()->deleteTextField("animationId");
	_gui->getOverlay()->deleteTextField("animationFrame");

	_modelAnimationsToStop.clear();
	_modelAnimationsToStart.clear();
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
	_isEditorLoaded = false;
	_startedModelAnimations.clear();
	_animations.clear();
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
	_updateModelAnimationExecution();

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
		_updateFrameMenu();
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
		_updateModelChoosing();
	}
	if(_isEditorLoaded)
	{
		_updatePartChoosing();
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