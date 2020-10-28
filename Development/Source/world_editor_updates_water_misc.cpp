#include "world_editor.hpp"

void WorldEditor::_updateWaterEditor()
{
	if (_currentWorldPart == WorldPart::WATER)
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

void WorldEditor::_updateWaterCreation()
{
	if (_isLoaded)
	{
		if (_waterCreationEnabled)
		{
			string newWaterName;

			// Create new water
			if (_gui.getGlobalScreen()->checkValueForm("newWaterName", newWaterName, {}))
			{
				// Starting with at-sign not allowed
				if (newWaterName[0] != '@')
				{
					newWaterName = "@" + newWaterName;

					// If water name not existing yet
					if (std::find(_waterNames.begin(), _waterNames.end(), newWaterName) == _waterNames.end())
					{
						_currentWaterID = newWaterName;
						_waterNames.push_back(_currentWaterID);
						_fe3d.waterEntity_add(_currentWaterID);
						_fe3d.waterEntity_select(_currentWaterID);
						_leftWindow->setActiveScreen("waterEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(),
							"Water: " + _currentWaterID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID());
						_waterCreationEnabled = false;
						_waterEditingEnabled = true;
					}
					else
					{
						_fe3d.logger_throwWarning("Water name \"" + newWaterName.substr(1) + "\" already exists!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New water name cannot begin with '@'");
				}
			}
		}
	}
}

void WorldEditor::_updateWaterChoosing()
{
	if (_isLoaded)
	{
		if (_waterChoosingEnabled)
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
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select water
					_currentWaterID = "@" + selectedButtonID;
					_hoveredWaterID = "";

					// Only if going to editor
					if (_waterEditingEnabled)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");

						// Show water name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(),
							"Water: " + _currentWaterID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID());

						// Show entity
						_fe3d.waterEntity_select(_currentWaterID);
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("waterList");
					_waterChoosingEnabled = false;
				}
				else
				{
					// Set new hovered water
					_hoveredWaterID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("waterList")) // Cancelled choosing
			{
				_waterChoosingEnabled = false;
				_waterEditingEnabled = false;
				_waterRemovalEnabled = false;
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

void WorldEditor::_updateWaterRemoval()
{
	if (_isLoaded)
	{
		if (_waterRemovalEnabled && _currentWaterID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("removeWater", "Are you sure?", vec2(0.0f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("removeWater"))
			{
				// Delete entity
				_fe3d.waterEntity_delete(_currentWaterID);

				// Delete from name record
				_waterNames.erase(std::remove(_waterNames.begin(), _waterNames.end(), _currentWaterID), _waterNames.end());
				_waterRemovalEnabled = false;
				_currentWaterID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("removeWater"))
			{
				_waterRemovalEnabled = false;
				_currentWaterID = "";
			}
		}
	}
}

void WorldEditor::_updateWaterCamera()
{
	if (_isLoaded)
	{
		// Check if a water is selected or hovered
		string waterID = (_currentWaterID != "") ? _currentWaterID : ((_hoveredWaterID != "") ? _hoveredWaterID : "");

		// Check if water entity exists
		if (_fe3d.waterEntity_isExisting(waterID))
		{
			// Get scroll wheel input
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) / _scrollWheelDivider;
				_cameraRotationSpeed += rotationAcceleration;
			}

			// Apply camera smoothing & rotation
			_cameraRotationSpeed *= 0.975f;
			_totalCameraRotation += _cameraRotationSpeed;

			// Calculate new camera position
			vec3 waterPosition = _fe3d.waterEntity_getPosition(waterID);
			float waterSize = _fe3d.waterEntity_getSize(waterID);
			float x = waterPosition.x + (waterSize / 2.0f) * sin(_totalCameraRotation);
			float y = waterPosition.y + (waterPosition.y + (waterSize / 16.0f));
			float z = waterPosition.z + (waterSize / 2.0f) * cos(_totalCameraRotation);

			// Update camera position
			_fe3d.camera_setPosition(vec3(x, y, z));
			_fe3d.camera_enableLookat(waterPosition);
		}
	}
}