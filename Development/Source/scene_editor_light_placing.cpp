#include "scene_editor.hpp"

void SceneEditor::_updateLightPlacing()
{
	if (_isLoaded)
	{
		// Only if user is in placement mode
		if (_isPlacingPointlight)
		{
			// Check if mouse behavior isn't being invalid
			if (_fe3d.misc_isMouseInsideViewport() && 
				!_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT) && 
				!_gui->getGlobalScreen()->isFocused())
			{
				// Default placement position
				vec3 newPosition = vec3(0.0f);

				// Check if a terrain is loaded
				if (_fe3d.terrainEntity_getSelectedID() != "")
				{
					// Update preview pointlight position
					newPosition = _fe3d.terrainEntity_getMousePoint() + vec3(0.0f, 1.0f, 0.0f);

					// Show preview pointlight
					_fe3d.lightEntity_show(_previewPointlightID);
					_fe3d.gameEntity_show(_previewPointlightID);
					_fe3d.lightEntity_setPosition(_previewPointlightID, newPosition);
					_fe3d.gameEntity_setPosition(_previewPointlightID, newPosition);
				}

				// Placing pointlight
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) || _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new pointlight
				begin: int randomSerial = _fe3d.misc_getUniqueInt(0, INT_MAX);
					string newID = "pointlight" + std::to_string(randomSerial);

					// Check if ID not already exists
					if (_fe3d.lightEntity_isExisting(newID))
					{
						goto begin;
					}

					// Add light entity
					_fe3d.gameEntity_add("@" + newID, "Engine\\OBJs\\lamp.obj", newPosition, vec3(0.0f), _defaultLightbulbSize);
					_fe3d.gameEntity_setColor("@" + newID, vec3(1.0f));
					_fe3d.gameEntity_setShadowed("@" + newID, false);
					_fe3d.aabbEntity_bindToGameEntity("@" + newID, _defaultLightbulbAabbSize, true);
					_fe3d.lightEntity_add(newID, newPosition);

					// Disable placement mode if no terrain availible to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_isPlacingPointlight = false;
					}
				}
				else if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_MIDDLE)) // Cancelling pointlight placement
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