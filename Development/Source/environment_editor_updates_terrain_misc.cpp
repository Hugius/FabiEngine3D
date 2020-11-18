#include "environment_editor.hpp"

void EnvironmentEditor::_updateTerrainEditor()
{
	if (_currentEnvironmentType == EnvironmentType::TERRAIN)
	{
		_updateTerrainMenuMain();
		_updateTerrainMenuChoice();
		_updateTerrainMenuMesh();
		_updateTerrainMenuBlendMap();
		_updateTerrainCreation();
		_updateTerrainChoosing();
		_updateTerrainRemoval();
		_updateTerrainCamera();
	}
}

void EnvironmentEditor::_updateTerrainCreation()
{
	if (_isLoaded)
	{
		if (_terrainCreationEnabled)
		{
			string newTerrainName;

			// Create new terrain
			if (_gui.getGlobalScreen()->checkValueForm("newTerrainName", newTerrainName, {}))
			{
				// Starting with at-sign not allowed
				if (newTerrainName[0] != '@')
				{
					newTerrainName = "@" + newTerrainName;

					// If terrain name not existing yet
					if (std::find(_terrainNames.begin(), _terrainNames.end(), newTerrainName) == _terrainNames.end())
					{
						_currentTerrainID = newTerrainName;
						_terrainNames.push_back(_currentTerrainID);
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
							"Terrain: " + _currentTerrainID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID());
						_terrainCreationEnabled = false;
						_terrainEditingEnabled = true;
					}
					else
					{
						_fe3d.logger_throwWarning("Terrain name \"" + newTerrainName.substr(1) + "\" already exists!");
					}
				}
				else
				{
					_fe3d.logger_throwWarning("New terrain name cannot begin with '@'");
				}
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainChoosing()
{
	if (_isLoaded)
	{
		if (_terrainChoosingEnabled)
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
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select terrain
					_currentTerrainID = "@" + selectedButtonID;
					_hoveredTerrainID = "";

					// Only if going to editor
					if (_terrainEditingEnabled)
					{
						// Go to editor screen
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

						// Show terrain name
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
							"Terrain: " + _currentTerrainID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID());

						// Only select the terrain if it has a heightmap
						if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
						{
							_fe3d.terrainEntity_select(_currentTerrainID);
						}
					}

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("terrainList");
					_terrainChoosingEnabled = false;
				}
				else
				{
					// Set new hovered terrain
					_hoveredTerrainID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList")) // Cancelled choosing
			{
				_terrainChoosingEnabled = false;
				_terrainEditingEnabled = false;
				_terrainRemovalEnabled = false;
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
	if (_isLoaded)
	{
		if (_terrainRemovalEnabled && _currentTerrainID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("removeTerrain", "Are you sure?", vec2(0.0f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("removeTerrain"))
			{
				// Delete entity
				_fe3d.terrainEntity_delete(_currentTerrainID);

				// Delete from name record
				_terrainNames.erase(std::remove(_terrainNames.begin(), _terrainNames.end(), _currentTerrainID), _terrainNames.end());
				_terrainRemovalEnabled = false;
				_currentTerrainID = "";
			}
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("removeTerrain"))
			{
				_terrainRemovalEnabled = false;
				_currentTerrainID = "";
			}
		}
	}
}

void EnvironmentEditor::_updateTerrainCamera()
{
	if (_isLoaded)
	{
		// Check if a terrain is selected or hovered
		string terrainID = (_currentTerrainID != "") ? _currentTerrainID : ((_hoveredTerrainID != "") ? _hoveredTerrainID : "");

		// Check if terrain entity exists
		if (_fe3d.terrainEntity_isExisting(terrainID))
		{
			// Get scroll wheel input
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) / _scrollWheelDivider;
				_cameraRotationSpeed += rotationAcceleration;
			}
			_cameraRotationSpeed *= 0.975f;
			_totalCameraRotation += _cameraRotationSpeed;

			// Calculate new camera position
			float x = (_fe3d.terrainEntity_getSize(terrainID) / 2.0f) * sin(_totalCameraRotation);
			float y = (_fe3d.terrainEntity_getMaxHeight(terrainID) * 1.25f);
			float z = (_fe3d.terrainEntity_getSize(terrainID) / 2.0f) * cos(_totalCameraRotation);

			// Update camera position
			_fe3d.camera_setPosition(vec3(x, y, z));
			_fe3d.camera_enableLookat(vec3(0.0f));
		}
	}
}