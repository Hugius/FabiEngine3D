#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::update()
{
	if (_isLoaded)
	{
		_updateModelManagement();
		_updateModelCreation();
		_updateModelChoosing();
		_updateModelEditing();
		_updateModelRemoval();
		_updateMiscellaneous();
	}
}

void ModelEditor::_updateModelManagement()
{
	auto screen = _window->getScreen("modelManagement");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("addModel")->isHovered()) // Add model button
		{
			_gui->getGlobalScreen()->addValueForm("newModelName", "New model name", "", vec2(0.0f)); 
			_modelCreationEnabled = true;
		}
		else if (screen->getButton("editModel")->isHovered()) // Edit model button
		{
			_modelChoosingEnabled = true;
			_modelEditingEnabled = true;
			_gui->getGlobalScreen()->addChoiceForm("modelList", "Select mode;", vec2(0.0f), _modelNames);
		}
		else if (screen->getButton("deleteModel")->isHovered()) // Delete model button
		{
			_modelChoosingEnabled = true;
			_modelRemovalEnabled = true;
			_gui->getGlobalScreen()->addChoiceForm("modelList", "Select mode;", vec2(0.0f), _modelNames);
		}
		else if (screen->getButton("back")->isHovered()) // Back button
		{
			_gui->getGlobalScreen()->addAnswerForm("exitModelEditor", "Save changes?", vec2(0.0f, 0.25f));
		}
	}

	// Check if user wants to save changes
	if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitModelEditor"))
	{
		save();
		_window->setActiveScreen("main");
		unload();
	}
	else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitModelEditor"))
	{
		_window->setActiveScreen("main");
		unload();
	}
}

void ModelEditor::_updateModelCreation()
{
	if (_modelCreationEnabled)
	{
		string modelName;

		// Create new model
		if (_gui->getGlobalScreen()->checkValueForm("newModelName", modelName))
		{
			// Add model
			_addModel(modelName, "", "", "", "", vec3(0.0f), 0, 1, 0, 0, vec3(1.0f), 1.0f, vec3(1.0f));

			// Go to editor screen
			_currentModelName = modelName;
			_modelCreationEnabled = false;
			_modelEditingEnabled = true;
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelEditingMain");
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	if (_modelChoosingEnabled)
	{
		string clickedButtonID = _gui->getGlobalScreen()->getClickedChoiceFormButtonID("modelList");

		if (clickedButtonID != "")
		{
			_currentModelName = clickedButtonID;
			_modelChoosingEnabled = false;
		}
		else
		{
			if (_gui->getGlobalScreen()->isChoiceFormCancelled("modelList"))
			{
				_modelChoosingEnabled = false;
				_modelEditingEnabled = false;
				_modelRemovalEnabled = false;
				_gui->getGlobalScreen()->removeChoiceForm("modelList");
			}
		}
	}
}

void ModelEditor::_updateModelRemoval()
{
	if (_modelRemovalEnabled && _currentModelName != "")
	{
		_gui->getGlobalScreen()->addAnswerForm("removeModel", "Are you sure?", vec2(0.0f));

		if (_gui->getGlobalScreen()->isAnswerFormConfirmed("removeModel"))
		{
			if (_fe3d.gameEntity_isExisting(_currentModelName))
			{
				_fe3d.gameEntity_delete(_currentModelName);
			}

			_modelNames.erase(std::remove(_modelNames.begin(), _modelNames.end(), _currentModelName), _modelNames.end());
			_modelRemovalEnabled = false;
			_currentModelName = "";
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("removeModel"))
		{
			_modelChoosingEnabled = true;
			_currentModelName = "";
		}
	}
}