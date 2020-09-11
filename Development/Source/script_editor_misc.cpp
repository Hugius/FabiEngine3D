#include "script_editor.hpp"

void ScriptEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool ScriptEditor::isLoaded()
{
	return _isLoaded;
}

void ScriptEditor::addChoiceList(ChoiceListType listType)
{
	// Check if not already generated yet
	if (std::find(_choiceListStack.begin(), _choiceListStack.end(), listType) == _choiceListStack.end())
	{
		// General variables
		_choiceListStack.push_back(std::make_pair(listType, -1));
		int listIndex = static_cast<int>(listType);
		string headerName;
		vector<string> optionNames;

		// Determine list to be generated
		switch (listType)
		{
		case ChoiceListType::EVENT_TYPES:
			headerName = "Event type";
			optionNames = _eventTypeNames;
			break;
		case ChoiceListType::INPUT_TYPES:
			headerName = "Input type";
			optionNames = _inputTypeNames;
			break;
		case ChoiceListType::INPUT_KEY_NAMES:
			headerName = "Keyboard key";
			optionNames = _inputKeyNames;
			break;
		case ChoiceListType::INPUT_MOUSE_NAMES:
			headerName = "Mouse button";
			optionNames = _inputMouseNames;
			break;
		}

		// Generation values
		const string fontPath = "Engine\\Fonts\\futura.ttf";
		const float maxY = 4.5f;
		const float minX = -8.0f;
		const float xOffset = 4.0f;
		const float yOffset = 0.7f;
		vec3 headerPosition = vec3(minX + (xOffset * listIndex), 5.0f, 0.5f);

		// Header generation
		_fe3d.gameEntity_add(std::to_string(listIndex) + "_header", "Engine\\OBJs\\crate.obj", headerPosition,
			vec3(0.0f), vec3(headerName.size() * 0.25f, 0.75f, 0.5f));
		_fe3d.gameEntity_setDiffuseMap(std::to_string(listIndex) + "_header", "Engine\\Textures\\crate.png");
		_fe3d.billBoardEntity_add(std::to_string(listIndex) + "_header", headerName, fontPath, vec3(1.0f), headerPosition + vec3(0.0f, 0.25f, 0.05f),
			vec3(0.0f), vec2(headerName.size() * 0.4f, 1.0f), 0, 0);

		// Choice list generation
		for (size_t i = 0; i < optionNames.size(); i++)
		{
			vec3 optionPosition = vec3(minX + (xOffset * listIndex), maxY - (yOffset * (i + 1)), 0.55f);
			vec2 optionSize = vec2(optionNames[i].size() * 0.25f, 0.75f);

			_fe3d.billBoardEntity_add(std::to_string(listIndex) + "_option_" + std::to_string(i), optionNames[i], fontPath, vec3(1.0f),
				optionPosition, vec3(0.0f), optionSize, 0, 0);
			_fe3d.aabbEntity_add(std::to_string(listIndex) + "_option_" + std::to_string(i), optionPosition, vec3(optionSize.x, optionSize.y, 0.1f), true);
		}
	}
}

void ScriptEditor::removeChoiceList()
{
	if (_choiceListStack.size() > 1)
	{
		// Remove last list
		auto currentChoiceList = _choiceListStack.back();
		int currentListID = static_cast<int>(currentChoiceList.first);
		_choiceListStack.pop_back();

		// Remove header
		_fe3d.gameEntity_delete(std::to_string(currentListID) + "_header");
		_fe3d.billboardEntity_delete(std::to_string(currentListID) + "_header");

		// Remove all options
		for (auto& ID : _fe3d.billboardEntity_getAllIDs())
		{
			if (ID.substr(0, std::to_string(currentListID).size()) == std::to_string(currentListID))
			{
				_fe3d.billboardEntity_delete(ID);
				_fe3d.aabbEntity_delete(ID);
			}
		}
	}
}