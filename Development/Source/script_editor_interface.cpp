#include "script_editor.hpp"

void ScriptEditor::_generateScriptLineInterface(ScriptLine& scriptLine)
{
	// Clear all previous choice lists
	while (!_choiceListStack.empty())
	{
		_removeChoiceList();
	}

	// Add default choicelist
	_addChoiceList(ChoiceListType::EVENT_TYPES);

	// Check if script line has event
	if (scriptLine.event != nullptr)
	{
		//if (scriptLine.event->getType() == ScriptEventType::INIT_EVENT)
		if (scriptLine.event->getType() == ScriptEventType::INPUT_EVENT) _addChoiceList(ChoiceListType::INPUT_TYPES);
		//if (scriptLine.event->getType() == ScriptEventType::COLLISION_EVENT)
		//if (scriptLine.event->getType() == ScriptEventType::TIME_EVENT)
		//if (scriptLine.event->getType() == ScriptEventType::CONDITION_EVENT)

		if (dynamic_pointer_cast<ScriptEventInput>(scriptLine.event)->getInputType() == InputType::KEYBOARD)
		{
			_addChoiceList(ChoiceListType::INPUT_KEY_NAMES);
		}

		// Check if script line has action
		if (scriptLine.action != nullptr)
		{

		}
	}
}

void ScriptEditor::_addChoiceList(ChoiceListType listType)
{
	// General variables
	int listIndex = static_cast<int>(listType);
	string headerName;
	vector<string> optionNames;

	// Determine list to be generated
	switch (listType)
	{
		case ChoiceListType::EVENT_TYPES:
		{
			headerName = "Event type";
			optionNames = _eventTypeNames;
			break;
		}
		case ChoiceListType::INPUT_TYPES:
		{
			headerName = "Input type";
			optionNames = _inputTypeNames;
			break;
		}
		case ChoiceListType::INPUT_KEY_NAMES:
		{
			headerName = "Keyboard key";
			optionNames = _inputKeyNames;
			break;
		}
		case ChoiceListType::INPUT_MOUSE_NAMES:
		{
			headerName = "Mouse button";
			optionNames = _inputMouseNames;
			break;
		}
		case ChoiceListType::INPUT_METHODS:
		{
			headerName = "Input method";
			optionNames = _inputMethodNames;
			break;
		}
	}

	// Generation values
	const string fontPath = "Engine\\Fonts\\futura.ttf";
	const float maxY = 4.5f;
	const float minX = -8.0f;
	const float xOffset = 5.0f;
	const float yOffset = 0.7f;
	vec3 headerPosition = vec3(minX + (xOffset * listIndex), 5.0f, 0.5f);

	// Header generation
	_fe3d.gameEntity_add(std::to_string(listIndex) + "_header", "Engine\\OBJs\\crate.obj", headerPosition,
		vec3(0.0f), vec3(headerName.size() * 0.275f, 0.75f, 0.5f));
	_fe3d.gameEntity_setDiffuseMap(std::to_string(listIndex) + "_header", "Engine\\Textures\\crate.png");
	_fe3d.billBoardEntity_add(std::to_string(listIndex) + "_header", headerName, fontPath, vec3(0.0f, 0.5f, 0.0f), headerPosition + vec3(0.0f, 0.25f, 0.05f),
		vec3(0.0f), vec2(headerName.size() * 0.4f, 1.0f), 0, 0);

	// Choice list generation
	for (size_t i = 0; i < optionNames.size(); i++)
	{
		// Entity values
		vec3 optionPosition = vec3(minX + (xOffset * listIndex), maxY - (yOffset * (i + 1)), 0.55f);
		vec2 optionSize = vec2(optionNames[i].size() * 0.25f, _optionBillboardHeight);
		string ID = std::to_string(listIndex) + "_option_" + std::to_string(i);

		// Create new option entity
		_fe3d.billBoardEntity_add(ID, optionNames[i], fontPath, vec3(1.0f),
			optionPosition, vec3(0.0f), optionSize, 0, 0);
		_fe3d.billboardEntity_setMaxY(ID, maxY);
		_fe3d.aabbEntity_bindToBillboardEntity(ID, vec3(optionSize.x, optionSize.y, 0.1f), true);
	}

	// Add to stack
	_choiceListStack.push_back(ChoiceList(listType, optionNames.size()));
}

void ScriptEditor::_removeChoiceList()
{
	int currentListIndex = static_cast<int>(_choiceListStack.back().type);

	// Remove header
	_fe3d.gameEntity_delete(std::to_string(currentListIndex) + "_header");
	_fe3d.billboardEntity_delete(std::to_string(currentListIndex) + "_header");

	// Remove all options
	for (int i = 0; i < _choiceListStack.back().total; i++)
	{
		string ID = std::to_string(currentListIndex) + "_option_" + std::to_string(i);
		_fe3d.billboardEntity_delete(ID);
	}

	// Remove last list
	_choiceListStack.pop_back();
}