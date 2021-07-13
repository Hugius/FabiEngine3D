#include "scene_editor.hpp"

void SceneEditor::_updateLightPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (_isPlacingPointlight)
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
					// Update preview pointlight position
					newPosition = _fe3d.misc_getRaycastPointOnTerrain() + Vec3(0.0f, 1.0f, 0.0f);

					// Show preview pointlight
					_fe3d.lightEntity_setVisible(PREVIEW_POINTLIGHT_ID, true);
					_fe3d.modelEntity_setVisible(PREVIEW_POINTLIGHT_ID, true);
					_fe3d.lightEntity_setPosition(PREVIEW_POINTLIGHT_ID, newPosition);
					_fe3d.modelEntity_setPosition(PREVIEW_POINTLIGHT_ID, newPosition);
				}
				else
				{
					// Hide preview pointlight
					_fe3d.modelEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
					_fe3d.lightEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
				}

				// Placing pointlight
				if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new pointlight
				BEGIN: int randomSerial = _fe3d.misc_getRandomInteger(0, INT_MAX);
					string newID = "pointlight_" + to_string(randomSerial);

					// Check if ID not already exists
					if (_fe3d.lightEntity_isExisting(newID))
					{
						goto BEGIN;
					}

					// Add light entity
					_fe3d.lightEntity_add(newID, newPosition);
					_fe3d.modelEntity_add("@" + newID, "engine_assets\\meshes\\lamp.obj", newPosition, Vec3(0.0f), DEFAULT_LIGHTBULB_SIZE);
					_fe3d.modelEntity_setShadowed("@" + newID, false);
					_fe3d.modelEntity_setReflected("@" + newID, false);
					_fe3d.modelEntity_setBloomed("@" + newID, true);
					_fe3d.modelEntity_setColor("@" + newID, Vec3(1.0f));
					_fe3d.aabbEntity_bindToModelEntity("@" + newID, Vec3(0.0f), DEFAULT_LIGHTBULB_AABB_SIZE, true, true);
					_loadedLightIDs.push_back(newID);

					// Disable placement mode if no terrain available to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_fe3d.modelEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
						_fe3d.lightEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
						_isPlacingPointlight = false;
					}
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling pointlight placement
				{
					// Hide preview pointlight
					_fe3d.modelEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
					_fe3d.lightEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
					_isPlacingPointlight = false;
				}
			}
			else
			{
				// Hide preview pointlight
				_fe3d.modelEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
				_fe3d.lightEntity_setVisible(PREVIEW_POINTLIGHT_ID, false);
			}
		}
	}
}