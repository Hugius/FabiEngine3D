#include "scene_editor.hpp"
#include "tools.hpp"

void SceneEditor::_updateModelPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewModelID.empty())
		{
			if (_fe3d.terrainEntity_getSelectedID() == "") // Placing without terrain
			{
				// Add new model
			BEGIN1:
				int randomSerial = Tools::getRandomInteger(0, INT_MAX);
				string newID = _currentPreviewModelID.substr(1); // Remove the '@'
				newID = newID + "_" + to_string(randomSerial); // Adding a number to make it unique

				// Check if ID not already exists
				if (_fe3d.modelEntity_isExisting(newID))
				{
					goto BEGIN1;
				}

				// Add model
				_copyPreviewModel(newID, _currentPreviewModelID, Vec3(0.0f));

				// Disable placement mode
				_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
				_currentPreviewModelID = "";
			}
			else // Placing on terrain
			{
				// Check if allowed by GUI
				if (_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
				{
					// Check if allowed by mouse
					if (!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
					{
						// Default placement position
						Vec3 newPosition = Vec3(0.0f);

						// Check if a terrain is loaded
						if (_fe3d.terrainEntity_getSelectedID() != "" && _fe3d.misc_isRaycastPointOnTerrainValid())
						{
							// Show preview model
							_fe3d.modelEntity_setVisible(_currentPreviewModelID, true);

							// Retrieve currrent position
							newPosition = _fe3d.misc_getRaycastPointOnTerrain();

							// Instanced entity has different positioning
							if (_fe3d.modelEntity_isInstanced(_currentPreviewModelID))
							{
								_fe3d.modelEntity_setInstanced(_currentPreviewModelID, true, { newPosition });
							}
							else
							{
								_fe3d.modelEntity_setPosition(_currentPreviewModelID, newPosition);
							}
						}
						else
						{
							// Hide preview model
							_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
						}

						// Placing model on terrain
						if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid())
						{
							// Add new model
						BEGIN2:
							int randomSerial = Tools::getRandomInteger(0, INT_MAX);
							string newID = _currentPreviewModelID.substr(1); // Remove the '@'
							newID = newID + "_" + to_string(randomSerial); // Adding a number to make it unique

							// Check if ID not already exists
							if (_fe3d.modelEntity_isExisting(newID))
							{
								goto BEGIN2;
							}

							// Add model
							_copyPreviewModel(newID, _currentPreviewModelID, newPosition);
						}
						else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Disable placement mode
						{
							_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
							_currentPreviewModelID = "";
							string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
							_fe3d.textEntity_setVisible(textEntityID, false);
						}
					}
					else
					{
						// Hide preview model
						_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
					}
				}
			}
		}
	}
}