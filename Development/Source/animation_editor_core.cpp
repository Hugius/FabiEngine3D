#include "animation_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.15f, 1.8f)

AnimationEditor::AnimationEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, ModelEditor& modelEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_modelEditor(modelEditor)
{

}

void AnimationEditor::initializeGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - animationEditorMenuMain
	leftWindow->addScreen("animationEditorMenuMain");
	leftWindow->getScreen("animationEditorMenuMain")->addButton("addAnimation", Vec2(0.0f, 0.63f), Vec2(GW("Add animation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add animation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuMain")->addButton("editAnimation", Vec2(0.0f, 0.21f), Vec2(GW("Edit animation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit animation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuMain")->addButton("deleteAnimation", Vec2(0.0f, -0.21f), Vec2(GW("Delete animation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete animation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
	
	// Left-viewport: mainWindow - animationEditorMenuChoice
	leftWindow->addScreen("animationEditorMenuChoice");
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("preview", Vec2(0.0f, 0.7875f), Vec2(GW("Preview model"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Preview model", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("play", Vec2(-0.5f, 0.525f), Vec2(GW("Play"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Play", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("stop", Vec2(0.5f, 0.525f), Vec2(GW("Stop"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Stop", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("addFrame", Vec2(0.0f, 0.2625f), Vec2(GW("Add frame"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add frame", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("editFrame", Vec2(0.0f, 0.0f), Vec2(GW("Edit frame"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit frame", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("deleteFrame", Vec2(0.0f, -0.2625f), Vec2(GW("Delete frame"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete frame", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("prev", Vec2(-0.5f, -0.525f), Vec2(GW("Prev"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Prev", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("next", Vec2(0.5f, -0.525f), Vec2(GW("Next"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Next", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport: mainWindow - animationEditorMenuFrame
	leftWindow->addScreen("animationEditorMenuFrame");
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("transformation", Vec2(0.0f, 0.7875f), Vec2(GW("Transformation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Transformation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("rotationOrigin", Vec2(0.0f, 0.525f), Vec2(GW("Rotation origin"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rotation origin", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("speed", Vec2(0.0f, 0.2625f), Vec2(GW("Speed"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Speed", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("speedType", Vec2(0.0f, 0.0f), Vec2(GW("Speed: linear"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Speed: linear", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("transType", Vec2(0.0f, -0.2625f), Vec2(GW("Type: translation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Type: translation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("part", Vec2(0.0f, -0.525f), Vec2(GW("Choose part"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Choose part", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuFrame")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void AnimationEditor::load()
{
	_isEditorLoading = true;

	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, _defaultCameraPosition, -90.0f);
	_fe3d.camera_enableLookatView();

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.45f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableSkyReflections(0.5f);
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableSpecularLighting();

	// Load models
	_modelEditor.loadGameEntitiesFromFile();
	_fe3d.gameEntity_setLevelOfDetailDistance(10000.0f);

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
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableShadows(true);
	_fe3d.gfx_disableSkyReflections(true);
	_fe3d.gfx_disableLightMapping(true);
	_fe3d.gfx_disableNormalMapping(true);
	_fe3d.gfx_disableSpecularLighting(true);

	// Delete models
	_fe3d.gameEntity_deleteAll();

	// Delete animation extfields
	_gui.getGlobalScreen()->deleteTextfield("selectedAnimationName");
	_gui.getGlobalScreen()->deleteTextfield("selectedAnimationFrame");

	// Reset variables
	_animations.clear();
	_playingAnimations.clear();
	_currentAnimationID = "";
	_currentPartName = "";
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
	_fe3d.misc_disableDebugRendering();
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_isEditorLoaded = false;
}
