#include "environment_editor.hpp"
#include "logger.hpp"

void EnvironmentEditor::_updateWaterEditor()
{
	if (_currentEnvironmentType == EnvironmentType::WATER)
	{
		_updateWaterMenuMain();
		_updateWaterMenuChoice();
		_updateWaterMenuMesh();
		_updateWaterMenuEffects();
		_updateWaterMenuOptions();
		_updateWaterCreating();
		_updateWaterChoosing();
		_updateWaterDeleting();
		_updateWaterCamera();
	}
}

void EnvironmentEditor::_updateWaterCreating()
{
	if (_isEditorLoaded)
	{
		if (_isCreatingWater)
		{
			string newWaterName;

			// Create new water
			if (_gui.getGlobalScreen()->checkValueForm("waterCreate", newWaterName, {}))
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
							_fe3d.waterEntity_create(_currentWaterID);
							_fe3d.waterEntity_select(_currentWaterID);
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuWaterChoice");
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(),
								"Water: " + _currentWaterID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(), true);
							_isCreatingWater = false;
							_isEditingWater = true;
						}
						else
						{
							Logger::throwWarning("Water name \"" + newWaterName.substr(1) + "\" already exists!");
						}
					}
					else
					{
						Logger::throwWarning("Water name cannot contain any spaces!");
					}
				}
				else
				{
					Logger::throwWarning("Water name cannot contain '@'!");
				}
			}
		}
	}
}

void EnvironmentEditor::_updateWaterChoosing()
{
	if (_isEditorLoaded)
	{
		if (_isChoosingWater)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("waterList");

			// Check if a water name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select water
					_currentWaterID = "@" + selectedButtonID;

					// Only if going to editor
					if (_isEditingWater)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuWaterChoice");

						// Show water name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(),
							"Water: " + _currentWaterID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID(), true);
					}

					// Show entity
					_fe3d.waterEntity_select(_currentWaterID);

					// Miscellaneous
					_gui.getGlobalScreen()->deleteChoiceForm("waterList");
					_isChoosingWater = false;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("waterList")) // Cancelled choosing
			{
				_isChoosingWater = false;
				_isEditingWater = false;
				_isDeletingWater = false;
				_gui.getGlobalScreen()->deleteChoiceForm("waterList");
			}
		}
	}
}

void EnvironmentEditor::_updateWaterDeleting()
{
	if (_isEditorLoaded)
	{
		if (_isDeletingWater && _currentWaterID != "")
		{
			// Add answer form
			if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
			{
				_gui.getGlobalScreen()->addAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
			}

			// Check if form is answered
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
			{
				// Delete entity
				_fe3d.waterEntity_delete(_currentWaterID);

				// Delete from name record
				_loadedWaterIDs.erase(std::remove(_loadedWaterIDs.begin(), _loadedWaterIDs.end(), _currentWaterID), _loadedWaterIDs.end());
				_isDeletingWater = false;
				_currentWaterID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
			{
				_fe3d.waterEntity_select("");
				_isDeletingWater = false;
				_currentWaterID = "";
			}
		}
	}
}

void EnvironmentEditor::_updateWaterCamera()
{
	if (_isEditorLoaded)
	{
		// Disable third person view
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			_fe3d.camera_disableThirdPersonView();
		}

		// Check if water is inactive
		if (_currentWaterID.empty() || !_fe3d.waterEntity_isExisting(_currentWaterID))
		{
			// Reset camera
			_fe3d.camera_reset();
			_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
		}
		else
		{
			// Show cursor
			_fe3d.imageEntity_setVisible("@@cursor", true);

			// Check if allowed by GUI
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				// Check if RMB pressed
				if (_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{	
					// Enable third person view
					_fe3d.camera_enableThirdPersonView(
						_fe3d.camera_getThirdPersonYaw(),
						_fe3d.camera_getThirdPersonPitch(),
						_fe3d.camera_getThirdPersonDistance());

					// Hide cursor
					_fe3d.imageEntity_setVisible("@@cursor", false);
				}
			}
		}
	}
}