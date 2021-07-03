#include "environment_editor.hpp"

void EnvironmentEditor::_updateWaterEditor()
{
	if (_currentEnvironmentType == EnvironmentType::WATER)
	{
		_updateWaterMenuMain();
		_updateWaterMenuChoice();
		_updateWaterMenuMesh();
		_updateWaterMenuEffects();
		_updateWaterMenuOptions();
		_updateWaterCreation();
		_updateWaterChoosing();
		_updateWaterRemoval();
		_updateWaterCamera();
	}
}

void EnvironmentEditor::_updateWaterCreation()
{
	if (_isEditorLoaded)
	{
		if (_isWaterCreationEnabled)
		{
			string newWaterName;

			// Create new water
			if (_gui.getGlobalScreen()->checkValueForm("newWaterName", newWaterName, {}))
			{
				// @ sign not allowed
				if (newWaterName.find('@') == string::npos)
				{
					// Spaces not allowed
					if (newWaterName.find(' ') == string::npos)
					{
						// Add @ sign to new name
						newWaterName = "@" + newWaterName;

						// If water name not existing yet
						if (std::find(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), newWaterName) == _loadedWaterIDs.end())
						{
							_currentWaterID = newWaterName;
							_loadedWaterIDs.push_back(_currentWaterID);
							_fe3d.waterEntity_add(_currentWaterID);
							_fe3d.waterEntity_select(_currentWaterID);
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(),
								"Water: " + _currentWaterID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(), true);
							_isWaterCreationEnabled = false;
							_isWaterEditingEnabled = true;
						}
						else
						{
							_fe3d.logger_throwWarning("Water name \"" + newWaterName.substr(1) + "\" already exists!");
						}
					}
					else
					{
						_fe3d.logger_throwWarning("Water name cannot contain any spaces!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("Water name cannot contain '@'!");
				}
			}
		}
	}
}

void EnvironmentEditor::_updateWaterChoosing()
{
	if (_isEditorLoaded)
	{
		if (_isWaterChoosingEnabled)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("waterList");

			// Hide last water
			if (_hoveredWaterID != "")
			{
				_fe3d.waterEntity_select("");
			}

			// Check if a water name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select water
					_currentWaterID = "@" + selectedButtonID;
					_hoveredWaterID = "";

					// Only if going to editor
					if (_isWaterEditingEnabled)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

						// Show water name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(),
							"Water: " + _currentWaterID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(), true);
					}

					// Show entity
					_fe3d.waterEntity_select(_currentWaterID);

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("waterList");
					_isWaterChoosingEnabled = false;
				}
				else
				{
					// Set new hovered water
					_hoveredWaterID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("waterList")) // Cancelled choosing
			{
				_isWaterChoosingEnabled = false;
				_isWaterEditingEnabled = false;
				_isWaterRemovalEnabled = false;
				_gui.getGlobalScreen()->removeChoiceForm("waterList");
			}
			else // Nothing hovered
			{
				_hoveredWaterID = "";
			}

			// Show hovered water
			if (_hoveredWaterID != "")
			{
				_fe3d.waterEntity_select(_hoveredWaterID);
			}
		}
	}
}

void EnvironmentEditor::_updateWaterRemoval()
{
	if (_isEditorLoaded)
	{
		if (_isWaterRemovalEnabled && _currentWaterID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("removeWater", "Are you sure?", Vec2(0.0f, 0.25f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("removeWater"))
			{
				// Delete entity
				_fe3d.waterEntity_delete(_currentWaterID);

				// Delete from name record
				_loadedWaterIDs.erase(std::remove(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), _currentWaterID), _loadedWaterIDs.end());
				_isWaterRemovalEnabled = false;
				_currentWaterID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("removeWater"))
			{
				_fe3d.waterEntity_select("");
				_isWaterRemovalEnabled = false;
				_currentWaterID = "";
			}
		}
	}
}

void EnvironmentEditor::_updateWaterCamera()
{
	if (_isEditorLoaded)
	{
		// Check if water is active
		if ((_currentWaterID != "" && _fe3d.waterEntity_isExisting(_currentWaterID)) || 
			(_hoveredWaterID != "" && _fe3d.waterEntity_isExisting(_hoveredWaterID)))
		{
			// Temporary values
			auto waterID = ((_currentWaterID != "") ? _currentWaterID : _hoveredWaterID);

			// Get scroll wheel input
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				float rotationAcceleration = static_cast<float>(_fe3d.input_getMouseWheelY()) / SCROLL_WHEEL_DIVIDER;
				_cameraAcceleration += rotationAcceleration;
			}

			// Apply camera smoothing & rotation
			_cameraAcceleration *= 0.975f;
			_totalCameraRotation += _cameraAcceleration;

			// Calculate new camera position
			Vec3 waterPosition = _fe3d.waterEntity_getPosition(waterID);
			float waterSize = _fe3d.waterEntity_getSize(waterID);
			float x = waterPosition.x + (waterSize / 2.0f) * sin(_totalCameraRotation);
			float y = waterPosition.y + (waterSize / 8.0f);
			float z = waterPosition.z + (waterSize / 2.0f) * cos(_totalCameraRotation);

			// Update camera
			if (!_fe3d.camera_isLookatViewEnabled())
			{
				_fe3d.camera_enableLookatView();
			}
			_fe3d.camera_setPosition(Vec3(x, y, z));
			_fe3d.camera_setLookatPosition(waterPosition);
		}
		else
		{
			// Set default camera view
			if (_fe3d.camera_isLookatViewEnabled())
			{
				_fe3d.camera_disableLookatView();
				_fe3d.camera_setPosition(Vec3(0.0f));
				_fe3d.camera_setLookatPosition(Vec3(0.0f));
				_totalCameraRotation = 0.0f;
				_cameraAcceleration = 0.0f;
			}
		}
	}
}