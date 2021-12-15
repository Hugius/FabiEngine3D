#include "animation3d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using std::numeric_limits;

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

Animation3dEditor::Animation3dEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, ModelEditor& modelEditor)
	:
	_fe3d(fe3d),
	_gui(gui),
	_modelEditor(modelEditor)
{

}

void Animation3dEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	// Default graphics
	_fe3d.gfx_enableAmbientLighting();
	_fe3d.gfx_setAmbientLightingColor(fvec3(1.0f));
	_fe3d.gfx_setAmbientLightingIntensity(1.0f);
	_fe3d.gfx_enableDirectionalLighting();
	_fe3d.gfx_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d.gfx_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d.gfx_setDirectionalLightingIntensity(3.0f);
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);
	_fe3d.gfx_enableBloom();
	_fe3d.gfx_setBloomType(BloomType::PARTS);
	_fe3d.gfx_setBloomIntensity(1.0f);
	_fe3d.gfx_setBloomBlurCount(5);
	_fe3d.gfx_setBloomQuality(Config::MAX_BLOOM_QUALITY);
	_fe3d.gfx_enableShadows();
	_fe3d.gfx_setShadowLightness(0.25f);
	_fe3d.gfx_setShadowQuality(Config::MAX_SHADOW_QUALITY);

	// Editor models
	_fe3d.model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d.model_setBasePosition("@@box", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.model_setDiffuseMap("@@box", "", "engine\\assets\\texture\\box.png");
	_fe3d.model_setFaceCulled("@@box", true);
	_fe3d.model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d.model_setBasePosition("@@grid", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.model_setDiffuseMap("@@grid", "", "engine\\assets\\texture\\grid.png");
	_fe3d.model_setTextureRepeat("@@grid", "", GRID_UV);
	_fe3d.model_setShadowed("@@grid", false);

	// Miscellaneous
	_fe3d.reflection_create("@@reflection");
	_fe3d.reflection_capture("@@reflection");
	_gui.getGlobalScreen()->createTextField("animationID", fvec2(0.0f, -0.45f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_gui.getGlobalScreen()->createTextField("animationFrame", fvec2(0.0f, -0.55f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_isEditorLoaded = true;
}

void Animation3dEditor::unload()
{
	// GUI
	_unloadGUI();

	// Camera
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableBloom(true);
	_fe3d.gfx_disableShadows(true);

	// Delete models
	_fe3d.model_deleteAll();

	// Delete textfields
	_gui.getGlobalScreen()->deleteTextField("animationID");
	_gui.getGlobalScreen()->deleteTextField("animationFrame");

	// Reset editor properties
	_animations.clear();
	_modelAnimationsToStop.clear();
	_modelAnimationsToStart.clear();
	_startedModelAnimations.clear();
	_currentAnimationID = "";
	_currentPartID = "";
	_hoveredModelID = "";
	_hoveredPartID = "";
	_cameraLookatPosition = fvec3(0.0f);
	_currentFrameIndex = 0;
	_selectedPartHighlightDirection = 1;
	_mustUpdateCurrentFramePreview = true;
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isDeletingAnimation = false;
	_isEditorLoaded = false;

	// Miscellaneous
	_fe3d.reflection_delete("@@reflection");
	if(_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
}

void Animation3dEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: animationEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("animation3dEditorMenuMain");
	leftWindow->getScreen("animation3dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: animationEditorMenuChoice
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("animation3dEditorMenuChoice");
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("preview", fvec2(0.0f, positions[0]), fvec2(TW("Preview Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Preview Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("create", fvec2(0.0f, positions[1]), fvec2(TW("Create Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("edit", fvec2(0.0f, positions[2]), fvec2(TW("Edit Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("delete", fvec2(0.0f, positions[3]), fvec2(TW("Delete Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("prev", fvec2(-0.5f, positions[4]), fvec2(TW("Prev"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Prev", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("next", fvec2(0.5f, positions[4]), fvec2(TW("Next"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Next", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("start", fvec2(-0.5f, positions[5]), fvec2(TW("Start"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Start", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("stop", fvec2(0.5f, positions[5]), fvec2(TW("Stop"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[6]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: animationEditorMenuFrame
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("animation3dEditorMenuFrame");
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("part", fvec2(0.0f, positions[0]), fvec2(TW("Part"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Part", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("transformation", fvec2(0.0f, positions[1]), fvec2(TW("Transformation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transformation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("transformationType", fvec2(0.0f, positions[2]), fvec2(TW("Type: MOVE"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Type: MOVE", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("speed", fvec2(0.0f, positions[3]), fvec2(TW("Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("speedType", fvec2(0.0f, positions[4]), fvec2(TW("Type: LINEAR"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Type: LINEAR", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("rotationOrigin", fvec2(0.0f, positions[5]), fvec2(TW("Rotation Origin"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation Origin", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("animation3dEditorMenuFrame")->createButton("back", fvec2(0.0f, positions[6]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void Animation3dEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animation3dEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animation3dEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animation3dEditorMenuFrame");
}

void Animation3dEditor::update()
{
	// Animation execution
	_updateModelAnimationExecution();

	// Editor updates
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
		_updateCamera();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}