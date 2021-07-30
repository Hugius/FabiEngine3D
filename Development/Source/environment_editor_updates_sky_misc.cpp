#include "environment_editor.hpp"
#include "logger.hpp"

void EnvironmentEditor::_updateSkyEditor()
{
	if (_currentEnvironmentType == EnvironmentType::SKY)
	{
		_updateSkyMenuMain();
		_updateSkyMenuChoice();
		_updateSkyMenuMesh();
		_updateSkyMenuOptions();
		_updateSkyCreating();
		_updateSkyChoosing();
		_updateSkyDeleting();
		_updateSkyCamera();
	}
}

void EnvironmentEditor::_updateSkyCreating()
{
	if (_isEditorLoaded)
	{
		if (_isCreatingSky)
		{
			string newSkyName;

			// Create new sky
			if (_gui.getGlobalScreen()->checkValueForm("skyCreate", newSkyName, {}))
			{
				// @ sign not allowed
				if (newSkyName.find('@') == string::npos)
				{
					// Spaces not allowed
					if (newSkyName.find(' ') == string::npos)
					{
						// Add @ sign to new name
						newSkyName = "@" + newSkyName;

						// If sky name not existing yet
						if (std::find(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), newSkyName) == _loadedSkyIDs.end())
						{
							_currentSkyID = newSkyName;
							_loadedSkyIDs.push_back(_currentSkyID);
							_fe3d.skyEntity_create(_currentSkyID);
							_fe3d.skyEntity_select(_currentSkyID);
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuSkyChoice");
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(),
								"Sky: " + _currentSkyID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(), true);
							_isCreatingSky = false;
							_isEditingSky = true;
						}
						else
						{
							Logger::throwWarning("Sky name \"" + newSkyName.substr(1) + "\" already exists!");
						}
					}
					else
					{
						Logger::throwWarning("Sky name cannot contain any spaces!");
					}
				}
				else
				{
					Logger::throwWarning("Sky name cannot contain '@'!");
				}
			}
		}
	}
}

void EnvironmentEditor::_updateSkyChoosing()
{
	if (_isEditorLoaded)
	{
		if (_isChoosingSky)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("skyList");

			// Check if a sky name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select sky
					_currentSkyID = "@" + selectedButtonID;

					// Only if going to editor
					if (_isEditingSky)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuSkyChoice");

						// Show sky name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(),
							"Sky: " + _currentSkyID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(), true);
					}

					// Show entity
					_fe3d.skyEntity_select(_currentSkyID);

					// Miscellaneous
					_gui.getGlobalScreen()->deleteChoiceForm("skyList");
					_isChoosingSky = false;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("skyList")) // Cancelled choosing
			{
				_isChoosingSky = false;
				_isEditingSky = false;
				_isDeletingSky = false;
				_gui.getGlobalScreen()->deleteChoiceForm("skyList");
			}
		}
	}
}

void EnvironmentEditor::_updateSkyDeleting()
{
	if (_isEditorLoaded)
	{
		if (_isDeletingSky && _currentSkyID != "")
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
				_fe3d.skyEntity_delete(_currentSkyID);

				// Delete from name record
				_loadedSkyIDs.erase(std::remove(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), _currentSkyID), _loadedSkyIDs.end());
				_isDeletingSky = false;
				_currentSkyID = "";

				// Enable engine background
				_fe3d.skyEntity_select("@@engineBackground");
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
			{
				// Enable engine background
				_fe3d.skyEntity_select("@@engineBackground");

				// Miscellaneous
				_isDeletingSky = false;
				_currentSkyID = "";
			}
		}
	}
}

void EnvironmentEditor::_updateSkyCamera()
{
	if (_isEditorLoaded)
	{
		// Disable first person view
		if (_fe3d.camera_isFirstPersonViewEnabled())
		{
			_fe3d.camera_disableFirstPersonView();
		}

		// Check if sky is inactive
		if (_currentSkyID.empty() || !_fe3d.skyEntity_isExisting(_currentSkyID))
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
					// Enable first person view
					_fe3d.camera_enableFirstPersonView(_fe3d.camera_getFirstPersonYaw(), _fe3d.camera_getFirstPersonPitch());
					
					// Hide cursor
					_fe3d.imageEntity_setVisible("@@cursor", false);
				}
			}
		}
	}
}