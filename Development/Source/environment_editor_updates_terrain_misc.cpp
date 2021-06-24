#include "environment_editor.hpp"

void EnvironmentEditor::_updateTerrainEditor()
{
	if (_currentEnvironmentType == EnvironmentType::TERRAIN)
	{
		_updateTerrainMenuMain();
		_updateTerrainMenuChoice();
		_updateTerrainMenuMesh();
		_updateTerrainMenuBlendMap();
		_updateTerrainMenuLighting();
		_updateTerrainCreation();
		_updateTerrainChoosing();
		_updateTerrainRemoval();
		_updateTerrainCamera();
	}
}

void EnvironmentEditor::_updateTerrainCreation()
{
	if (_isEditorLoaded)
	{
		if (_isTerrainCreationEnabled)
		{
			string newTerrainName;

			// Create new terrain
			if (_gui.getGlobalScreen()->checkValueForm("newTerrainName", newTerrainName, {}))
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
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
								"Terrain: " + _currentTerrainID.substr(1), 0.025f);
							_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID());
							_isTerrainCreationEnabled = false;
							_isTerrainEditingEnabled = true;
						}
						else
						{
							_fe3d.logger_throwWarning("Terrain name \"" + newTerrainName.substr(1) + "\" already exists!");
						}
					}
					else
					{
						_fe3d.logger_throwWarning("New terrain name cannot contain any spaces!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New terrain name cannot contain '@'!");
				}
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainChoosing()
{
	if (_isEditorLoaded)
	{
		if (_isTerrainChoosingEnabled)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("terrainList");

			// Hide last terrain
			if (_hoveredTerrainID != "")
			{
				_fe3d.terrainEntity_select("");
			}

			// Check if a terrain name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select terrain
					_currentTerrainID = "@" + selectedButtonID;
					_hoveredTerrainID = "";

					// Only if going to editor
					if (_isTerrainEditingEnabled)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

						// Show terrain name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
							"Terrain: " + _currentTerrainID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID());
					}

					// Only select the terrain if it has a heightmap
					if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
					{
						_fe3d.terrainEntity_select(_currentTerrainID);
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("terrainList");
					_isTerrainChoosingEnabled = false;
				}
				else
				{
					// Set new hovered terrain
					_hoveredTerrainID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList")) // Cancelled choosing
			{
				_isTerrainChoosingEnabled = false;
				_isTerrainEditingEnabled = false;
				_isTerrainRemovalEnabled = false;
				_gui.getGlobalScreen()->removeChoiceForm("terrainList");
			}
			else // Nothing hovered
			{
				_hoveredTerrainID = "";
			}

			// Show hovered terrain
			if (_hoveredTerrainID != "")
			{
				// Only select the terrain if it has a heightmap
				if (_fe3d.terrainEntity_isExisting(_hoveredTerrainID))
				{
					_fe3d.terrainEntity_select(_hoveredTerrainID);
				}
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainRemoval()
{
	if (_isEditorLoaded)
	{
		if (_isTerrainRemovalEnabled && _currentTerrainID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("removeTerrain", "Are you sure?", Vec2(0.0f, 0.25f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("removeTerrain"))
			{
				// Delete entity
				_fe3d.terrainEntity_delete(_currentTerrainID);

				// Delete from name record
				_loadedTerrainIDs.erase(std::remove(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), _currentTerrainID), _loadedTerrainIDs.end());
				_isTerrainRemovalEnabled = false;
				_currentTerrainID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("removeTerrain"))
			{
				_fe3d.terrainEntity_select("");
				_isTerrainRemovalEnabled = false;
				_currentTerrainID = "";
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainCamera()
{
	if (_isEditorLoaded)
	{
		// Check if terrain is selected or hovered
		string terrainID = (_currentTerrainID != "") ? _currentTerrainID : ((_hoveredTerrainID != "") ? _hoveredTerrainID : "");

		// Check if terrain is active
		if (_fe3d.terrainEntity_isExisting(terrainID) && _fe3d.terrainEntity_isVisible(terrainID))
		{
			// Get scroll wheel input
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				float rotationAcceleration = static_cast<float>(_fe3d.input_getMouseWheelY()) / SCROLL_WHEEL_DIVIDER;
				_cameraAcceleration += rotationAcceleration;
			}
			_cameraAcceleration *= 0.975f;
			_totalCameraRotation += _cameraAcceleration;

			// Calculate new camera position
			float x = (_fe3d.terrainEntity_getSize(terrainID) / 2.0f) * sin(_totalCameraRotation);
			float y = (_fe3d.terrainEntity_getMaxHeight(terrainID) * 1.25f);
			float z = (_fe3d.terrainEntity_getSize(terrainID) / 2.0f) * cos(_totalCameraRotation);

			// Update camera
			_fe3d.camera_enableLookatView();
			_fe3d.camera_setPosition(Vec3(x, y, z));
			_fe3d.camera_setLookatPosition(Vec3(0.0f));
		}
		else
		{
			// Set default camera
			_fe3d.camera_disableLookatView();
			_fe3d.camera_setPosition(Vec3(0.0f));
			_fe3d.camera_setLookatPosition(Vec3(0.0f));
			_totalCameraRotation = 0.0f;
			_cameraAcceleration = 0.0f;
		}
	}
}