#include "script_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

ScriptEditor::ScriptEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SceneEditor& sceneEditor,
	ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, 
	AudioEditor& audioEditor, EnvironmentEditor& environmentEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_script(fe3d),
	_scriptExecutor(fe3d, _script, sceneEditor, modelEditor, animationEditor, billboardEditor, audioEditor, environmentEditor)
{

}

void ScriptEditor::_loadGUI()
{	
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Main menu
	string screenID = "scriptEditorMenuMain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addTextfield("lineCount", Vec2(0.0f, 0.7875f), Vec2(CW("Lines: 1000"), TH), "Lines: 1000", Vec3(1.0f));
	leftWindow->getScreen(screenID)->addButton("search", Vec2(0.0f, 0.525f), Vec2(CW("Search"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Search", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("add", Vec2(0.0f, 0.2625f), Vec2(CW("Add Script"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("edit", Vec2(0.0f, 0.0f), Vec2(CW("Edit Script"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("rename", Vec2(0.0f, -0.2625f), Vec2(CW("Rename Script"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rename Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("delete", Vec2(0.0f, -0.525f), Vec2(CW("Delete Script"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void ScriptEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("scriptEditorMenuMain");
}

void ScriptEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_load(CAMERA_FOV, Config::DEFAULT_CAMERA_NEAR, Config::DEFAULT_CAMERA_FAR, CAMERA_POSITION, -90.0f, 0.0f);

	// Background
	_fe3d.skyEntity_setLightness("@@engineBackground", 0.3f);

	// Graphics
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 0.5f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableNormalMapping();

	// Selection light
	_fe3d.lightEntity_add("@@selectionLight", Vec3(0.0f), Vec3(0.0f, 1.0f, 0.0f), 2.5f, 10.0f, false);

	// Load script
	loadScriptFiles(true);

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("scriptEditorControls");
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_isEditorLoaded = true;
}

void ScriptEditor::unload()
{
	// GUI
	_unloadGUI();

	// Graphics
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableSpecularLighting(true);
	_fe3d.gfx_disableNormalMapping(true);

	// Delete added entities
	_fe3d.modelEntity_deleteAll();
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
	_isSingleActionAllowed = true;
	_isContinuousActionAllowed = false;
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