#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::update()
{
	_updateManagementScreen();
	_updateCreationScreen();
	_updateModelChoosing();
	_updateEditingScreen();
	_updateModelRemoval();
	_updateCamera();
	_updateMiscellaneous();
}

void ModelEditor::_updateManagementScreen()
{
	if (_isLoaded)
	{
		auto screen = _leftWindow->getScreen("modelEditorMenuMain");

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("addModel")->isHovered()) // Add model button
			{
				_gui->getGlobalScreen()->addValueForm("newModelName", "New model name", "", vec2(0.0f), vec2(0.5f, 0.1f));
				_modelCreationEnabled = true;
			}
			else if (screen->getButton("editModel")->isHovered()) // Edit model button
			{
				_modelChoosingEnabled = true;
				_modelEditingEnabled = true;
				for (auto& name : _modelNames) { name = name.substr(1); }
				_gui->getGlobalScreen()->addChoiceForm("modelList", "Select model", vec2(-0.4f, 0.1f), _modelNames);
				for (auto& name : _modelNames) { name = "@" + name; }
			}
			else if (screen->getButton("deleteModel")->isHovered()) // Delete model button
			{
				_modelChoosingEnabled = true;
				_modelRemovalEnabled = true;
				for (auto& name : _modelNames) { name = name.substr(1); }
				_gui->getGlobalScreen()->addChoiceForm("modelList", "Select model", vec2(-0.4f, 0.1f), _modelNames);
				for (auto& name : _modelNames) { name = "@" + name; }
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
			unload();
			_leftWindow->setActiveScreen("main");
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitModelEditor"))
		{
			unload();
			_leftWindow->setActiveScreen("main");
		}
	}
}

void ModelEditor::_updateEditingScreen()
{
	if (_modelEditingEnabled && _currentModelName != "")
	{
		static bool firstTime = true;
		auto screen = _leftWindow->getScreen("modelEditorMenuChoice");

		// Show model (name)
		if (firstTime)
		{
			firstTime = false;
			_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(),
				"Model: " + _currentModelName.substr(1), 0.025f);
			_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
			_leftWindow->setActiveScreen("modelEditorMenuChoice");
		}

		// GUI management
		if (_leftWindow->getActiveScreen()->getID() == "modelEditorMenuChoice")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("mesh")->isHovered())
				{
					_leftWindow->setActiveScreen("modelEditorMenuMesh");
				}
				else if (screen->getButton("options")->isHovered())
				{
					_leftWindow->setActiveScreen("modelEditorMenuOptions");
				}
				else if (screen->getButton("lighting")->isHovered())
				{
					_leftWindow->setActiveScreen("modelEditorMenuLighting");
				}
				else if (screen->getButton("size")->isHovered())
				{
					if (_fe3d.gameEntity_isExisting(_currentModelName))
					{
						_leftWindow->setActiveScreen("modelEditorMenuSize");
					}
				}
				else if (screen->getButton("back")->isHovered())
				{
					// Hide game entity
					if (_fe3d.gameEntity_isExisting(_currentModelName))
					{
						_fe3d.gameEntity_hide(_currentModelName);
					}

					// Reset variables and go back to last screen
					firstTime = true;
					_modelEditingEnabled = false;
					_currentModelName = "";
					_leftWindow->setActiveScreen("modelEditorMenuMain");
					_fe3d.textEntity_hide(_gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
				}
			}

			// Check if OBJ exists
			bool existing = _fe3d.gameEntity_isExisting(_currentModelName);
			bool hoverable = false;
			if (existing)
			{
				hoverable = true;

				// Show OBJ model
				_fe3d.gameEntity_show(_currentModelName);
			}

			// Editing buttons hoverability
			screen->getButton("options")->setHoverable(hoverable);
			screen->getButton("lighting")->setHoverable(hoverable);
			screen->getButton("size")->setHoverable(hoverable);
		}
		else if (_leftWindow->getActiveScreen()->getID() == "modelEditorMenuMesh")
		{
			_updateModelEditingMesh();
		}
		else if (_leftWindow->getActiveScreen()->getID() == "modelEditorMenuOptions")
		{
			_updateModelEditingOptions();
		}
		else if (_leftWindow->getActiveScreen()->getID() == "modelEditorMenuLighting")
		{
			_updateModelEditingLighting();
		}
		else if (_leftWindow->getActiveScreen()->getID() == "modelEditorMenuSize")
		{
			_updateModelEditingSize();
		}
	}
}

