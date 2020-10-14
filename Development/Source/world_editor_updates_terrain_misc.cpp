#include "world_editor.hpp"

void WorldEditor::_updateTerrainEditor()
{
	if (_currentWorldPart == WorldPart::TERRAIN)
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

void WorldEditor::_updateTerrainCreation()
{
	if (_isLoaded)
	{
		if (_terrainCreationEnabled)
		{
			string newTerrainName;

			// Create new terrain
			if (_gui->getGlobalScreen()->checkValueForm("newTerrainName", newTerrainName, {}))
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
						_fe3d.terrainEntity_add(_currentTerrainID);
						_leftWindow->setActiveScreen("terrainEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
							"Terrain: " + _currentTerrainID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID());
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

void WorldEditor::_updateTerrainChoosing()
{
	if (_isLoaded)
	{
		if (_terrainChoosingEnabled)
		{
			// Get selected button ID
			string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("terrainList");

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

					// Go to editor screen & show terrain name
					if (_terrainEditingEnabled)
					{
						_gui->getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui->getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
							"Terrain: " + _currentTerrainID.substr(1), 0.025f);
						_fe3d.textEntity_show(_gui->getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID());
					}

					// Miscellaneous
					_gui->getGlobalScreen()->removeChoiceForm("terrainList");
					_terrainChoosingEnabled = false;
				}
				else
				{
					// Set new hovered terrain
					_hoveredTerrainID = "@" + selectedButtonID;
				}
			}
			else if (_gui->getGlobalScreen()->isChoiceFormCancelled("terrainList")) // Cancelled choosing
			{
				_terrainChoosingEnabled = false;
				_terrainEditingEnabled = false;
				_terrainRemovalEnabled = false;
				_gui->getGlobalScreen()->removeChoiceForm("terrainList");
			}
			else // Nothing hovered
			{
				_hoveredTerrainID = "";
			}

			// Show hovered terrain
			if (_hoveredTerrainID != "")
			{
				if (_fe3d.terrainEntity_getHeightMapPath(_hoveredTerrainID) != "")
				{
					_fe3d.terrainEntity_select(_hoveredTerrainID);
				}
			}
		}
	}
}

void WorldEditor::_updateTerrainRemoval()
{
	if (_isLoaded)
	{
		if (_terrainRemovalEnabled && _currentTerrainID != "")
		{
			_gui->getGlobalScreen()->addAnswerForm("removeTerrain", "Are you sure?", vec2(0.0f));

			if (_gui->getGlobalScreen()->isAnswerFormConfirmed("removeTerrain"))
			{
				// Delete entity
				_fe3d.terrainEntity_delete(_currentTerrainID);

				// Delete from name record
				_terrainNames.erase(std::remove(_terrainNames.begin(), _terrainNames.end(), _currentTerrainID), _terrainNames.end());
				_terrainRemovalEnabled = false;
				_currentTerrainID = "";
			}
			else if (_gui->getGlobalScreen()->isAnswerFormCancelled("removeTerrain"))
			{
				_terrainRemovalEnabled = false;
				_currentTerrainID = "";
			}
		}
	}
}

void WorldEditor::_updateTerrainCamera()
{
	if (_isLoaded && _currentTerrainID != "")
	{
		if (_fe3d.terrainEntity_isExisting(_currentTerrainID))
		{
			std::cout << "hoi";
			// Get scroll wheel input
			if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport())
			{
				float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) / _scrollWheelDivider;
				_cameraRotationSpeed += rotationAcceleration;
			}
			_cameraRotationSpeed *= 0.975f;
			_totalCameraRotation += _cameraRotationSpeed;

			// Calculate new camera position
			float x = (_fe3d.terrainEntity_getSize(_currentTerrainID) / 2.0f) * sin(_totalCameraRotation);
			float y = (_fe3d.terrainEntity_getMaxHeight(_currentTerrainID) * 1.25f);
			float z = (_fe3d.terrainEntity_getSize(_currentTerrainID) / 2.0f) * cos(_totalCameraRotation);

			// Update camera position
			_fe3d.camera_setPosition(vec3(x, y, z));
			_fe3d.camera_enableLookat(vec3(0.0f));
		}
	}
}