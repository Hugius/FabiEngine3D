#include "scene_editor.hpp"

void SceneEditor::_updateModelPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewModelID.empty())
		{
			// Check if mouse behavior isn't being invalid
			if ((_fe3d.misc_isCursorInsideViewport() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT) && 
				!_gui.getGlobalScreen()->isFocused()) || _fe3d.terrainEntity_getSelectedID() == "")
			{
				// Default placement position
				Vec3 newPosition = Vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "" && _fe3d.misc_isRaycastPointOnTerrainValid())
				{
					// Show preview model
					_fe3d.modelEntity_setVisible(_currentPreviewModelID, true);

					// Update preview model position
					if (_fe3d.misc_isRaycastPointOnTerrainValid())
					{
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
				}
				else
				{
					// Hide preview model
					_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
				}

				// Placing model
				if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "")  // Bypass placement if no terrain selected
				{
					// Add new model
				BEGIN:
					int randomSerial = _fe3d.misc_getRandomInteger(0, INT_MAX);
					string newID = _currentPreviewModelID.substr(1); // Remove the '@'
					newID = newID + "_" + to_string(randomSerial); // Adding a number to make it unique

					// Check if ID not already exists
					if (_fe3d.modelEntity_isExisting(newID))
					{
						goto BEGIN;
					}

					// Add model
					_copyPreviewModel(newID, _currentPreviewModelID, newPosition);

					// Disable placement mode if no terrain available to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_fe3d.modelEntity_setVisible(_currentPreviewModelID, false);
						_currentPreviewModelID = "";
					}
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling model placement
				{
					// Hide preview model
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