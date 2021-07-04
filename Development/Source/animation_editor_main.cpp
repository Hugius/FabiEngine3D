#include "animation_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

AnimationEditor::AnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, ModelEditor& modelEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_modelEditor(modelEditor)
{

}

void AnimationEditor::_loadGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - animationEditorMenuMain
	leftWindow->addScreen("animationEditorMenuMain");
	leftWindow->getScreen("animationEditorMenuMain")->addButton("addAnimation", Vec2(0.0f, 0.63f), Vec2(CW("Add Animation"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->addButton("editAnimation", Vec2(0.0f, 0.21f), Vec2(CW("Edit Animation"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->addButton("deleteAnimation", Vec2(0.0f, -0.21f), Vec2(CW("Delete Animation"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Animation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - animationEditorMenuChoice
	leftWindow->addScreen("animationEditorMenuChoice");
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("preview", Vec2(0.0f, 0.7875f), Vec2(CW("Preview Model"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Preview Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("play", Vec2(-0.5f, 0.525f), Vec2(CW("Play"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Play", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("stop", Vec2(0.5f, 0.525f), Vec2(CW("Stop"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("addFrame", Vec2(0.0f, 0.2625f), Vec2(CW("Add Frame"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("editFrame", Vec2(0.0f, 0.0f), Vec2(CW("Edit Frame"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("deleteFrame", Vec2(0.0f, -0.2625f), Vec2(CW("Delete Frame"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Frame", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("prev", Vec2(-0.5f, -0.525f), Vec2(CW("Prev"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Prev", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("next", Vec2(0.5f, -0.525f), Vec2(CW("Next"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Next", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - animationEditorMenuFrame
	leftWindow->addScreen("animationEditorMenuFrame");
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("transformation", Vec2(0.0f, 0.7875f), Vec2(CW("Transformation"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transformation", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("rotationOrigin", Vec2(0.0f, 0.525f), Vec2(CW("Rotation Origin"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation Origin", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("speed", Vec2(0.0f, 0.2625f), Vec2(CW("Speed"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("speedType", Vec2(0.0f, 0.0f), Vec2(CW("Speed: LINEAR"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Speed: LINEAR", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("transType", Vec2(0.0f, -0.2625f), Vec2(CW("Type: TRANSLATE"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Type: TRANSLATE", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("part", Vec2(0.0f, -0.525f), Vec2(CW("Choose Part"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Choose Part", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void AnimationEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("animationEditorMenuMain");
	leftWindow->deleteScreen("animationEditorMenuChoice");
	leftWindow->deleteScreen("animationEditorMenuFrame");
}

void AnimationEditor::load()
{
	_isEditorLoading = true;

	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_load(Config::DEFAULT_CAMERA_FOV, Config::DEFAULT_CAMERA_NEAR, Config::DEFAULT_CAMERA_FAR, Vec3(0.0f), -90.0f, 0.0f);

	// Enable default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.45f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableSpecularLighting();

	// Load models
	_modelEditor.loadModelEntitiesFromFile();
	_fe3d.misc_setLevelOfDetailDistance(Config::DEFAULT_CAMERA_FAR);

	// Load animations
	loadAnimationsFromFile();

	// Miscellaneous
	_gui.getGlobalScreen()->addTextfield("selectedAnimationName", Vec2(0.0f, -0.45f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedAnimationFrame", Vec2(0.0f, -0.55f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("animationEditorControls");
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_isEditorLoading = false;
	_isEditorLoaded = true;
}

void AnimationEditor::unload()
{
	// GUI
	_unloadGUI();

	// Disable default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableSkyReflections(true);
	_fe3d.gfx_disableLightMapping(true);
	_fe3d.gfx_disableNormalMapping(true);
	_fe3d.gfx_disableSpecularLighting(true);

	// Delete models
	_fe3d.modelEntity_deleteAll();

	// Delete animation extfields
	_gui.getGlobalScreen()->deleteTextfield("selectedAnimationName");
	_gui.getGlobalScreen()->deleteTextfield("selectedAnimationFrame");

	// Reset editor properties
	_animations.clear();
	_startedAnimations.clear();
	_currentAnimationID = "";
	_currentPartID = "";
	_cameraLookatPosition = Vec3(0.0f);
	_totalCursorDifference = Vec2(0.0f, 0.5f);
	_cameraAcceleration = Vec2(0.0f);
	_lastCursorPos = Vec2(0.0f);
	_cameraDistance = 5.0f;
	_cameraSpeed = 0.1f;
	_cameraScrollingAcceleration = 0.0f;
	_partColorStrength = 0.0f;
	_colorChangingSpeed = 0.05f;
	_currentFrameIndex = 0;
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isEditingAnimation = false;
	_isRemovingAnimation = false;
	_isEditorLoaded = false;
	_isEditorLoading = false;
	_partColorIncreasing = true;

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_isEditorLoaded = false;
}
