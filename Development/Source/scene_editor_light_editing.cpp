#include "scene_editor.hpp"

#define ACTIVE_BULB_ID _activeLightBulbID
#define ACTIVE_LIGHT_ID _activeLightBulbID.substr(1)

void SceneEditor::_updateLightEditing()
{
	if (_isLoaded)
	{
		_selectedLightBulbID = "";

		if (_currentPreviewModelName == "" && _currentPreviewBillboardName == "" && !_isPlacingPointlight)
		{
			// Check if user selected a lightbulb model
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				// Must be light preview entity
				if (entityID.substr(0, 11) == "@pointlight")
				{
					// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
					if (_fe3d.collision_checkCursorInAny() == entityID && _fe3d.misc_isMouseInsideViewport() &&
						!_gui->getGlobalScreen()->isFocused() && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
					{
						// Set new selected lightbulb
						_selectedLightBulbID = entityID;

						// Check if nothing is active
						if (_activeLightBulbID == "" && _activeModelID == "" && _activeBillboardID == "")
						{
							string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedPointlightName")->getEntityID();
							_fe3d.textEntity_show(textEntityID);
							_fe3d.textEntity_setTextContent(textEntityID, "Selected light: " + _selectedLightBulbID.substr(1), 0.025f);
						}

						// Change cursor
						_fe3d.guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_pointing.png");

						// Check if user clicked lightbulb
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							// Check if same lightbulb is clicked again
							if (_selectedLightBulbID != ACTIVE_BULB_ID)
							{
								// Set new active light
								ACTIVE_BULB_ID = _selectedLightBulbID;
								_transformation = TransformationType::TRANSLATION;

								// Filling writefields
								vec3 position = _fe3d.gameEntity_getPosition(ACTIVE_BULB_ID);
								_rightWindow->getScreen("pointLightPropertiesMenu")->getWriteField("x")->setTextContent(to_string(static_cast<int>(position.x)));
								_rightWindow->getScreen("pointLightPropertiesMenu")->getWriteField("y")->setTextContent(to_string(static_cast<int>(position.y)));
								_rightWindow->getScreen("pointLightPropertiesMenu")->getWriteField("z")->setTextContent(to_string(static_cast<int>(position.z)));
							
								// Update selected text
								string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedPointlightName")->getEntityID();
								_fe3d.textEntity_show(textEntityID);
								_fe3d.textEntity_setTextContent(textEntityID, "Active light: " + _selectedLightBulbID.substr(1), 0.025f);
							}
						}
					}
					else
					{
						// Don't reset if lightbulb is active
						if (entityID != ACTIVE_BULB_ID)
						{
							_fe3d.gameEntity_setSize(entityID, _defaultLightbulbSize);
							_fe3d.aabbEntity_setSize(entityID, _defaultLightbulbAabbSize);
						}
					}
				}
			}
			
			// Check if user made the active lightbulb inactive
			if (_selectedLightBulbID == "" && ACTIVE_BULB_ID != "" && _fe3d.misc_isMouseInsideViewport() && !_gui->getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					ACTIVE_BULB_ID = "";
					_rightWindow->setActiveScreen("main");
				}
			}

			// Update lightbulb animations
			if (_selectedLightBulbID != ACTIVE_BULB_ID)
			{
				_updateLightbulbAnimation(_selectedLightBulbID, _selectedLightSizeMultiplier);
			}
			_updateLightbulbAnimation(ACTIVE_BULB_ID, _activeLightSizeMultiplier);

			// Update properties screen
			if (ACTIVE_BULB_ID != "")
			{
				_rightWindow->setActiveScreen("pointLightPropertiesMenu");

				// GUI management (pressed)
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (_rightWindow->getScreen("pointLightPropertiesMenu")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.gameEntity_delete(ACTIVE_BULB_ID);
						_fe3d.lightEntity_delete(ACTIVE_LIGHT_ID);
						_rightWindow->setActiveScreen("main");
						ACTIVE_BULB_ID = "";
						return;
					}
				}

				// Get current values
				vec3 position = _fe3d.lightEntity_getPosition(ACTIVE_LIGHT_ID);
				vec3 color = _fe3d.lightEntity_getColor(ACTIVE_LIGHT_ID);
				float intensity = _fe3d.lightEntity_getIntensity(ACTIVE_LIGHT_ID);
				float distance = _fe3d.lightEntity_getDistanceFactor(ACTIVE_LIGHT_ID);

				// Update value filling and changing
				_handleValueChanging("pointLightPropertiesMenu", "distancePlus", "distance", distance, _lightingChangingSpeed, 10.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "distanceMinus", "distance", distance, -_lightingChangingSpeed, 10.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "intensityPlus", "intensity", intensity, _lightingChangingSpeed, 10.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "intensityMinus", "intensity", intensity, -_lightingChangingSpeed, 10.0f, 0.0f);
				_handleValueChanging("pointLightPropertiesMenu", "xPlus", "x", position.x, _movementChangingSpeed);
				_handleValueChanging("pointLightPropertiesMenu", "xMinus", "x", position.x, -_movementChangingSpeed);
				_handleValueChanging("pointLightPropertiesMenu", "yPlus", "y", position.y, _movementChangingSpeed);
				_handleValueChanging("pointLightPropertiesMenu", "yMinus", "y", position.y, -_movementChangingSpeed);
				_handleValueChanging("pointLightPropertiesMenu", "zPlus", "z", position.z, _movementChangingSpeed);
				_handleValueChanging("pointLightPropertiesMenu", "zMinus", "z", position.z, -_movementChangingSpeed);
				_handleValueChanging("pointLightPropertiesMenu", "rPlus", "r", color.r, _colorChangingSpeed, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "rMinus", "r", color.r, -_colorChangingSpeed, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "gPlus", "g", color.g, _colorChangingSpeed, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "gMinus", "g", color.g, -_colorChangingSpeed, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "bPlus", "b", color.b, _colorChangingSpeed, 255.0f, 0.0f, 1.0f);
				_handleValueChanging("pointLightPropertiesMenu", "bMinus", "b", color.b, -_colorChangingSpeed, 255.0f, 0.0f, 1.0f);
				
				// Apply new values
				_fe3d.gameEntity_setPosition(ACTIVE_BULB_ID, position);
				_fe3d.lightEntity_setPosition(ACTIVE_LIGHT_ID, position);
				_fe3d.gameEntity_setColor(ACTIVE_BULB_ID, color);
				_fe3d.lightEntity_setColor(ACTIVE_LIGHT_ID, color);
				_fe3d.lightEntity_setIntensity(ACTIVE_LIGHT_ID, intensity);
				_fe3d.lightEntity_setDistanceFactor(ACTIVE_LIGHT_ID, distance);
			}

			// Check if light is still selected or active
			string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedPointlightName")->getEntityID();
			if (_selectedLightBulbID == "" && _activeLightBulbID == "")
			{
				_fe3d.textEntity_hide(textEntityID);
			}
			else
			{
				if (_selectedModelID == "" && _activeModelID == "" && _selectedBillboardID == "" && _activeBillboardID == "")
				{
					_fe3d.textEntity_show(textEntityID);
				}
			}
		}
	}
}