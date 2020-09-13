#include "script_editor.hpp"
#include "left_viewport_controller.hpp"

#define GW(text) LVC::calcTextWidth(text, 0.2f, 1.8f)

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

	// Left-viewport screen
	string screenID = "scriptEditorMenuMain";
	_leftWindow->addScreen(screenID);
	_leftWindow->getScreen(screenID)->addButton("addLine", vec2(0.0f, 0.7f), vec2(GW("Add script"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Add script", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("deleteLine", vec2(0.0f, 0.35f), vec2(GW("Delete script"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Delete script", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("createLine", vec2(0.0f, 0.0f), vec2(GW("Create script"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Create script", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("viewLine", vec2(0.0f, -0.35f), vec2(GW("View script"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "View script", LVC::textColor, LVC::textHoverColor);
	_leftWindow->getScreen(screenID)->addButton("back", vec2(0.0f, -0.7f), vec2(GW("Go back"), 0.1f), LVC::buttonColor, LVC::buttonHoverColor, "Go back", LVC::textColor, LVC::textHoverColor);
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
	_eventTypeNames = { "INIT_EVENT", "INPUT_EVENT", "COLLISION_EVENT", "TIME_EVENT", "CONDITION_EVENT" };

	// Init event
	
	// Input event
	_inputTypeNames = { "KEYBOARD", "MOUSE" };
	_inputKeyNames = { "KEY_A", "KEY_B", "KEY_C", "KEY_D", "KEY_E", "KEY_F", "KEY_G", "KEY_H", "KEY_i", "KEY_J", "KEY_K", "KEY_L", "KEY_M",
		"KEY_N", "KEY_O", "KEY_P", "KEY_Q", "KEY_R", "KEY_S", "KEY_T", "KEY_U", "KEY_V", "KEY_W", "KEY_X", "KEY_Y", "KEY_Z" };
	_inputMouseNames = { "BUTTON_LEFT", "BUTTON_MIDDLE", "BUTTON_RIGHT", "SCROLL_UP", "SCROLL_DOWN" };
	_inputMethodNames = { "DOWN", "PRESSED", "TOGGLED" };

	// Collision event

	// Time event
	
	// Condition event

	// Load script

	// Miscellaneous
	_isLoaded = true;
}

void ScriptEditor::save()
{

}

void ScriptEditor::unload()
{
	// Graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableSpecularLighting();
	_fe3d.gfx_disableNormalMapping();

	// Delete added entities
	_fe3d.gameEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();

	// Reset editor properties
	_script.reset();
	_choiceListStack.clear();
	_eventTypeNames.clear();
	_inputTypeNames.clear();
	_inputKeyNames.clear();
	_inputMouseNames.clear();
	_scrollingAcceleration = 0.0f;
	_currentScriptLineID = "";
	_isLoaded = false;
}

void ScriptEditor::_addNewScriptLine(const string& newID)
{
	// Placeholders
	shared_ptr<ScriptEvent> event = nullptr;
	shared_ptr<ScriptAction> action = nullptr;

	// Fill the placeholders
	for (auto& choiceList : _choiceListStack)
	{
		int optionIndex = choiceList.selectedOptionIndex;

		// Determine choicelist type
		switch (choiceList.type)
		{
			// Event types
			case ChoiceListType::EVENT_TYPES:
			{
				if (choiceList.selectedOptionIndex == 0) event = make_shared<ScriptEventInit>(_fe3d, ScriptEventType::INIT_EVENT);
				if (choiceList.selectedOptionIndex == 1) event = make_shared<ScriptEventInput>(_fe3d, ScriptEventType::INPUT_EVENT);
				if (choiceList.selectedOptionIndex == 2) event = make_shared<ScriptEventCollision>(_fe3d, ScriptEventType::COLLISION_EVENT);
				if (choiceList.selectedOptionIndex == 3) event = make_shared<ScriptEventTime>(_fe3d, ScriptEventType::TIME_EVENT);
				if (choiceList.selectedOptionIndex == 4) event = make_shared<ScriptEventCondition>(_fe3d, ScriptEventType::CONDITION_EVENT);
				break;
			}

			// Input event
			case ChoiceListType::INPUT_TYPES:
			{
				dynamic_pointer_cast<ScriptEventInput>(event)->setInputType(static_cast<InputType>(choiceList.selectedOptionIndex + 1));
				break;
			}
			case ChoiceListType::INPUT_KEY_NAMES:
			{
				dynamic_pointer_cast<ScriptEventInput>(event)->setInputElement(_inputKeyNames[optionIndex]);
				break;
			}
			case ChoiceListType::INPUT_MOUSE_NAMES:
			{
				dynamic_pointer_cast<ScriptEventInput>(event)->setInputElement(_inputMouseNames[optionIndex]);
				break;
			}
			case ChoiceListType::INPUT_METHODS:
			{
				dynamic_pointer_cast<ScriptEventInput>(event)->setInputMethod(static_cast<InputMethod>(choiceList.selectedOptionIndex + 1));
				break;
			}
		}
	}

	// Create new script line
	_script.addLine(newID, event, action);
}