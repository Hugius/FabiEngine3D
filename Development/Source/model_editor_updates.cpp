#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::update(float delta)
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
			_gui->getGlobalScreen()->addTextfield("newModelName", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Enter model name:", vec3(1.0f));
			_gui->getGlobalScreen()->addWriteField("newModelName", vec2(0.0f, 0.0f), vec2(0.5f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 0, 1, 0);
			_gui->getGlobalScreen()->getWriteField("newModelName")->setPermActive(true);
			_gui->getGlobalScreen()->addButton("done", vec2(-0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));
			_gui->getGlobalScreen()->addButton("cancel", vec2(0.15f, -0.2f), vec2(0.15f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "Cancel", vec3(1.0f), vec3(0.0f));
			_gui->getGlobalScreen()->setFocus(true);
			_modelCreationEnabled = true;
		}
		else if (screen->getButton("editModel")->isHovered()) // Edit model button
		{
			_modelEditingEnabled = true;
			_window->setActiveScreen("modelChoice");
		}
		else if (screen->getButton("deleteModel")->isHovered()) // Deelete model button
		{
			_modelRemovalEnabled = true;
			_window->setActiveScreen("modelChoice");
		}
		else if (screen->getButton("back")->isHovered()) // Back button
		{
			_gui->getGlobalScreen()->addAnswerForm("exitModelEditor", "Save changes?", vec2(0.0f, 0.25f));
		}
	}

	// Check if user wants to save changes
	if (_gui->getGlobalScreen()->checkAnswerFormConfirmed("exitModelEditor"))
	{
		save();
		_window->setActiveScreen("main");
		unload();
	}
	else if (_gui->getGlobalScreen()->checkAnswerFormDeclined("exitModelEditor"))
	{
		_window->setActiveScreen("main");
		unload();
	}
}

void ModelEditor::_updateModelCreation()
{
	if (_modelCreationEnabled)
	{
		bool done = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && _gui->getGlobalScreen()->getButton("done")->isHovered();
		bool entered = _gui->getGlobalScreen()->getWriteField("newModelName")->confirmedInput();
		bool cancelled = _fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && _gui->getGlobalScreen()->getButton("cancel")->isHovered();
		bool escaped = _gui->getGlobalScreen()->getWriteField("newModelName")->cancelledInput();
		bool cleanup = false;

		// Check if pressed ESCAPE or ENTER
		if (done || entered || cancelled || escaped)
		{
			// Extract new name
			string modelName = _gui->getGlobalScreen()->getWriteField("newModelName")->getTextContent();

			// Create new project
			if (done || entered)
			{
				if (modelName != "")
				{
					cleanup = true;

					// Add model
					_addModel(modelName, "", "", "", "", vec3(0.0f), 0, 1, 0, 0, vec3(1.0f), 1.0f, vec3(1.0f));

					// Go to editor screen
					_currentModelName = modelName;
					_modelEditingEnabled = true;
					_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelEditingMain");
				}
			}
			else
			{
				cleanup = true;
			}

			// Cleanup
			if (cleanup)
			{
				_modelCreationEnabled = false;
				_gui->getGlobalScreen()->setFocus(false);
				_gui->getGlobalScreen()->deleteTextfield("newModelName");
				_gui->getGlobalScreen()->deleteWriteField("newModelName");
				_gui->getGlobalScreen()->deleteButton("done");
				_gui->getGlobalScreen()->deleteButton("cancel");
			}
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	auto choiceScreen = _window->getScreen("modelChoice");

	// Check if LMB is pressed
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		// Check which model has been chosen
		for (auto& modelName : _modelNames)
		{
			if (choiceScreen->getScrollingList("modelList")->getButton(modelName)->isHovered())
			{
				// Set new current model name
				_currentModelName = modelName;

				// Send user to editing screen
				if (_modelEditingEnabled)
				{
					// Show model name
					_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID(), "Model: " + modelName);
					_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("currentModelName")->getEntityID());

					// Go to editing screen
					_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelEditingMain");
				}
				else if (_modelRemovalEnabled) // Add confirmation choice
				{
					_gui->getGlobalScreen()->addTextfield("areYouSure", vec2(0.0f, 0.1f), vec2(0.3f, 0.1f), "Are you sure?", vec3(1.0f));
					_gui->getGlobalScreen()->addButton("yes", vec2(-0.1f, -0.1f), vec2(0.1f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Yes", vec3(1.0f), vec3(0.0f));
					_gui->getGlobalScreen()->addButton("no", vec2(0.1f, -0.1f), vec2(0.1f, 0.1f), vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), "No", vec3(1.0f), vec3(0.0f));
				}
			}
		}

		// Back button
		if (choiceScreen->getButton("back")->isHovered())
		{
			_modelEditingEnabled = false;
			_modelRemovalEnabled = false;
			_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelManagement");
		}
	}
}

void ModelEditor::_updateModelRemoval()
{
	if (_modelRemovalEnabled)
	{
		if (_currentModelName != "")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (_gui->getGlobalScreen()->getButton("yes")->isHovered()) // Confirmed
				{
					// Remove game entity
					if (_fe3d.gameEntity_isExisting(_currentModelName))
					{
						_fe3d.gameEntity_delete(_currentModelName);
					}

					// Delete from model names vector
					for (size_t i = 0; i < _modelNames.size(); i++)
					{
						if (_modelNames[i] == _currentModelName)
						{
							_modelNames.erase(_modelNames.begin() + i);
						}
					}

					// Delete choice button and go back to management screen
					_gui->getViewport("left")->getWindow("main")->getScreen("modelChoice")->getScrollingList("modelList")->deleteButton(_currentModelName);
					_currentModelName = "";

					// Delete confirmation GUI
					_gui->getGlobalScreen()->deleteTextfield("areYouSure");
					_gui->getGlobalScreen()->deleteButton("yes");
					_gui->getGlobalScreen()->deleteButton("no");
				}
				else if (_gui->getGlobalScreen()->getButton("no")->isHovered()) // Cancelled
				{
					_currentModelName = "";

					// Delete confirmation GUI
					_gui->getGlobalScreen()->deleteTextfield("areYouSure");
					_gui->getGlobalScreen()->deleteButton("yes");
					_gui->getGlobalScreen()->deleteButton("no");
				}
			}
		}
	}
}