void ModelEditor::_updateCreationScreen()
{
	if (_isLoaded)
	{
		if (_modelCreationEnabled)
		{
			string newModelName;

			// Create new model
			if (_gui->getGlobalScreen()->checkValueForm("newModelName", newModelName, {}))
			{
				// Starting with at-sign not allowed
				if (newModelName[0] != '@')
				{
					// Add model and check if not already existing
					if (_addModel("@" + newModelName, "", "", "", "", "", vec3(0.0f), 0, 1, 0, 0, 0, 1.0f, 1.0f, 1.0f, vec3(1.0f), 1.0f, vec3(2.5f), ""))
					{
						// Go to editor screen
						_currentModelName = "@" + newModelName;
						_modelCreationEnabled = false;
						_modelEditingEnabled = true;
						_gui->getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
					}
				}
			}
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	static string hoveredModelID = "";

	if (_isLoaded)
	{
		if (_modelChoosingEnabled)
		{
			// Get selected button ID
			string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("modelList");

			// Hide last model
			if (hoveredModelID != "")
			{
				// Check if model has game entity
				if (_fe3d.gameEntity_isExisting(hoveredModelID))
				{
					_fe3d.gameEntity_hide(hoveredModelID);
				}
			}

			// Check if a model name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select selected model
					_currentModelName = "@" + selectedButtonID;
					_modelChoosingEnabled = false;
					hoveredModelID = "";
					_gui->getGlobalScreen()->removeChoiceForm("modelList");
				}
				else
				{
					// Set new hovered model
					hoveredModelID = "@" + selectedButtonID;
				}
			}
			else if (_gui->getGlobalScreen()->isChoiceFormCancelled("modelList")) // Cancelled choosing
			{
				_modelChoosingEnabled = false;
				_modelEditingEnabled = false;
				_modelRemovalEnabled = false;
				_gui->getGlobalScreen()->removeChoiceForm("modelList");
			}
			else // Nothing hovered
			{
				hoveredModelID = "";
			}

			// Show hovered model
			if (hoveredModelID != "")
			{
				// Check if model has game entity
				if (_fe3d.gameEntity_isExisting(hoveredModelID))
				{
					_fe3d.gameEntity_show(hoveredModelID);
				}
			}
		}
	}
}

void ModelEditor::_updateModelRemoval()
{
	if (_isLoaded)
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
				_modelRemovalEnabled = false;
				_currentModelName = "";
			}
		}
	}
}

void ModelEditor::_updateCamera()
{
	if (_isLoaded)
	{
		// Update cursor difference
		vec2 cursorPosition = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());
		vec2 cursorDifference = cursorPosition - _lastCursorPos;
		_lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos());

		// Update scrolling
		static float scollSpeed = 0.0f;
		if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport()) // No GUI focus and cursor must be within viewport
		{
			if (!_meshResizingToggled && !_boxResizingToggled) // No active resizing
			{
				scollSpeed += float(-_fe3d.input_getMouseWheelY() / _scrollWheelDivider); // Add scroll speed
			}
		}
		scollSpeed *= 0.975f; // Slowing down (smoothing)
		scollSpeed = std::clamp(scollSpeed, -1.0f, 1.0f);

		// Adding movement to the 3rd person view & making sure you cannot zoom inverted
		_cameraDistance += scollSpeed;
		if (_cameraDistance < 0.0f)
		{
			_cameraDistance = 0.0f;
		}

		// Check if MMB pressed
		if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport())
		{
			if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_MIDDLE))
			{
				if (_fe3d.misc_isMouseInsideViewport()) // Only if cursor inside 3d screen
				{
					_cameraAcceleration.x += cursorDifference.x * _cameraSpeed;
					_cameraAcceleration.y += cursorDifference.y * _cameraSpeed;
				}
			}
		}

		// Calculate cursor moving speed
		_cameraAcceleration *= 0.975f;
		_totalCursorDifference += _cameraAcceleration;
		_totalCursorDifference.y = std::clamp(_totalCursorDifference.y, 0.0f, 1.0f);

		// Calculate new camera position
		float x = (_cameraDistance * sin(_totalCursorDifference.x));
		float y = _minCameraHeight + (_cameraDistance * _totalCursorDifference.y);
		float z = (_cameraDistance * cos(_totalCursorDifference.x));

		// Update camera position
		_fe3d.camera_setPosition(vec3(x, y, z));
	}
}