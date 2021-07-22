#include "scene_editor.hpp"
#include <iostream>

#define ACTIVE_BULB_ID _activeLightBulbID
#define ACTIVE_LIGHT_ID _activeLightBulbID.substr(1)

void SceneEditor::_updateLightEditing()
{
	if (_isEditorLoaded)
	{
		_selectedLightBulbID = "";

		// User must not be in placement mode
		if (_currentPreviewModelID == "" && _currentPreviewBillboardID == "" && !_isPlacingPointLight && _currentPreviewSoundID == "")
		{
			// Check which entity is selected
			auto hoveredAabbID = _fe3d.collision_checkCursorInAny().first;

			// Check if user selected a light bulb model
			for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
			{
				// Must be light preview entity
				if (entityID.substr(0, 6) == "@light")
				{
					// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
					if (hoveredAabbID == entityID && _fe3d.misc_isCursorInsideViewport() &&
						!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
					{
						// Set new selected light bulb
						_selectedLightBulbID = entityID;

						// Change cursor
						_fe3d.imageEntity_changeDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

						// Check if user clicked light bulb
						if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							// Check if same light bulb is clicked again
							if (_selectedLightBulbID != ACTIVE_BULB_ID)
							{
								// Set new active light
								ACTIVE_BULB_ID = _selectedLightBulbID;
								_transformation = TransformationType::MOVEMENT;

								// Filling writefields
								Vec3 position = _fe3d.modelEntity_getPosition(ACTIVE_BULB_ID);
								_gui.getViewport("right")->getWindow("main")->getScreen("pointLightPropertiesMenu")->getWritefield("x")->changeTextContent(to_string(static_cast<int>(position.x)));
								_gui.getViewport("right")->getWindow("main")->getScreen("pointLightPropertiesMenu")->getWritefield("y")->changeTextContent(to_string(static_cast<int>(position.y)));
								_gui.getViewport("right")->getWindow("main")->getScreen("pointLightPropertiesMenu")->getWritefield("z")->changeTextContent(to_string(static_cast<int>(position.z)));
							}
						}
					}
					else 
					{
						// Don't reset if light bulb is active
						if (entityID != ACTIVE_BULB_ID)
						{
							_fe3d.modelEntity_setSize(entityID, DEFAULT_LIGHT_BULB_SIZE);
							_fe3d.aabbEntity_setSize(entityID, DEFAULT_LIGHT_BULB_AABB_SIZE);
						}
					}
				}
			}
			
			// Check if user made the active light bulb inactive
			if (_selectedLightBulbID == "" && ACTIVE_BULB_ID != "" && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					ACTIVE_BULB_ID = "";
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
				}
			}

			// Update light bulb animations
			if (_selectedLightBulbID != ACTIVE_BULB_ID)
			{
				_updateLightBulbAnimation(_selectedLightBulbID, _selectedLightBulbSizeDirection);
			}
			_updateLightBulbAnimation(ACTIVE_BULB_ID, _activeLightBulbSizeDirection);

			// Update properties screen
			if (ACTIVE_BULB_ID != "")
			{
				_gui.getViewport("right")->getWindow("main")->setActiveScreen("pointLightPropertiesMenu");

				// Check if input received
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (_gui.getViewport("right")->getWindow("main")->getScreen("pointLightPropertiesMenu")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.modelEntity_delete(ACTIVE_BULB_ID);
						_fe3d.lightEntity_delete(ACTIVE_LIGHT_ID);
						_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
						ACTIVE_BULB_ID = "";
						return;
					}
				}

				// Get current values
				Vec3 position = _fe3d.lightEntity_getPosition(ACTIVE_LIGHT_ID);
				Vec3 color = _fe3d.lightEntity_getColor(ACTIVE_LIGHT_ID);
				float intensity = _fe3d.lightEntity_getIntensity(ACTIVE_LIGHT_ID);
				float distance = _fe3d.lightEntity_getDistanceFactor(ACTIVE_LIGHT_ID);

				// Update value filling and changing
				_handleValueChanging("pointLightPropertiesMenu", "distancePlus", "distance", distance, LIGHTING_CHANGING_SPEED, 10.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "distanceMinus", "distance", distance, -LIGHTING_CHANGING_SPEED, 10.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "intensityPlus", "intensity", intensity, LIGHTING_CHANGING_SPEED, 10.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "intensityMinus", "intensity", intensity, -LIGHTING_CHANGING_SPEED, 10.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "xPlus", "x", position.x, _editorSpeed / 100.0f);
				_handleValueChanging("pointLightPropertiesMenu", "xMinus", "x", position.x, -_editorSpeed / 100.0f);
				_handleValueChanging("pointLightPropertiesMenu", "yPlus", "y", position.y, _editorSpeed / 100.0f);
				_handleValueChanging("pointLightPropertiesMenu", "yMinus", "y", position.y, -_editorSpeed / 100.0f);
				_handleValueChanging("pointLightPropertiesMenu", "zPlus", "z", position.z, _editorSpeed / 100.0f);
				_handleValueChanging("pointLightPropertiesMenu", "zMinus", "z", position.z, -_editorSpeed / 100.0f);
				_handleValueChanging("pointLightPropertiesMenu", "rPlus", "r", color.r, LIGHTING_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "rMinus", "r", color.r, -LIGHTING_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "gPlus", "g", color.g, LIGHTING_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "gMinus", "g", color.g, -LIGHTING_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "bPlus", "b", color.b, LIGHTING_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "bMinus", "b", color.b, -LIGHTING_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
				
				// Apply new values
				_fe3d.modelEntity_setPosition(ACTIVE_BULB_ID, position);
				_fe3d.lightEntity_setPosition(ACTIVE_LIGHT_ID, position);
				_fe3d.modelEntity_setColor(ACTIVE_BULB_ID, color);
				_fe3d.lightEntity_setColor(ACTIVE_LIGHT_ID, color);
				_fe3d.lightEntity_setIntensity(ACTIVE_LIGHT_ID, intensity);
				_fe3d.lightEntity_setDistanceFactor(ACTIVE_LIGHT_ID, distance);
			}
		}
	}
}