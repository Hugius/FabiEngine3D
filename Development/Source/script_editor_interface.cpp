#include "script_editor.hpp"

void ScriptEditor::_generateScriptLineOverview(ScriptLine& scriptLine)
{
	// Clear all previous choice lists
	_clearChoiceLists();

	// Check if script line has event
	if (scriptLine.event != nullptr)
	{
		_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_TYPES, static_cast<int>(scriptLine.event->getType()));

		if (scriptLine.event->getType() == ScriptEventType::INITIALIZATION)
		{

		}
		else if (scriptLine.event->getType() == ScriptEventType::INPUT)
		{
			auto inputEvent = dynamic_pointer_cast<ScriptEventInput>(scriptLine.event);
			
			_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::INPUT_TYPES, static_cast<int>(inputEvent->getInputType()));
			
			// Determine input type
			if (inputEvent->getInputType() == InputType::KEYBOARD)
			{
				_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::INPUT_KEY_NAMES, inputEvent->getInputElementIndex());
			}
			else if (inputEvent->getInputType() == InputType::MOUSE)
			{
				_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::INPUT_KEY_NAMES, inputEvent->getInputElementIndex());
			}
			_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::INPUT_METHODS, static_cast<int>(inputEvent->getInputMethod()));
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

		}
	}
}

void ScriptEditor::_addChoiceList(ChoiceListSort listSort, ChoiceListType listType, int activeIndex)
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
	const string fontPath = "Engine\\Fonts\\lucida.ttf";
	const float maxY = 4.5f;
	const float minX = -8.0f;
	const float xOffset = 7.5f;
	const float yOffset = 0.7f;
	vec3 headerPosition = vec3(minX + (xOffset * _choiceListStack.size()), 5.0f, 0.5f);
	
	// Header generation
	_fe3d.gameEntity_add(std::to_string(listIndex) + "_header", "Engine\\OBJs\\crate.obj", headerPosition,
		vec3(0.0f), vec3(headerName.size() * 0.275f, 0.75f, 0.5f));
	_fe3d.gameEntity_setDiffuseMap(std::to_string(listIndex) + "_header", "Engine\\Textures\\crate.png");
	_fe3d.billBoardEntity_add(std::to_string(listIndex) + "_header", headerName, fontPath, vec3(0.0f, 0.5f, 0.0f), headerPosition + vec3(0.0f, 0.25f, 0.05f),
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
		string ID = std::to_string(listIndex) + "_option_" + std::to_string(i);
		
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
		_choiceListStack.push_back(ChoiceList(listSort, listType, optionNames.size()));
	}
	else
	{
		_choiceListStack.push_back(ChoiceList(listSort, listType, optionNames[activeIndex].size()));
	}
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
	for (unsigned int i = 0; i < _pointLightCounter; i++)
	{
		if (_fe3d.lightEntity_isExisting(std::to_string(i)))
		{
			_fe3d.lightEntity_delete(std::to_string(i));
		}
	}

	// Default camera position
	_fe3d.camera_setPosition(_cameraStartingPosition);
}
