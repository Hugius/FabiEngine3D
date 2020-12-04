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
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("play", Vec2(0.0f, 0.525f), Vec2(GW("Play animation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Play animation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("stop", Vec2(0.0f, 0.2625f), Vec2(GW("Stop animation"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Stop animation", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("addFrame", Vec2(0.0f, 0.0f), Vec2(GW("Add frame"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add frame", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("editFrame", Vec2(0.0f, -0.2625f), Vec2(GW("Edit frame"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit frame", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("deleteFrame", Vec2(0.0f, -0.525f), Vec2(GW("Delete frame"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete frame", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen("animationEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void AnimationEditor::load()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, _defaultCameraPosition, -90.0f);
	_fe3d.camera_enableLookat(Vec3(0.0f));

	// Enable graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.45f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableShadows(Vec3(10.0f, 10.0f, 10.0f), Vec3(0.0f), 25.0f, 50.0f, false);

	// Load models
	_modelEditor.loadGameEntitiesFromFile();

	// Miscellaneous
	_gui.getGlobalScreen()->addTextfield("selectedAnimationName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	//_gui.getViewport("right")->getWindow("main")->setActiveScreen("animationEditorControls");
	_isLoaded = true;
}

void AnimationEditor::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableShadows();

	// Delete models
	_fe3d.gameEntity_deleteAll();

	// Delete animation name textfield
	_gui.getGlobalScreen()->deleteTextfield("selectedAnimationName");

	// Reset variables
	_currentAnimationID = "";
	_animations.clear();
	_totalCursorDifference = Vec2(0.0f);
	_cameraAcceleration = Vec2(0.0f);
	_lastCursorPos = Vec2(0.0f);
	_cameraDistance = 5.0f;
	_cameraScrollingAcceleration = 0.0f;
	_isCreatingAnimation = false;
	_isChoosingAnimation = false;
	_isEditingAnimation = false;
	_isRemovingAnimation = false;

	// Miscellaneous
	//_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	_fe3d.misc_disableDebugRendering();
	_fe3d.input_clearKeyToggles();
	_isLoaded = false;
}
