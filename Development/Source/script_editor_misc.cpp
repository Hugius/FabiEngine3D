#include "script_editor.hpp"

#include <algorithm>

void ScriptEditor::_unloadScript()
{
	_script = nullptr;
	_scriptExecutor = nullptr;
}

shared_ptr<ScriptExecutor> ScriptEditor::getScriptExecutor()
{
	// Check if script is loaded yet
	if (_scriptExecutor == nullptr)
	{
		_loadScriptFromFile();
	}
	
	return _scriptExecutor;
}

void ScriptEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool ScriptEditor::isLoaded()
{
	return _isLoaded;
}

void ScriptEditor::_calibrateScriptLines()
{
	auto scriptLineIDs = _script->getAllScriptLineIDs();
	int counter = 1;

	// Change all IDs (line numbers) accordingly
	for (auto& ID : scriptLineIDs)
	{
		_script->getScriptLine(ID).ID = to_string(counter);
		counter++;
	}
}

void ScriptEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		//  Smooth scrolling movement
		_scrollingAcceleration *= 0.95f;

		if (!_gui->getGlobalScreen()->isFocused())
		{
			// Camear movement input
			if (_fe3d.input_getKeyDown(Input::KEY_A))
			{
				_cameraAcceleration -= 0.005f;
			}
			else if (_fe3d.input_getKeyDown(Input::KEY_D))
			{
				_cameraAcceleration += 0.005f;
			}
		}

		// Smooth camera movement
		_cameraAcceleration = std::clamp(_cameraAcceleration, -0.3f, 0.3f);
		_cameraAcceleration *= 0.965f;

		// Cannot go out of screen
		if (_fe3d.camera_getPosition().x < _cameraStartingPosition.x)
		{
			_cameraAcceleration = 0.0f;
			_fe3d.camera_setPosition(_cameraStartingPosition);
		}

		// Move camera
		_fe3d.camera_translate(vec3(_cameraAcceleration, 0.0f, 0.0f));

		// Add & delete buttons hoverability
		_leftWindow->getScreen("scriptEditorMenuMain")->getButton("addLine")->setHoverable(_allowedToAddScriptLine);
		_leftWindow->getScreen("scriptEditorMenuMain")->getButton("updateLine")->setHoverable(_currentScriptLineID != "");
		_leftWindow->getScreen("scriptEditorMenuMain")->getButton("deleteLine")->setHoverable(_currentScriptLineID != "");
		_leftWindow->getScreen("scriptEditorMenuVariables")->getButton("addVariable")->setHoverable(_allowedToAddScriptVariable);
		_leftWindow->getScreen("scriptEditorMenuVariables")->getButton("updateVariable")->setHoverable(_currentScriptVariableID != "");
		_leftWindow->getScreen("scriptEditorMenuVariables")->getButton("deleteVariable")->setHoverable(_currentScriptVariableID != "");

		// Check if user filled in a name for new variable
		string newName;
		if (_gui->getGlobalScreen()->checkValueForm("variableName", newName, {}))
		{
			// Check if variable name not existing yet
			bool unique = true;
			for (auto& existingName : _script->getAllScriptVariableIDs())
			{
				if (newName == existingName)
				{
					unique = false;
				}
			}

			// Add default choicelist
			if (unique)
			{
				_clearChoiceLists();
				_addChoiceList(ChoiceListSort::VARIABLE, ChoiceListType::VARIABLE_CONSTANT);
				_isCreatingScriptVariable = true;
				_allowedToAddScriptVariable = false;
				_newScriptVariableID = newName;
			}
		}

		// Check if existing script line chosen for viewing
		string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("scriptLinesList");
		if (selectedButtonID != "")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				_generateScriptLineOverview(_script->getScriptLine(selectedButtonID));
				_gui->getGlobalScreen()->removeChoiceForm("scriptLinesList");
				_currentScriptLineID = selectedButtonID;
				_isCreatingScriptLine = false;
				_allowedToAddScriptLine = false;
			}
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("scriptLinesList"))
		{
			_gui->getGlobalScreen()->removeChoiceForm("scriptLinesList");
		}

		// Check if existing script variable chosen for viewing
		selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("scriptVariablesList");
		if (selectedButtonID != "")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				_generateScriptVariableOverview(_script->getScriptVariable(selectedButtonID));
				_gui->getGlobalScreen()->removeChoiceForm("scriptVariablesList");
				_currentScriptVariableID = selectedButtonID;
				_isCreatingScriptVariable = false;
				_allowedToAddScriptVariable = false;
			}
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("scriptVariablesList"))
		{
			_gui->getGlobalScreen()->removeChoiceForm("scriptVariablesList");
		}
	}
}