#include "scene_editor.hpp"

void SceneEditor::_updateBillboardPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewBillboardID.empty())
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
					// Show preview billboard
					_fe3d.billboardEntity_show(_currentPreviewBillboardID);

					// Update preview billboard position
					Vec2 size = _fe3d.billboardEntity_getSize(_currentPreviewBillboardID);
					newPosition = _fe3d.misc_getRaycastPositionOnTerrain();
					_fe3d.billboardEntity_setPosition(_currentPreviewBillboardID, newPosition);
				}
				else
				{
					// Hide preview billboard
					_fe3d.billboardEntity_hide(_currentPreviewBillboardID);
				}

				// Placing billboard
				if ((_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPositionOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "")  // Can be bypassed if terrain does not exist
				{
					// Add new billboard
				begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = _currentPreviewBillboardID.substr(1); // Remove the '@'
					newID = newID + "_" + to_string(randomSerial); // Adding a number to make it unique

					// Check if ID not already exists
					if (_fe3d.billboardEntity_isExisting(newID))
					{
						goto begin;
					}

					// Add billboard
					_copyPreviewBillboard(newID, _currentPreviewBillboardID, newPosition);

					// Disable placement mode if no terrain available to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_fe3d.billboardEntity_hide(_currentPreviewBillboardID);
						_currentPreviewBillboardID = "";
					}
				}
				else if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling billboard placement
				{
					// Hide preview billboard
					_fe3d.billboardEntity_hide(_currentPreviewBillboardID);
					_currentPreviewBillboardID = "";
					string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}
			else
			{
				// Hide preview billboard
				_fe3d.billboardEntity_hide(_currentPreviewBillboardID);
			}
		}
	}
}