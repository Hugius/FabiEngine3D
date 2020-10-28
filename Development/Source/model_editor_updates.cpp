#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::update()
{
	_updateManagementScreen();
	_updateModelCreation();
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
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("modelEditorMenuMain");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("addModel")->isHovered()) // Add model button
			{
				_gui.getGlobalScreen()->addValueForm("newModelName", "New model name", "", vec2(0.0f), vec2(0.5f, 0.1f));
				_isCreatingModel = true;
			}
			else if (screen->getButton("editModel")->isHovered()) // Edit model button
			{
				_isChoosingModel = true;
				_isEditingModel = true;
				for (auto& name : _modelNames) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("models", "Select model", vec2(-0.4f, 0.1f), _modelNames);
				for (auto& name : _modelNames) { name = "@" + name; }
			}
			else if (screen->getButton("deleteModel")->isHovered()) // Delete model button
			{
				_isChoosingModel = true;
				_isDeletingModel = true;
				for (auto& name : _modelNames) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("models", "Select model", vec2(-0.4f, 0.1f), _modelNames);
				for (auto& name : _modelNames) { name = "@" + name; }
			}
			else if (screen->getButton("back")->isHovered()) // Back button
			{
				_gui.getGlobalScreen()->addAnswerForm("exitModelEditor", "Save changes?", vec2(0.0f, 0.25f));
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitModelEditor"))
		{
			save();
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
		}
		else if (_gui.getGlobalScreen()->isAnswerFormCancelled("exitModelEditor"))
		{
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
		}
	}
}

void ModelEditor::_updateEditingScreen()
{
	if (_isEditingModel && _currentModelID != "")
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("modelEditorMenuChoice");
		
		// GUI management
		if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "modelEditorMenuChoice")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("mesh")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuMesh");
				}
				else if (screen->getButton("options")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuOptions");
				}
				else if (screen->getButton("lighting")->isHovered())
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuLighting");
				}
				else if (screen->getButton("size")->isHovered())
				{
					if (_fe3d.gameEntity_isExisting(_currentModelID))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuSize");
					}
				}
				else if (screen->getButton("aabb")->isHovered())
				{
					if (_fe3d.gameEntity_isExisting(_currentModelID))
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuAabb");
						_fe3d.misc_enableAabbFrameRendering();
					}
				}
				else if (screen->getButton("back")->isHovered())
				{
					// Hide game entity
					if (_fe3d.gameEntity_isExisting(_currentModelID))
					{
						_fe3d.gameEntity_hide(_currentModelID);
					}

					// Reset variables and go back to main screen
					_isEditingModel = false;
					_currentModelID = "";
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuMain");
					_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
				}
			}

			// Check if OBJ exists
			bool existing = _fe3d.gameEntity_isExisting(_currentModelID);
			bool hoverable = false;
			if (existing)
			{
				hoverable = true;

				// Show OBJ model
				_fe3d.gameEntity_show(_currentModelID);
			}

			// Editing buttons hoverability
			screen->getButton("options")->setHoverable(hoverable);
			screen->getButton("lighting")->setHoverable(hoverable);
			screen->getButton("size")->setHoverable(hoverable);
			screen->getButton("aabb")->setHoverable(hoverable && !_fe3d.gameEntity_isInstanced(_currentModelID));
		}
		else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "modelEditorMenuMesh")
		{
			_updateModelEditingMesh();
		}
		else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "modelEditorMenuOptions")
		{
			_updateModelEditingOptions();
		}
		else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "modelEditorMenuLighting")
		{
			_updateModelEditingLighting();
		}
		else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "modelEditorMenuSize")
		{
			_updateModelEditingSize();
		}
		else if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "modelEditorMenuAabb")
		{
			_updateModelEditingAabb();
		}
	}
}

