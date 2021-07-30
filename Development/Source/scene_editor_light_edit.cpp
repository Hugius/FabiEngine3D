#include "scene_editor.hpp"

#define SELECTED_BULB_ID _selectedLightBulbID
#define ACTIVE_BULB_ID _activeLightBulbID
#define ACTIVE_LIGHT_ID _activeLightBulbID.substr(1)

void SceneEditor::_updateLightEditing()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		auto rightWindow = _gui.getViewport("right")->getWindow("main");

		// Reset selected light from last frame
		SELECTED_BULB_ID = "";

		// User must not be in placement mode
		if ((_currentPreviewModelID == "") && (_currentPreviewBillboardID == "") && !_isPlacingPointLight && (_currentPreviewSoundID == ""))
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
						SELECTED_BULB_ID = entityID;

						// Change cursor
						_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");

						// Check if user clicked light bulb
						if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							// Check if same light bulb is not clicked again
							if (SELECTED_BULB_ID != ACTIVE_BULB_ID)
							{
								// Set new active light
								ACTIVE_BULB_ID = SELECTED_BULB_ID;
								
								// Update buttons hoverability
								rightWindow->getScreen("pointLightPropertiesMenu")->getButton("position")->setHoverable(false);
								rightWindow->getScreen("pointLightPropertiesMenu")->getButton("radius")->setHoverable(true);
								rightWindow->getScreen("pointLightPropertiesMenu")->getButton("color")->setHoverable(true);

								// Filling writefields
								Vec3 position = _fe3d.modelEntity_getPosition(ACTIVE_BULB_ID);
								rightWindow->getScreen("pointLightPropertiesMenu")->getWritefield("x")->changeTextContent(to_string(static_cast<int>(position.x)));
								rightWindow->getScreen("pointLightPropertiesMenu")->getWritefield("y")->changeTextContent(to_string(static_cast<int>(position.y)));
								rightWindow->getScreen("pointLightPropertiesMenu")->getWritefield("z")->changeTextContent(to_string(static_cast<int>(position.z)));
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
			if ((SELECTED_BULB_ID == "") && (ACTIVE_BULB_ID != "") && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					ACTIVE_BULB_ID = "";
					rightWindow->setActiveScreen("sceneEditorControls");
				}
			}

			// Update light bulb animations
			if (SELECTED_BULB_ID != ACTIVE_BULB_ID)
			{
				_updateLightBulbAnimation(SELECTED_BULB_ID, _selectedLightBulbSizeDirection);
			}
			_updateLightBulbAnimation(ACTIVE_BULB_ID, _activeLightBulbSizeDirection);

			// Update properties screen
			if (ACTIVE_BULB_ID != "")
			{
				// Temporary values
				auto screen = rightWindow->getScreen("pointLightPropertiesMenu");

				// Activate screen
				rightWindow->setActiveScreen("pointLightPropertiesMenu");

				// Check if input received
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (screen->getButton("position")->isHovered()) // Position button
					{
						// Update buttons hoverability
						screen->getButton("position")->setHoverable(false);
						screen->getButton("radius")->setHoverable(true);
						screen->getButton("color")->setHoverable(true);
					}
					else if (screen->getButton("radius")->isHovered()) // Rotation button
					{
						// Update buttons hoverability
						screen->getButton("position")->setHoverable(true);
						screen->getButton("radius")->setHoverable(false);
						screen->getButton("color")->setHoverable(true);
					}
					else if (screen->getButton("color")->isHovered()) // Color button
					{
						// Update buttons hoverability
						screen->getButton("position")->setHoverable(true);
						screen->getButton("radius")->setHoverable(true);
						screen->getButton("color")->setHoverable(false);
					}
					else if (screen->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.modelEntity_delete(ACTIVE_BULB_ID);
						_fe3d.lightEntity_delete(ACTIVE_LIGHT_ID);
						rightWindow->setActiveScreen("sceneEditorControls");
						ACTIVE_BULB_ID = "";
						return;
					}
				}

				// Get current values
				auto position = _fe3d.lightEntity_getPosition(ACTIVE_LIGHT_ID);
				auto radius = _fe3d.lightEntity_getRadius(ACTIVE_LIGHT_ID);
				auto color = _fe3d.lightEntity_getColor(ACTIVE_LIGHT_ID);
				auto intensity = _fe3d.lightEntity_getIntensity(ACTIVE_LIGHT_ID);

				// Handle position, radius, color
				if (!screen->getButton("position")->isHoverable())
				{
					_handleValueChanging("pointLightPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
					_handleValueChanging("pointLightPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
					_handleValueChanging("pointLightPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
					_handleValueChanging("pointLightPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
					_handleValueChanging("pointLightPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
					_handleValueChanging("pointLightPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
					_fe3d.modelEntity_setPosition(ACTIVE_BULB_ID, position);
					_fe3d.lightEntity_setPosition(ACTIVE_LIGHT_ID, position);
				}
				else if (!screen->getButton("radius")->isHoverable())
				{
					_handleValueChanging("pointLightPropertiesMenu", "xPlus", "x", radius.x, (_editorSpeed / 100.0f), 1.0f, 0.0f);
					_handleValueChanging("pointLightPropertiesMenu", "xMinus", "x", radius.x, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
					_handleValueChanging("pointLightPropertiesMenu", "yPlus", "y", radius.y, (_editorSpeed / 100.0f), 1.0f, 0.0f);
					_handleValueChanging("pointLightPropertiesMenu", "yMinus", "y", radius.y, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
					_handleValueChanging("pointLightPropertiesMenu", "zPlus", "z", radius.z, (_editorSpeed / 100.0f), 1.0f, 0.0f);
					_handleValueChanging("pointLightPropertiesMenu", "zMinus", "z", radius.z, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
					_fe3d.lightEntity_setRadius(ACTIVE_LIGHT_ID, radius);
				}
				else if (!screen->getButton("color")->isHoverable())
				{
					_handleValueChanging("pointLightPropertiesMenu", "xPlus", "x", color.r, LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
					_handleValueChanging("pointLightPropertiesMenu", "xMinus", "x", color.r, -LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
					_handleValueChanging("pointLightPropertiesMenu", "yPlus", "y", color.g, LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
					_handleValueChanging("pointLightPropertiesMenu", "yMinus", "y", color.g, -LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
					_handleValueChanging("pointLightPropertiesMenu", "zPlus", "z", color.b, LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
					_handleValueChanging("pointLightPropertiesMenu", "zMinus", "z", color.b, -LIGHT_COLOR_CHANGING_SPEED, 255.0f, 0.0f, 1.0f);
					_fe3d.modelEntity_setColor(ACTIVE_BULB_ID, color);
					_fe3d.lightEntity_setColor(ACTIVE_LIGHT_ID, color);
				}
				
				// Handle intensity
				_handleValueChanging("pointLightPropertiesMenu", "intensityPlus", "intensity", intensity, LIGHT_INTENSITY_CHANGING_SPEED, 100.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "intensityMinus", "intensity", intensity, -LIGHT_INTENSITY_CHANGING_SPEED, 100.0f, 0.0f);
				_fe3d.lightEntity_setIntensity(ACTIVE_LIGHT_ID, intensity);
			}
		}
	}
}