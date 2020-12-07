#include "scene_editor.hpp"

void SceneEditor::_updateLightPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (_isPlacingPointlight)
		{
			// Check if mouse behavior isn't being invalid
			if (_fe3d.misc_isCursorInsideViewport() && 
				!_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT) && 
				!_gui.getGlobalScreen()->isFocused())
			{
				// Default placement position
				Vec3 newPosition = Vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "")
				{
					// Update preview pointlight position
					newPosition = _fe3d.terrainEntity_getMousePoint() + Vec3(0.0f, 1.0f, 0.0f);

					// Show preview pointlight
					_fe3d.lightEntity_show(_previewPointlightID);
					_fe3d.gameEntity_show(_previewPointlightID);
					_fe3d.lightEntity_setPosition(_previewPointlightID, newPosition);
					_fe3d.gameEntity_setPosition(_previewPointlightID, newPosition);
				}

				// Placing pointlight
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new pointlight
				begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = "pointlight" + to_string(randomSerial);

					// Check if ID not already exists
					if (_fe3d.lightEntity_isExisting(newID))
					{
						goto begin;
					}

					// Add light entity
					_fe3d.gameEntity_add("@" + newID, "engine\\models\\lamp.obj", newPosition, Vec3(0.0f), _defaultLightbulbSize);
					_fe3d.gameEntity_setShadowed("@" + newID, false);
					_fe3d.aabbEntity_bindToGameEntity("@" + newID, Vec3(0.0f), _defaultLightbulbAabbSize, true);
					_fe3d.lightEntity_add(newID, newPosition);

					// Disable placement mode if no terrain availible to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_isPlacingPointlight = false;
					}
				}
				else if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling pointlight placement
				{
					// Hide preview pointlight
					_fe3d.gameEntity_hide(_previewPointlightID);
					_fe3d.lightEntity_hide(_previewPointlightID);
					_isPlacingPointlight = false;
				}
			}
			else
			{
				// Hide preview pointlight
				_fe3d.gameEntity_hide(_previewPointlightID);
				_fe3d.lightEntity_hide(_previewPointlightID);
			}
		}
	}
}