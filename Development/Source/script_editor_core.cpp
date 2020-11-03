#include "script_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.2f, 1.8f)

ScriptEditor::ScriptEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SceneEditor& sceneEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_script(fe3d),
	_scriptExecutor(fe3d, _script, sceneEditor)
{

}

void ScriptEditor::initializeGUI()
{	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Main menu
	string screenID = "scriptEditorMenuMain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("createScript", vec2(0.0f, 0.63f), vec2(GW("New script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "New script", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("editScript", vec2(0.0f, 0.21f), vec2(GW("Edit script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Edit script", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("deleteScript", vec2(0.0f, -0.21f), vec2(GW("Delete script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete script", LVPC::textColor, LVPC::textHoverColor);
	leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void ScriptEditor::load()
{
	// Camera
	_fe3d.camera_load(70.0f, 0.1f, 10000.0f, _cameraStartingPosition, -90.0f);

	// Graphics
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), vec3(1.0f), 0.5f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enablePointLighting();

	// Background
	_fe3d.gameEntity_add("background", "engine\\models\\plane.obj", vec3(0.0f), vec3(90.0f, 0.0f, 0.0f), vec3(static_cast<float>(_maxLineAmount) * 1.1f));
	_fe3d.gameEntity_setDiffuseMap("background", "engine\\textures\\brick.png");
	_fe3d.gameEntity_setNormalMap("background", "engine\\textures\\brick_normal.png");
	_fe3d.gameEntity_setSpecularLighted("background", true);
	_fe3d.gameEntity_setSpecularFactor("background", 32.0f);
	_fe3d.gameEntity_setSpecularIntensity("background", 1.5f);
	_fe3d.gameEntity_setUvRepeat("background", (static_cast<float>(_maxLineAmount) * 1.1f) * 0.25f);
	_fe3d.gameEntity_setNormalMapped("background", true);

	// Selection light
	_fe3d.lightEntity_add("@@selectionLight", vec3(0.0f), vec3(0.0f, 1.0f, 0.0f), 2.5f, 10.0f, false);

	// Load script
	_loadScriptsFromFile();

	// Miscellaneous
	_isLoaded = true;
}

void ScriptEditor::save()
{
	_saveScriptToFile();
}

void ScriptEditor::unload()
{
	// Graphics
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableSpecularLighting();
	_fe3d.gfx_disableNormalMapping();
	_fe3d.gfx_disablePointLighting();

	// Delete added entities
	_fe3d.gameEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();

	// Unload script
	_script.reset();

	// Reset editor properties
	_scriptFileNamesToDelete.clear();
	_activeActionKey = InputType::NONE;
	_currentScriptFileID = "";
	_scrollingAcceleration = 0.0f;
	_isLoaded = false;
	_isScriptLoadedFromFile = false;
	_isWritingScript = false;
	_singleActionAllowed = true;
	_continuousActionAllowed = false;
	_wasGuiFocused = false;
	_isSelectingLines = false;
	_firstSelectedLineIndex = -1;
	_lastSelectedLineIndex = -1;
	_passedFrames = 0;
}