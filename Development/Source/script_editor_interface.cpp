#include "script_editor.hpp"

void ScriptEditor::_generateScriptLineOverview(ScriptLine& scriptLine)
{
	// Clear all previous choice lists
	_clearChoiceLists();

	// Check if script line has event
	if (scriptLine.event != nullptr)
	{
		// Add event type
		_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_TYPES, static_cast<int>(scriptLine.event->getType()));

		// Determine event type and add resulting choices
		if (scriptLine.event->getType() == ScriptEventType::INITIALIZATION)
		{

		}
		else if (scriptLine.event->getType() == ScriptEventType::INPUT)
		{
			auto inputEvent = dynamic_pointer_cast<ScriptEventInput>(scriptLine.event);
			
			// Add input type
			_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_TYPES, static_cast<int>(inputEvent->getInputType()));
			
			// Determine input type
			if (inputEvent->getInputType() == InputEventType::KEYBOARD)
			{
				_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_KEY_NAMES, inputEvent->getInputElementIndex());
				_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_METHODS, static_cast<int>(inputEvent->getInputMethod()));
			}
			else if (inputEvent->getInputType() == InputEventType::MOUSE)
			{
				if (inputEvent->getMouseType() == InputEventMouseType::BUTTON)
				{
					_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_MOUSE_BUTTONS, inputEvent->getInputElementIndex());
					_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_METHODS, static_cast<int>(inputEvent->getInputMethod()));
				}
				else
				{
					_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_MOUSE_TYPES, inputEvent->getInputElementIndex());
				}
			}
		}
		else if (scriptLine.event->getType() == ScriptEventType::COLLISION)
		{

		}
		else if (scriptLine.event->getType() == ScriptEventType::TIME)
		{

		}
		else if (scriptLine.event->getType() == ScriptEventType::CONDITION)
		{

		}

		// Check if script line has action
		if (scriptLine.action != nullptr)
		{
			// Add action type
			_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_TYPES, static_cast<int>(scriptLine.action->getType()));

			// Determine event type and add resulting choices
			if (scriptLine.action->getType() == ScriptActionType::CAMERA)
			{
				auto cameraAction = dynamic_pointer_cast<ScriptActionCamera>(scriptLine.action);

				// Add camera type
				_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_TYPES, static_cast<int>(cameraAction->getCameraType()));

				// Determine camera type and add resulting screens
				if (cameraAction->getCameraType() == CameraActionType::POSITION)
				{
					_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_DIRECTIONS, static_cast<int>(cameraAction->getCameraDirection()));

					// XYZ change is only setting
					if (cameraAction->getCameraDirection() != CameraActionDirection::XYZ)
					{
						_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_METHODS, static_cast<int>(cameraAction->getCameraMethod()));
					}
				}
				else if (cameraAction->getCameraType() == CameraActionType::FOLLOW)
				{
					_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_FOLLOWS, static_cast<int>(cameraAction->getCameraFollow()));
				}
				else if (cameraAction->getCameraType() == CameraActionType::YAW || cameraAction->getCameraType() == CameraActionType::PITCH)
				{
					_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_METHODS, static_cast<int>(cameraAction->getCameraMethod()));
				}
				else if (cameraAction->getCameraType() == CameraActionType::LOOKAT || cameraAction->getCameraType() == CameraActionType::FIRST_PERSON)
				{
					_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_TOGGLE, static_cast<int>(cameraAction->getCameraToggle()));
				}

				// Add argument screens if existing
				if (cameraAction->hasVectorArgument())
				{
					_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_VALUES, "Values", {
						"X: " + to_string(static_cast<int>(cameraAction->getVectorArgument().x)),
						"Y: " + to_string(static_cast<int>(cameraAction->getVectorArgument().y)),
						"Z: " + to_string(static_cast<int>(cameraAction->getVectorArgument().z))});
				}
				else if (cameraAction->hasFloatArgument())
				{
					_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_VALUES, "Value", 
						{ to_string(static_cast<int>(cameraAction->getFloatArgument())) });
				}
			}
		}
	}
}

void ScriptEditor::_generateScriptVariableOverview(ScriptVariable& scriptVariable)
{

}

