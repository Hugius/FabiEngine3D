#include "animation_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using std::numeric_limits;

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

AnimationEditor::AnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, ModelEditor& modelEditor)
	:
	_fe3d(fe3d),
	_gui(gui),
	_modelEditor(modelEditor)
{

}

void AnimationEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	// Default graphics
	_fe3d.gfx_enableAmbientLighting();
	_fe3d.gfx_setAmbientLightingColor(Vec3(1.0f));
	_fe3d.gfx_setAmbientLightingIntensity(1.0f);
	_fe3d.gfx_enableDirectionalLighting();
	_fe3d.gfx_setDirectionalLightingColor(Vec3(1.0f));
	_fe3d.gfx_setDirectionalLightingPosition(Vec3(10000.0f));
	_fe3d.gfx_setDirectionalLightingIntensity(3.0f);
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);
	_fe3d.gfx_enableBloom();
	_fe3d.gfx_setBloomType(BloomType::PARTS);
	_fe3d.gfx_setBloomIntensity(1.0f);
	_fe3d.gfx_setBloomBlurCount(5);
	_fe3d.gfx_enableMotionBlur();
	_fe3d.gfx_setMotionBlurStrength(0.1f);
	_fe3d.gfx_enableShadows();
	_fe3d.gfx_setShadowLightness(0.25f);

	// Editor models
	_fe3d.modelEntity_create("@@cube", "engine_assets\\meshes\\cube.obj");
	_fe3d.modelEntity_setBasePosition("@@cube", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setDiffuseMap("@@cube", "", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_create("@@grid", "engine_assets\\meshes\\plane.obj");
	_fe3d.modelEntity_setBasePosition("@@grid", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setBaseSize("@@grid", Vec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setTextureRepeat("@@grid", "", GRID_UV);
	_fe3d.modelEntity_setShadowed("@@grid", false);

	// Miscellaneous
	_fe3d.reflectionEntity_create("@@reflection");
	_fe3d.reflectionEntity_capture("@@reflection");
	_gui.getGlobalScreen()->createTextField("animationID", Vec2(0.0f, -0.45f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->createTextField("animationFrame", Vec2(0.0f, -0.55f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("animationEditorControls");
	_fe3d.misc_setLevelOfDetailDistance(numeric_limits<float>::max());
	_isEditorLoaded = true;
}

void AnimationEditor::unload()
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
	_fe3d.gfx_disableMotionBlur(true);
	_fe3d.gfx_disableShadows(true);

	// Delete models
	_fe3d.modelEntity_deleteAll();

	// Delete animation extfields
	_gui.getGlobalScreen()->deleteTextField("animationID");
	_gui.getGlobalScreen()->deleteTextField("animationFrame");

	// Reset editor properties
	_animations.clear();
	_animationsToStop.clear();
	_animationsToStartAgain.clear();
	_startedAnimations.clear();
	_currentAnimationID = "";
	_currentPartID = "";
	_hoveredModelID = "";
	_hoveredPartID = "";
	_cameraLookatPosition = Vec3(0.0f);
	_currentFrameIndex = 0;
	_selectedPartInversionDirection = 1;
	_mustUpdateCurrentFramePreview = true;
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isDeletingAnimation = false;
	_isEditorLoaded = false;

	// Miscellaneous
	_fe3d.reflectionEntity_delete("@@reflection");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if(_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
}

void AnimationEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: animationEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("animationEditorMenuMain");
	leftWindow->getScreen("animationEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: animationEditorMenuChoice
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("animationEditorMenuChoice");
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("preview", Vec2(0.0f, positions[0]), Vec2(TW("Preview Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Preview Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("create", Vec2(0.0f, positions[1]), Vec2(TW("Create Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("edit", Vec2(0.0f, positions[2]), Vec2(TW("Edit Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("delete", Vec2(0.0f, positions[3]), Vec2(TW("Delete Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("prev", Vec2(-0.5f, positions[4]), Vec2(TW("Prev"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Prev", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("next", Vec2(0.5f, positions[4]), Vec2(TW("Next"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Next", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("play", Vec2(-0.5f, positions[5]), Vec2(TW("Play"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Play", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("stop", Vec2(0.5f, positions[5]), Vec2(TW("Stop"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: animationEditorMenuFrame
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("animationEditorMenuFrame");
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("transformation", Vec2(0.0f, positions[0]), Vec2(TW("Transformation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transformation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("rotationOrigin", Vec2(0.0f, positions[1]), Vec2(TW("Rotation Origin"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation Origin", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("speed", Vec2(0.0f, positions[2]), Vec2(TW("Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("speedType", Vec2(0.0f, positions[3]), Vec2(TW("Speed: LINEAR"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed: LINEAR", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("transType", Vec2(0.0f, positions[4]), Vec2(TW("Type: MOVE"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Type: MOVE", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("part", Vec2(0.0f, positions[5]), Vec2(TW("Part"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Part", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void AnimationEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animationEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animationEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animationEditorMenuFrame");
}