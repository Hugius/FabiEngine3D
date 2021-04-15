#include "scene_editor.hpp"

void SceneEditor::_updateModelPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewModelID.empty())
		{
			// Check if mouse behavior isn't being invalid
			if ((_fe3d.misc_isCursorInsideViewport() && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT) && 
				!_gui.getGlobalScreen()->isFocused()) || _fe3d.terrainEntity_getSelectedID() == "")
			{
				// Default placement position
				Vec3 newPosition = Vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "" && _fe3d.misc_isRaycastPositionOnTerrainValid())
				{
					// Show preview model
					_fe3d.modelEntity_show(_currentPreviewModelID);

					// Update preview model position
					if (_fe3d.misc_isRaycastPositionOnTerrainValid())
					{
						newPosition = _fe3d.misc_getRaycastPositionOnTerrain();

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
					_fe3d.modelEntity_hide(_currentPreviewModelID);
				}

				// Placing model
				if ((_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPositionOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "")  // Can be bypassed if terrain does not exist
				{
					// Add new model
					begin:
					int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = _currentPreviewModelID.substr(1); // Remove the '@'
					newID = newID + "_" + to_string(randomSerial); // Adding a number to make it unique

					// Check if ID not already exists
					if (_fe3d.modelEntity_isExisting(newID))
					{
						goto begin;
					}

					// Add model
					_copyPreviewModel(newID, _currentPreviewModelID, newPosition);

					// Disable placement mode if no terrain available to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_fe3d.modelEntity_hide(_currentPreviewModelID);
						_currentPreviewModelID = "";
					}
				}
				else if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling model placement
				{
					// Hide preview model
					_fe3d.modelEntity_hide(_currentPreviewModelID);
					_currentPreviewModelID = "";
					string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}
			else
			{
				// Hide preview model
				_fe3d.modelEntity_hide(_currentPreviewModelID);
			}
		}
	}
}