void ScriptEditor::_addChoiceList(ChoiceListSort listSort, ChoiceListType listType, int activeIndex)
{
	// General variables
	string headerName;
	vector<string> optionNames;

	// Type options
	vector<string> eventTypeNames = { "INIT_EVENT", "INPUT_EVENT", "COLLISION_EVENT", "TIME_EVENT", "CONDITION_EVENT" };
	vector<string> actionTypeNames = { "CAMERA_ACTION" };

	// Input options
	vector<string> inputTypeNames = { "KEYBOARD", "MOUSE" };
	vector<string> inputMouseTypeNames = { "BUTTON", "SCROLL_UP", "SCROLL_DOWN" };
	vector<string> inputKeyNames = { 
		"KEY_A", "KEY_B", "KEY_C", "KEY_D", "KEY_E", "KEY_F", "KEY_G", "KEY_H", "KEY_I", "KEY_J", "KEY_K", "KEY_L",
		"KEY_M", "KEY_N", "KEY_O", "KEY_P", "KEY_Q", "KEY_R", "KEY_S", "KEY_T", "KEY_U", "KEY_V", "KEY_W", "KEY_X", "KEY_Y", "KEY_Z",
		"KEY_LSHIFT", "KEY_RSHIFT", "KEY_LCTRL", "KEY_RCTRL", "KEY_SPACE", "KEY_ENTER", "KEY_BACKSPACE", "KEY_CAPSLOCK", "KEY_TAB", 
		"KEY_LEFT", "KEY_RIGHT", "KEY_UP", "KEY_DOWN", "KEY_0", "KEY_1", "KEY_2", "KEY_3", "KEY_4", "KEY_5", "KEY_6", "KEY_7", "KEY_8", "KEY_9" };
	vector<string> inputMouseNames = { "BUTTON_LEFT", "BUTTON_MIDDLE", "BUTTON_RIGHT" };
	vector<string> inputMethodNames = { "DOWN", "PRESSED", "TOGGLED" };

	// Camera options
	vector<string> cameraTypeNames = { "POSITION", "FOLLOW", "YAW", "PITCH", "LOOK_AT", "FIRST_PERSON" };
	vector<string> cameraDirectionNames = { "X", "Y", "Z", "XYZ" };
	vector<string> cameraFollowNames = { "FOLLOW_X", "FOLLOW_Z", "FOLLOW_ZY" };
	vector<string> cameraMethodNames = { "UPDATE", "SET" };

	// Miscellaneous options
	vector<string> toggleNames = { "ON", "OFF" };
	vector<string> decisionNames = { "YES", "NO" };
	vector<string> varTypeNames = {"STRING", "BOOLEAN", "NUMBER"};

	// Determine list to be generated
	switch (listType)
	{
		// Event or action
		case ChoiceListType::EVENT_TYPES:
		{
			headerName = "Event type";
			optionNames = eventTypeNames;
			break;
		}
		case ChoiceListType::ACTION_TYPES:
		{
			headerName = "Action type";
			optionNames = actionTypeNames;
			break;
		}

		// Initialization
		case ChoiceListType::EVENT_INITIALIZATION:
		{
			// Empty, because init event has no condition
			break;
		}

		// Input event
		case ChoiceListType::EVENT_INPUT_TYPES:
		{
			headerName = "Input type";
			optionNames = inputTypeNames;
			break;
		}
		case ChoiceListType::EVENT_INPUT_MOUSE_TYPES:
		{
			headerName = "Mouse type";
			optionNames = inputMouseTypeNames;
			break;
		}
		case ChoiceListType::EVENT_INPUT_KEY_NAMES:
		{
			headerName = "Keyboard key";
			optionNames = inputKeyNames;
			break;
		}
		case ChoiceListType::EVENT_INPUT_MOUSE_BUTTONS:
		{
			headerName = "Mouse button";
			optionNames = inputMouseNames;
			break;
		}
		case ChoiceListType::EVENT_INPUT_METHODS:
		{
			headerName = "Input method";
			optionNames = inputMethodNames;
			break;
		}

		// Camera action
		case ChoiceListType::ACTION_CAMERA_TYPES:
		{
			headerName = "Camera type";
			optionNames = cameraTypeNames;
			break;
		}
		case ChoiceListType::ACTION_CAMERA_DIRECTIONS:
		{
			headerName = "Camera direction";
			optionNames = cameraDirectionNames;
			break;
		}
		case ChoiceListType::ACTION_CAMERA_FOLLOWS:
		{
			headerName = "Camera follow";
			optionNames = cameraFollowNames;
			break;
		}
		case ChoiceListType::ACTION_CAMERA_METHODS:
		{
			headerName = "Camera method";
			optionNames = cameraMethodNames;
			break;
		}
		case ChoiceListType::ACTION_CAMERA_TOGGLE:
		{
			headerName = "Camera toggle";
			optionNames = toggleNames;
			break;
		}

		// Miscellaneous
		case ChoiceListType::VARIABLE_CONSTANT:
		{
			headerName = "Changeable";
			optionNames = decisionNames;
			break;
		}
		case ChoiceListType::VARIABLE_TYPE:
		{
			headerName = "Data type";
			optionNames = varTypeNames;
			break;
		}
	}

	// Add new choicelist
	_addChoiceList(listSort, listType, headerName, optionNames, activeIndex);
}

