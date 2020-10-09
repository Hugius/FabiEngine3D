#include "scene_editor.hpp"

void SceneEditor::_updateBillboardPlacing()
{
	if (_isLoaded)
	{
		// Only if user is in placement mode
		if (_currentPreviewBillboardName != "")
		{
			// Check if mouse behavior isn't being invalid
			if (_fe3d.misc_isMouseInsideViewport() && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT) && !_gui->getGlobalScreen()->isFocused())
			{
				// Default placement position
				vec3 newPosition = vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "")
				{
					// Show preview billboard
					_fe3d.billboardEntity_show(_currentPreviewBillboardName);

					// Update preview billboard position
					if (_fe3d.terrainEntity_isValidMousePoint())
					{
						vec2 size = _fe3d.billboardEntity_getSize(_currentPreviewBillboardName);
						newPosition = _fe3d.terrainEntity_getMousePoint() + vec3(0.0f, size.y / 2.0f, 0.0f);
						_fe3d.billboardEntity_setPosition(_currentPreviewBillboardName, newPosition);
					}
				}

				// Placing billboard
				if ((_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.terrainEntity_isValidMousePoint()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "")  // Can be bypassed if terrain does not exist
				{
					// Add new billboard
				begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = _currentPreviewBillboardName.substr(1); // Remove the '@'
					newID = to_string(randomSerial) + "@" + newID; // Adding a number to make it unique

					// Check if ID not already exists
					if (_fe3d.billboardEntity_isExisting(newID))
					{
						goto begin;
					}

					// Add billboard
					_placeBillboard(newID, _currentPreviewBillboardName, newPosition);

					// Disable placement mode if no terrain availible to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_currentPreviewBillboardName = "";
					}
				}
				else if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling billboard placement
				{
					// Hide preview billboard
					_fe3d.billboardEntity_hide(_currentPreviewBillboardName);
					_currentPreviewBillboardName = "";
					string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}
			else
			{
				// Hide preview billboard
				_fe3d.billboardEntity_hide(_currentPreviewBillboardName);
			}
		}
	}
}