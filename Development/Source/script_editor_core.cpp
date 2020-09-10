#include "script_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVC::calcTextWidth(text, 0.15f, 1.8f)

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

	// Generation values
	const string fontPath = "Engine\\Fonts\\futura.ttf";
	const vec3 color = vec3(1.0f);
	const vector<string> names = { "Event class", "Event type", "Event name", "Action class", "Action type", "Action name" };
	const float minX = -9.0f;
	const float offset = 6.0f;

	// Header generation
	for (size_t i = 0; i < names.size(); i++)
	{
		_fe3d.gameEntity_add(std::to_string(i), "Engine\\OBJs\\crate.obj", vec3(minX + (offset * i), 5.0f, 0.5f), vec3(0.0f), vec3(1.7f, 0.5f, 0.5f));
		_fe3d.gameEntity_setDiffuseMap(std::to_string(i), "Engine\\Textures\\crate.png");
		_fe3d.billBoardEntity_add(std::to_string(i), names[i], fontPath, color, vec3(minX + (offset * i), 5.25f, 0.55f), vec3(0.0f), vec2(2.5f, 0.5f), 0, 0);
	}
}

void ScriptEditor::save()
{

}

void ScriptEditor::unload()
{

}