void ScriptEditor::_addChoiceList(ChoiceListSort listSort, ChoiceListType listType, string headerName, vector<string> optionNames, int activeIndex)
{
	// Generation values
	int listIndex = static_cast<int>(listType);
	const string fontPath = "engine\\fonts\\lucida.ttf";
	const float maxY = 4.5f;
	const float minX = -8.0f;
	const float xOffset = 8.5f;
	const float yOffset = 0.7f;
	vec3 headerPosition = vec3(minX + (xOffset * _choiceListStack.size()), 5.0f, 0.5f);

	// Header generation
	_fe3d.gameEntity_add(to_string(listIndex) + "_header", "engine\\models\\crate.obj", headerPosition,
		vec3(0.0f), vec3(headerName.size() * 0.275f, 0.75f, 0.5f));
	_fe3d.gameEntity_setDiffuseMap(to_string(listIndex) + "_header", "engine\\textures\\crate.png");
	_fe3d.billBoardEntity_add(to_string(listIndex) + "_header", headerName, fontPath, vec3(0.0f, 0.5f, 0.0f), headerPosition + vec3(0.0f, 0.25f, 0.05f),
		vec3(0.0f), vec2(headerName.size() * 0.4f, 1.0f), 0, 0);

	// Choice list generation
	for (size_t i = 0; i < optionNames.size(); i++)
	{
		string optionName = optionNames[i];

		// Check if only single option needed
		if (activeIndex != -1)
		{
			optionName = optionNames[activeIndex];
		}
		
		// Entity values
		vec3 optionPosition = vec3(headerPosition.x, maxY - (yOffset * (i + 1)), 0.55f);
		vec2 optionSize = vec2(optionName.size() * 0.25f, _optionBillboardHeight);
		string ID = to_string(listIndex) + "_option_" + to_string(i);

		// Create new option entity
		_fe3d.billBoardEntity_add(ID, optionName, fontPath, vec3(1.0f),
			optionPosition, vec3(0.0f), optionSize, 0, 0);
		_fe3d.billboardEntity_setMaxY(ID, maxY);
		_fe3d.aabbEntity_bindToBillboardEntity(ID, vec3(optionSize.x, optionSize.y, 0.1f), true);

		// Only 1 option
		if (activeIndex != -1)
		{
			break;
		}
	}

	// Add to stack
	if (activeIndex == -1)
	{
		_choiceListStack.push_back(ChoiceList(listSort, listType, optionNames.size(), optionNames));
	}
	else
	{
		_choiceListStack.push_back(ChoiceList(listSort, listType, optionNames[activeIndex].size(), optionNames));
	}
}

void ScriptEditor::_removeChoiceList()
{
	int currentListIndex = static_cast<int>(_choiceListStack.back().type);

	// Remove header
	_fe3d.gameEntity_delete(to_string(currentListIndex) + "_header");
	_fe3d.billboardEntity_delete(to_string(currentListIndex) + "_header");

	// Remove all options
	for (int i = 0; i < _choiceListStack.back().total; i++)
	{
		string ID = to_string(currentListIndex) + "_option_" + to_string(i);
		if (_fe3d.billboardEntity_isExisting(ID))
		{
			_fe3d.billboardEntity_delete(ID);
		}
	}

	// Remove last list
	_choiceListStack.pop_back();
}

void ScriptEditor::_clearChoiceLists()
{
	// Clear all previous choice lists
	while (!_choiceListStack.empty())
	{
		_removeChoiceList();
	}

	// Clear placed pointlights
	for (unsigned int i = 0; i <= _pointLightCounter; i++)
	{
		if (_fe3d.lightEntity_isExisting(to_string(i)))
		{
			_fe3d.lightEntity_delete(to_string(i));
		}
	}

	// Hide selection light
	_fe3d.lightEntity_hide("@@selectionLight");

	// Default camera position
	_fe3d.camera_setPosition(_cameraStartingPosition);
}