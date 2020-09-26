#include "script_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVPC::calcTextWidth(text, 0.2f, 1.8f)

ScriptEditor::ScriptEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void ScriptEditor::initializeGUI()
{
	// Private window instances of left & right viewport
	_leftWindow = _gui->getViewport("left")->getWindow("main");
	_rightWindow = _gui->getViewport("right")->getWindow("main");

	// Left-viewport script line screen
	string screenID = "scriptEditorMenuMain";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("variables", vec2(0.0f, 0.7875f), vec2(GW("Variables"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Variables", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("addLine", vec2(0.0f, 0.525f), vec2(GW("Add script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add script", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("updateLine", vec2(0.0f, 0.2625f), vec2(GW("Update script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Update script", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("deleteLine", vec2(0.0f, 0.0f), vec2(GW("Delete script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete script", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("createLine", vec2(0.0f, -0.2625f), vec2(GW("New script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "New script", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("viewLine", vec2(0.0f, -0.525f), vec2(GW("View script"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "View script", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7875f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);

	// Left-viewport script variable screen
	screenID = "scriptEditorMenuVariables";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("addVariable", vec2(0.0f, 0.75f), vec2(GW("Add variable"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Add variable", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("updateVariable", vec2(0.0f, 0.45f), vec2(GW("Update variable"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Update variable", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("deleteVariable", vec2(0.0f, 0.15f), vec2(GW("Delete variable"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Delete variable", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("createVariable", vec2(0.0f, -0.15f), vec2(GW("New variable"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "New variable", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("viewVariable", vec2(0.0f, -0.45f), vec2(GW("View variable"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "View variable", LVPC::textColor, LVPC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.75f), vec2(GW("Go back"), 0.1f), LVPC::buttonColor, LVPC::buttonHoverColor, "Go back", LVPC::textColor, LVPC::textHoverColor);
}

void ScriptEditor::load()
{
	// Camera
	_fe3d.camera_load(70.0f, 0.1f, 100.0f, _cameraStartingPosition, -90.0f);

	// Graphics
	_fe3d.gfx_enableDirectionalLighting(vec3(100.0f), vec3(1.0f), 0.5f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enablePointLighting();

	// Background
	_fe3d.gameEntity_add("background", "engine\\models\\plane.obj", vec3(0.0f), vec3(90.0f, 0.0f, 0.0f), vec3(100.0f));
	_fe3d.gameEntity_setDiffuseMap("background", "engine\\textures\\brick.png");
	_fe3d.gameEntity_setNormalMap("background", "engine\\textures\\brick_normal.png");
	_fe3d.gameEntity_setSpecularLighted("background", true);
	_fe3d.gameEntity_setSpecularFactor("background", 32.0f);
	_fe3d.gameEntity_setSpecularIntensity("background", 1.0f);
	_fe3d.gameEntity_setUvRepeat("background", 25.0f);
	_fe3d.gameEntity_setNormalMapped("background", true);

	// Selection light
	_fe3d.lightEntity_add("@@selectionLight", vec3(0.0f), vec3(0.0f, 1.0f, 0.0f), 2.5f, 10.0f, false);

	// Load script
	_loadScriptFromFile();

	// Other
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("scriptEditor");
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
	_unloadScript();

	// Reset editor properties
	_choiceListStack.clear();
	_currentEventToAdd = nullptr;
	_scriptExecutor = nullptr;
	_script = nullptr;
	_currentScriptLineID = "";
	_currentScriptVariableID = "";
	_newScriptVariableID = "";
	_scrollingAcceleration = 0.0f;
	_cameraAcceleration = 0.0f;
	_pointLightCounter = 0;
	_allowedToAddScriptLine = false;
	_isCreatingScriptLine = false;
	_isUpdatingScriptLine = false;
	_isAddingScriptLine = false;
	_allowedToAddScriptVariable = false;
	_isCreatingScriptVariable = false;
	_isUpdatingScriptVariable = false;
	_isAddingScriptVariable = false;

	// Miscellaneous
	_gui->getViewport("bottom")->getWindow("controls")->setActiveScreen("mainMenu");
	_isLoaded = false;
}