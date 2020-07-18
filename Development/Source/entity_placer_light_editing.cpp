#include "entity_placer.hpp"

#define ACTIVE_BULB_ID activeLightBulbID
#define ACTIVE_LIGHT_ID activeLightBulbID.substr(1, activeLightBulbID.size() - 1)

void EntityPlacer::_updateLightEditing()
{
	static int selectedSizeMultiplier = 1;
	static int activeSizeMultiplier = 1;
	static string activeLightBulbID = "";
	string selectedLightBulbID = "";

	if (_isLoaded)
	{
		if (_currentPreviewModelName == "" && !_isPlacingPointlight)
		{
			// Check if user selected a lightbulb model
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				// Must be light preview entity
				if (entityID.substr(0, 11) == "@pointlight")
				{
					// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
					if (_fe3d.collision_checkCursorInEntity(entityID) && _fe3d.misc_isMouseInsideViewport() &&
						!_gui->getGlobalScreen()->isFocused() && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT))
					{
						// Set new selected lightbulb
						selectedLightBulbID = entityID;

						// Check if user clicked lightbulb
						if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
						{
							// Check if same lightbulb is clicked again
							if (selectedLightBulbID != ACTIVE_BULB_ID)
							{
								ACTIVE_BULB_ID = selectedLightBulbID;
								_transformation = Transformation::TRANSLATION;

								// Update selected lightbulb text
								string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedPointlightName")->getEntityID();
								string lightID = ACTIVE_LIGHT_ID;
								_fe3d.textEntity_show(textEntityID);
								_fe3d.textEntity_setTextContent(textEntityID, "Selected: " + lightID, 0.025f);

								// Filling writefields
								vec3 position = _fe3d.gameEntity_getPosition(ACTIVE_BULB_ID);
								_rightWindow->getScreen("lightProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(position.x)));
								_rightWindow->getScreen("lightProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(position.y)));
								_rightWindow->getScreen("lightProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(position.z)));
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
			if (selectedLightBulbID == "" && ACTIVE_BULB_ID != "" && _fe3d.misc_isMouseInsideViewport() && !_gui->getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT))
				{
					ACTIVE_BULB_ID = "";
					_rightWindow->setActiveScreen("main");
					string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedPointlightName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}

			// Update lightbulb animations
			if (selectedLightBulbID != ACTIVE_BULB_ID)
			{
				_updateLightbulbAnimation(selectedLightBulbID, selectedSizeMultiplier);
			}
			_updateLightbulbAnimation(ACTIVE_BULB_ID, activeSizeMultiplier);

			// Update properties screen
			if (ACTIVE_BULB_ID != "")
			{
				_rightWindow->setActiveScreen("lightProperties");

				// GUI management (pressed)
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					if (_rightWindow->getScreen("lightProperties")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.gameEntity_delete(ACTIVE_BULB_ID);
						_fe3d.lightEntity_delete(ACTIVE_LIGHT_ID);
						_rightWindow->setActiveScreen("main");
						ACTIVE_BULB_ID = "";
						string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedPointlightName")->getEntityID();
						_fe3d.textEntity_hide(textEntityID);
						return;
					}
				}

				// Get current values
				vec3 position = _fe3d.gameEntity_getPosition(ACTIVE_BULB_ID);
				vec3 color = _fe3d.gameEntity_getColor(ACTIVE_BULB_ID);
				float intensity = _fe3d.lightEntity_getIntensity(ACTIVE_LIGHT_ID);

				// Update value filling and changing
				_handleValueChanging("lightProperties", "intensityPlus", "intensity", intensity, _valueChangingSpeed);
				_handleValueChanging("lightProperties", "intensityMinus", "intensity", intensity, -_valueChangingSpeed);
				_handleValueChanging("lightProperties", "xPlus", "x", position.x, _valueChangingSpeed);
				_handleValueChanging("lightProperties", "xMinus", "x", position.x, -_valueChangingSpeed);
				_handleValueChanging("lightProperties", "yPlus", "y", position.y, _valueChangingSpeed);
				_handleValueChanging("lightProperties", "yMinus", "y", position.y, -_valueChangingSpeed);
				_handleValueChanging("lightProperties", "zPlus", "z", position.z, _valueChangingSpeed);
				_handleValueChanging("lightProperties", "zMinus", "z", position.z, -_valueChangingSpeed);
				_handleValueChanging("lightProperties", "rPlus", "r", color.r, _valueChangingSpeed);
				_handleValueChanging("lightProperties", "rMinus", "r", color.r, -_valueChangingSpeed);
				_handleValueChanging("lightProperties", "gPlus", "g", color.g, _valueChangingSpeed);
				_handleValueChanging("lightProperties", "gMinus", "g", color.g, -_valueChangingSpeed);
				_handleValueChanging("lightProperties", "bPlus", "b", color.b, _valueChangingSpeed);
				_handleValueChanging("lightProperties", "bMinus", "b", color.b, -_valueChangingSpeed);

				// Apply new values
				_fe3d.lightEntity_setIntensity(ACTIVE_LIGHT_ID, intensity);
				_fe3d.lightEntity_setPosition(ACTIVE_LIGHT_ID, position);
				_fe3d.lightEntity_setColor(ACTIVE_LIGHT_ID, color);
				_fe3d.gameEntity_setColor(ACTIVE_BULB_ID, color);
				_fe3d.gameEntity_setPosition(ACTIVE_BULB_ID, position);
			}
		}
	}
}