#include "script_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVC::calcTextWidth(text, 0.25f, 1.8f)

ScriptEditor::ScriptEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void ScriptEditor::initializeGUI()
{
	// Private window instance of left viewport
	_leftWindow = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - billboardManagement
	_leftWindow->addScreen("scriptEditorMenuMain");
	_leftWindow->getScreen("scriptEditorMenuMain")->addButton("inputEvents", vec2(0.0f, 0.63f), vec2(GW("Input events"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Input events", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("scriptEditorMenuMain")->addButton("collisionEvents", vec2(0.0f, 0.21), vec2(GW("Edit board"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Edit board", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("scriptEditorMenuMain")->addButton("timeEvents", vec2(0.0f, -0.21), vec2(GW("Delete board"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Delete board", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen("scriptEditorMenuMain")->addButton("back", vec2(0.0f, -0.63f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
}

void ScriptEditor::load()
{
	// Camera
	_fe3d.camera_load(70.0f, 0.1f, 100.0f, vec3(0.0f, 0.0f, 10.0f), -90.0f);

	// Graphics
	_fe3d.gfx_enableAmbientLighting(vec3(1.0f), 0.25f);
	_fe3d.gfx_enableDirectionalLighting(vec3(100.0f), vec3(1.0f), 1.0f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableNormalMapping();

	// Background
	_fe3d.gameEntity_add("background", "Engine\\OBJs\\plane.obj", vec3(0.0f), vec3(90.0f, 0.0f, 0.0f), vec3(20.0f));
	_fe3d.gameEntity_setDiffuseMap("background", "Engine\\Textures\\brick.png");
	_fe3d.gameEntity_setNormalMap("background", "Engine\\Textures\\brick_normal.png");
	_fe3d.gameEntity_setSpecularLighted("background", true);
	_fe3d.gameEntity_setSpecularFactor("background", 32.0f);
	_fe3d.gameEntity_setSpecularIntensity("background", 1.0f);
	_fe3d.gameEntity_setUvRepeat("background", 5.0f);
	_fe3d.gameEntity_setNormalMapped("background", true);

	// Event types
	_eventTypeNames = { "Initialization event", "Input event", "Collision event", "Time event", "Condition event" };

	// Init event

	// Input event
	_inputTypeNames = { "Keyboard", "Mouse" };
	_inputKeyNames = { "KEY_A", "KEY_B", "KEY_C", "KEY_D", "KEY_E", "KEY_F", "KEY_G", "KEY_H", "KEY_i", "KEY_J", "KEY_K", "KEY_L", "KEY_M",
		"KEY_N", "KEY_O", "KEY_P", "KEY_Q", "KEY_R", "KEY_S", "KEY_T", "KEY_U", "KEY_V", "KEY_W", "KEY_X", "KEY_Y", "KEY_Z" };
	_inputMouseNames = { "LMB", "MMB", "RMB", "Scroll UP", "Scroll DOWN" };

	// Collision event

	// Time event
	
	// Condition event

	// Add first choice list
	addChoiceList(ChoiceListType::EVENT_TYPES);
	_isLoaded = true;
}

void ScriptEditor::save()
{

}

void ScriptEditor::unload()
{

}