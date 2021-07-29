#include "environment_editor.hpp"
#include "logger.hpp"

void EnvironmentEditor::_updateTerrainEditor()
{
	if (_currentEnvironmentType == EnvironmentType::TERRAIN)
	{
		_updateTerrainMenuMain();
		_updateTerrainMenuChoice();
		_updateTerrainMenuMesh();
		_updateTerrainMenuBlendMap();
		_updateTerrainMenuLighting();
		_updateTerrainCreating();
		_updateTerrainChoosing();
		_updateTerrainDeleting();
		_updateTerrainCamera();
	}
}

void EnvironmentEditor::_updateTerrainCreating()
{
	if (_isEditorLoaded)
	{
		if (_isCreatingTerrain)
		{
			string newTerrainName;

			// Create new terrain
			if (_gui.getGlobalScreen()->checkValueForm("terrainCreate", newTerrainName, {}))
			{
				// @ sign not allowed
				if (newTerrainName.find('@') == string::npos)
				{
					// Spaces not allowed
					if (newTerrainName.find(' ') == string::npos)
					{
						// Add @ sign to new name
						newTerrainName = "@" + newTerrainName;

						// If terrain name not existing yet
						if (std::find(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), newTerrainName) == _loadedTerrainIDs.end())
						{
							_currentTerrainID = newTerrainName;
							_loadedTerrainIDs.push_back(_currentTerrainID);
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuTerrainChoice");
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
								"Terrain: " + _currentTerrainID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(), true);
							_isCreatingTerrain = false;
							_isEditingTerrain = true;
						}
						else
						{
							Logger::throwWarning("Terrain name \"" + newTerrainName.substr(1) + "\" already exists!");
						}
					}
					else
					{
						Logger::throwWarning("Terrain name cannot contain any spaces!");
					}
				}
				else
				{
					Logger::throwWarning("Terrain name cannot contain '@'!");
				}
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainChoosing()
{
	if (_isEditorLoaded)
	{
		if (_isChoosingTerrain)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("terrainList");

			// Check if a terrain name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select terrain
					_currentTerrainID = "@" + selectedButtonID;

					// Only if going to editor
					if (_isEditingTerrain)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenuTerrainChoice");

						// Show terrain name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
							"Terrain: " + _currentTerrainID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(), true);
					}

					// Only select the terrain if it has a heightMap
					if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
					{
						_fe3d.terrainEntity_select(_currentTerrainID);
						_fe3d.camera_setPosition(Vec3(0.0f, _fe3d.terrainEntity_getSize(_currentTerrainID) * 0.5f, 0.0f));
						_fe3d.camera_setPitch(-90.0f);
						_fe3d.camera_enableThirdPersonView(0.0f, 45.0f, _fe3d.terrainEntity_getSize(_currentTerrainID) * 0.5f);
					}

					// Miscellaneous
					_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
					_isChoosingTerrain = false;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList")) // Cancelled choosing
			{
				_isChoosingTerrain = false;
				_isEditingTerrain = false;
				_isDeletingTerrain = false;
				_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainDeleting()
{
	if (_isEditorLoaded)
	{
		if (_isDeletingTerrain && _currentTerrainID != "")
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
				_fe3d.terrainEntity_delete(_currentTerrainID);

				// Delete from name record
				_loadedTerrainIDs.erase(std::remove(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), _currentTerrainID), _loadedTerrainIDs.end());
				_isDeletingTerrain = false;
				_currentTerrainID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
			{
				_fe3d.terrainEntity_select("");
				_isDeletingTerrain = false;
				_currentTerrainID = "";
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainCamera()
{
	if (_isEditorLoaded)
	{
		// Disable third person view
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			_fe3d.camera_disableThirdPersonView();
		}

		// Check if terrain is inactive
		if (_currentTerrainID.empty() || !_fe3d.terrainEntity_isExisting(_currentTerrainID))
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
					// Set distance
					_fe3d.camera_setMinThirdPersonDistance(_fe3d.terrainEntity_getSize(_currentTerrainID) * 0.75f);
					_fe3d.camera_setMaxThirdPersonDistance(_fe3d.terrainEntity_getSize(_currentTerrainID) * 0.75f);
					_fe3d.camera_setMinThirdPersonPitch(45.0f);
					_fe3d.camera_setMaxThirdPersonPitch(45.0f);

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