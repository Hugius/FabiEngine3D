#include "animation_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using std::numeric_limits;

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
	_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	// Default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 3.0f);
	_fe3d.gfx_setSceneReflectionHeight(0.0f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 5);
	_fe3d.gfx_enableMotionBlur(0.1f);

	// 3D environment
	_fe3d.modelEntity_create("@@cube", "engine_assets\\meshes\\cube.obj");
	_fe3d.modelEntity_setPosition("@@cube", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setDiffuseMap("@@cube", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_create("@@grid", "engine_assets\\meshes\\plane.obj");
	_fe3d.modelEntity_setPosition("@@grid", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setSize("@@grid", Vec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setUvRepeat("@@grid", GRID_UV);
	_fe3d.modelEntity_setTransparent("@@grid", true);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextfield("selectedAnimationID", Vec2(0.0f, -0.45f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->createTextfield("selectedAnimationFrame", Vec2(0.0f, -0.55f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("animationEditorControls");
	_fe3d.misc_setLevelOfDetailDistance(numeric_limits<float>::max());
	_isEditorLoaded = true;
}

void AnimationEditor::unload()
{
	// GUI
	_unloadGUI();

	// Camera
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}

	// Shadows
	if (_fe3d.gfx_isShadowsEnabled())
	{
		_fe3d.gfx_disableShadows(true);
	}

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableSpecularLighting(true);
	_fe3d.gfx_disableBloom(true);
	_fe3d.gfx_disableMotionBlur(true);

	// Delete models
	_fe3d.modelEntity_deleteAll();

	// Delete animation extfields
	_gui.getGlobalScreen()->deleteTextfield("selectedAnimationID");
	_gui.getGlobalScreen()->deleteTextfield("selectedAnimationFrame");

	// Reset editor properties
	_animations.clear();
	_startedAnimations.clear();
	_currentAnimationID = "";
	_currentPartID = "";
	_cameraLookatPosition = Vec3(0.0f);
	_currentFrameIndex = 0;
	_selectedPartInversionDirection = 1;
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isEditingAnimation = false;
	_isDeletingAnimation = false;
	_isEditorLoaded = false;

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.misc_isDebugRenderingEnabled())
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
	leftWindow->getScreen("animationEditorMenuMain")->createButton("add", Vec2(0.0f, positions[0]), Vec2(TW("Create Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Animation"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: animationEditorMenuChoice
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("animationEditorMenuChoice");
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("preview", Vec2(0.0f, positions[0]), Vec2(TW("Preview Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Preview Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("addFrame", Vec2(0.0f, positions[1]), Vec2(TW("Create Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("editFrame", Vec2(0.0f, positions[2]), Vec2(TW("Edit Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->createButton("deleteFrame", Vec2(0.0f, positions[3]), Vec2(TW("Delete Frame"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
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
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("part", Vec2(0.0f, positions[5]), Vec2(TW("Choose Part"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Part", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void AnimationEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animationEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animationEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("animationEditorMenuFrame");
}