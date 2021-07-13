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
		_updateSkyCreation();
		_updateSkyChoosing();
		_updateSkyRemoval();
		_updateSkyCamera();
	}
}

void EnvironmentEditor::_updateSkyCreation()
{
	if (_isEditorLoaded)
	{
		if (_isSkyCreationEnabled)
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
							_fe3d.skyEntity_add(_currentSkyID);
							_fe3d.skyEntity_select(_currentSkyID);
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(),
								"Sky: " + _currentSkyID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(), true);
							_isSkyCreationEnabled = false;
							_isSkyEditingEnabled = true;
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
		if (_isSkyChoosingEnabled)
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
					if (_isSkyEditingEnabled)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

						// Show sky name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(),
							"Sky: " + _currentSkyID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedSkyName")->getEntityID(), true);
					}

					// Show entity
					_fe3d.skyEntity_select(_currentSkyID);

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("skyList");
					_isSkyChoosingEnabled = false;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("skyList")) // Cancelled choosing
			{
				_isSkyChoosingEnabled = false;
				_isSkyEditingEnabled = false;
				_isSkyRemovalEnabled = false;
				_gui.getGlobalScreen()->removeChoiceForm("skyList");
			}
		}
	}
}

void EnvironmentEditor::_updateSkyRemoval()
{
	if (_isEditorLoaded)
	{
		if (_isSkyRemovalEnabled && _currentSkyID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("delete", "Are you sure?", Vec2(0.0f, 0.25f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
			{
				// Delete entity
				_fe3d.skyEntity_delete(_currentSkyID);

				// Delete from name record
				_loadedSkyIDs.erase(std::remove(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), _currentSkyID), _loadedSkyIDs.end());
				_isSkyRemovalEnabled = false;
				_currentSkyID = "";

				// Default sky
				_fe3d.skyEntity_select("@@engineBackground");
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
			{
				// Default sky
				_fe3d.skyEntity_select("@@engineBackground");

				// Miscellaneous
				_isSkyRemovalEnabled = false;
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