void ModelEditor::_updateModelCreation()
{
	if (_isLoaded)
	{
		if (_isCreatingModel)
		{
			string newModelName;

			// Create new model
			if (_gui.getGlobalScreen()->checkValueForm("newModelName", newModelName, {}))
			{
				// Starting with at-sign not allowed
				if (newModelName[0] != '@')
				{
					// Add model and check if not already existing
					if (_addModel("@" + newModelName, "", "", "", "", "", vec3(0.0f), 0, 1, 0, 0, 0, 1.0f, 1.0f, 1.0f, vec3(1.0f), 1.0f, "", false, {}, {}, {}))
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
						
						// Select model
						_currentModelID = "@" + newModelName;

						// Miscellaneous
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(),
							"Model: " + _currentModelID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
						_isCreatingModel = false;
						_isEditingModel = true;
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New model name cannot begin with '@'");
				}
			}
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	if (_isLoaded)
	{
		if (_isChoosingModel)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("models");

			// Hide last model
			if (_hoveredModelID != "")
			{
				// Check if model has game entity
				if (_fe3d.gameEntity_isExisting(_hoveredModelID))
				{
					_fe3d.gameEntity_hide(_hoveredModelID);
				}
			}

			// Check if a model name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select modelf
					_currentModelID = "@" + selectedButtonID;
					_hoveredModelID = "";

					// Go to editor screen & show model name
					if (_isEditingModel)
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID(),
							"Model: " + _currentModelID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID());
					}

					// Check if model has game entity
					if (_fe3d.gameEntity_isExisting(_currentModelID))
					{
						_fe3d.gameEntity_show(_currentModelID);
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("models");
					_isChoosingModel = false;
				}
				else
				{
					// Set new hovered model
					_hoveredModelID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("models")) // Cancelled choosing
			{
				_isChoosingModel = false;
				_isEditingModel = false;
				_isDeletingModel = false;
				_gui.getGlobalScreen()->removeChoiceForm("models");
			}
			else // Nothing hovered
			{
				_hoveredModelID = "";
			}

			// Show hovered model
			if (_hoveredModelID != "")
			{
				// Check if model has game entity
				if (_fe3d.gameEntity_isExisting(_hoveredModelID))
				{
					_fe3d.gameEntity_show(_hoveredModelID);
				}
			}
		}
	}
}

void ModelEditor::_updateModelRemoval()
{
	if (_isLoaded)
	{
		if (_isDeletingModel && _currentModelID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("deleteModel", "Are you sure?", vec2(0.0f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("deleteModel"))
			{
				// Delete entity
				if (_fe3d.gameEntity_isExisting(_currentModelID))
				{
					_fe3d.gameEntity_delete(_currentModelID);
				}

				// Delete from name record
				_modelNames.erase(std::remove(_modelNames.begin(), _modelNames.end(), _currentModelID), _modelNames.end());
				_isDeletingModel = false;
				_currentModelID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("deleteModel"))
			{
				_isDeletingModel = false;
				_currentModelID = "";
			}
		}
	}
}

void ModelEditor::_updateCamera()
{
	if (_isLoaded)
	{
		// Update cursor difference
		vec2 cursorPosition = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition());
		vec2 cursorDifference = cursorPosition - _lastCursorPos;
		_lastCursorPos = _fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition());

		// Update scrolling
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport()) // No GUI focus and cursor must be within viewport
		{
			if (!_movingToggled && !_resizingToggled) // No active moving or resizing
			{
				_cameraScrollingAcceleration += float(-_fe3d.input_getMouseWheelY() / _scrollWheelDivider); // Add to acceleration
			}
		}
		_cameraScrollingAcceleration *= 0.975f; // Slowing down (smoothing)
		_cameraScrollingAcceleration = std::clamp(_cameraScrollingAcceleration, -1.0f, 1.0f);

		// Adding movement to the 3rd person view & making sure you cannot zoom inverted
		_cameraDistance += _cameraScrollingAcceleration;
		if (_cameraDistance < 0.0f)
		{
			_cameraDistance = 0.0f;
		}

		// Check if MMB pressed
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
			{
				if (_fe3d.misc_isCursorInsideViewport()) // Only if cursor inside 3d screen
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