#include "scene_editor.hpp"
#include "tools.hpp"

void SceneEditor::_updateBillboardPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (!_currentPreviewBillboardID.empty())
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
					// Show preview billboard
					_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, true);

					// Update preview billboard position
					Vec2 size = _fe3d.billboardEntity_getSize(_currentPreviewBillboardID);
					newPosition = _fe3d.misc_getRaycastPointOnTerrain();
					_fe3d.billboardEntity_setPosition(_currentPreviewBillboardID, newPosition);
				}
				else
				{
					// Hide preview billboard
					_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
				}

				// Placing billboard
				if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "")  // Can be bypassed if terrain does not exist
				{
					// Add new billboard
				BEGIN: int randomSerial = Tools::getRandomInteger(0, INT_MAX);
					string newID = _currentPreviewBillboardID.substr(1); // Remove the '@'
					newID = newID + "_" + to_string(randomSerial); // Adding a number to make it unique

					// Check if ID not already exists
					if (_fe3d.billboardEntity_isExisting(newID))
					{
						goto BEGIN;
					}

					// Add billboard
					_copyPreviewBillboard(newID, _currentPreviewBillboardID, newPosition);

					// Disable placement mode if no terrain available to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
						_currentPreviewBillboardID = "";
					}
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling billboard placement
				{
					// Hide preview billboard
					_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
					_currentPreviewBillboardID = "";
					string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
					_fe3d.textEntity_setVisible(textEntityID, false);
				}
			}
			else
			{
				// Hide preview billboard
				_fe3d.billboardEntity_setVisible(_currentPreviewBillboardID, false);
			}
		}
	}
}