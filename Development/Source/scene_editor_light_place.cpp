#include "scene_editor.hpp"
#include "tools.hpp"

void SceneEditor::_updateLightPlacing()
{
	if (_isEditorLoaded)
	{
		// Only if user is in placement mode
		if (_isPlacingPointLight)
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
					// Update preview point light position
					newPosition = _fe3d.misc_getRaycastPointOnTerrain() + Vec3(0.0f, 1.0f, 0.0f);

					// Show preview point light
					_fe3d.lightEntity_setVisible(PREVIEW_LAMP_ID, true);
					_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, true);
					_fe3d.lightEntity_setPosition(PREVIEW_LAMP_ID, newPosition);
					_fe3d.modelEntity_setPosition(PREVIEW_LAMP_ID, newPosition);
				}
				else
				{
					// Hide preview point light
					_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, false);
					_fe3d.lightEntity_setVisible(PREVIEW_LAMP_ID, false);
				}

				// Placing point light
				if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d.misc_isRaycastPointOnTerrainValid()) // If user pressed LMB
					|| _fe3d.terrainEntity_getSelectedID() == "") // Can be bypassed if terrain does not exist
				{
					// Add new point light
				BEGIN: int randomSerial = Tools::getRandomInteger(0, INT_MAX);
					string newID = ("light_" + to_string(randomSerial));

					// Check if ID not already exists
					if (_fe3d.lightEntity_isExisting(newID))
					{
						goto BEGIN;
					}

					// Create model
					const string newModelID = ("@@lamp_" + newID);
					_fe3d.modelEntity_create(newModelID, "engine_assets\\meshes\\lamp.obj");
					_fe3d.modelEntity_setPosition(newModelID, newPosition);
					_fe3d.modelEntity_setSize(newModelID, DEFAULT_LAMP_SIZE);
					_fe3d.modelEntity_setShadowed(newModelID, false);
					_fe3d.modelEntity_setReflected(newModelID, false);
					_fe3d.modelEntity_setBright(newModelID, true);
					_fe3d.modelEntity_setColor(newModelID, Vec3(1.0f));

					// Bind AABB
					_fe3d.aabbEntity_create(newModelID);
					_fe3d.aabbEntity_bindToModelEntity(newModelID, newModelID);
					_fe3d.aabbEntity_setSize(newModelID, DEFAULT_LAMP_AABB_SIZE);

					// Create light
					_fe3d.lightEntity_setPosition(newID, newPosition);
					_fe3d.lightEntity_setRadius(newID, Vec3(DEFAULT_LIGHT_RADIUS));
					_fe3d.lightEntity_setIntensity(newID, DEFAULT_LIGHT_INTENSITY);
					_loadedLightIDs.push_back(newID);

					// Disable placement mode if no terrain available to choose position from
					if (_fe3d.terrainEntity_getSelectedID() == "")
					{
						_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, false);
						_fe3d.lightEntity_setVisible(PREVIEW_LAMP_ID, false);
						_isPlacingPointLight = false;
					}
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_MIDDLE)) // Cancelling point light placement
				{
					// Hide preview point light
					_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, false);
					_fe3d.lightEntity_setVisible(PREVIEW_LAMP_ID, false);
					_isPlacingPointLight = false;
				}
			}
			else
			{
				// Hide preview point light
				_fe3d.modelEntity_setVisible(PREVIEW_LAMP_ID, false);
				_fe3d.lightEntity_setVisible(PREVIEW_LAMP_ID, false);
			}
		}
	}
}