#include "script_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.2f, 1.8f)

ScriptEditor::ScriptEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SceneEditor& sceneEditor,
	ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, 
	AudioEditor& audioEditor, EnvironmentEditor& environmentEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_script(fe3d),
	_scriptExecutor(fe3d, _script, sceneEditor, modelEditor, animationEditor, billboardEditor, audioEditor, environmentEditor)
{

}

void ScriptEditor::initializeGUI()
{	
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Main menu
	string screenID = "scriptEditorMenuMain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addTextfield("lineCount", Vec2(0.0f, 0.75f), Vec2(GW("Line count: 1000"), 0.1f), "Line count: 1000", Vec3(1.0f));
	leftWindow->getScreen(screenID)->addButton("createScript", Vec2(0.0f, 0.45f), Vec2(GW("New script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "New script", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("editScript", Vec2(0.0f, 0.15f), Vec2(GW("Edit script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit script", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("renameScript", Vec2(0.0f, -0.15f), Vec2(GW("Rename script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Rename script", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("deleteScript", Vec2(0.0f, -0.45f), Vec2(GW("Delete script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete script", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.75f), Vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void ScriptEditor::load()
{
	// Camera
	_fe3d.camera_load(70.0f, 0.1f, 10000.0f, _cameraStartingPosition, -90.0f);

	// Background
	_fe3d.skyEntity_setLightness("@@engineBackground", 0.3f);

	// Graphics
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 0.5f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableNormalMapping();

	// Selection light
	_fe3d.lightEntity_add("@@selectionLight", Vec3(0.0f), Vec3(0.0f, 1.0f, 0.0f), 2.5f, 10.0f, false);

	// Load script
	loadScriptsFromFile();

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("scriptEditorControls");
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_isEditorLoaded = true;
}

void ScriptEditor::unload()
{
	// Graphics
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableSpecularLighting();
	_fe3d.gfx_disableNormalMapping();

	// Delete added entities
	_fe3d.gameEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.aabbEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();

	// Unload script
	_script.reset();

	// Reset editor properties
	_scriptFileNamesToDelete.clear();
	_activeActionKey = InputType::NONE;
	_currentScriptFileID = "";
	_scrollingAcceleration = 0.0f;
	_isScriptLoadedFromFile = false;
	_isWritingScript = false;
	_singleActionAllowed = true;
	_continuousActionAllowed = false;
	_wasGuiFocused = false;
	_firstSelectedLineIndex = -1;
	_lastSelectedLineIndex = -1;
	_passedFrames = 0;

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_isEditorLoaded = false;
}