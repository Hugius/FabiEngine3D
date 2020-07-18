#include "entity_placer.hpp"

void EntityPlacer::_handleValueChanging(string screenID, string buttonID, string wfID, float& value, float adder, float divider, float multiplier)
{
	// Plus & minus button handling
	if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
	{
		if (_rightWindow->getScreen(screenID)->getButton(buttonID)->isHovered())
		{
			value += adder;
		}
	}

	// Writefield handling
	auto writefield = _rightWindow->getScreen(screenID)->getWriteField(wfID);
	if (writefield->confirmedInput())
	{
		if (writefield->getTextContent() != "")
		{
			// Cannot be empty
			if (writefield->getTextContent() == "-")
			{
				writefield->setTextContent(std::to_string(value));
			}

			value = float(stoi(writefield->getTextContent())) / divider;
		}
	}

	// Writefield filling
	if (!_rightWindow->getScreen(screenID)->getWriteField(wfID)->isActive())
	{
		_rightWindow->getScreen(screenID)->getWriteField(wfID)->setTextContent(std::to_string(static_cast<int>(value * multiplier)));
	}
}

void EntityPlacer::_updateModelEditing()
{
	string selectedModelID = "";

	if (_isLoaded)
	{
		// User must not be in placement mode
		if (_currentPreviewModelName == "" && !_isPlacingPointlight)
		{
			// Check if user selected a model
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				// Must not be preview entity
				if (entityID[0] != '@')
				{
					// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
					if (_fe3d.collision_checkCursorInEntity(entityID) && _fe3d.misc_isMouseInsideViewport() &&
						!_gui->getGlobalScreen()->isFocused() && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT))
					{
						// Set new selected model
						selectedModelID = entityID;

						// Check if user clicked model
						if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
						{
							// Check if same model is clicked again
							if (selectedModelID != _activeModelID)
							{
								_activateModel(selectedModelID);
							}
						}
					}
					else
					{
						// Don't reset if model is active
						if (entityID != _activeModelID)
						{
							_fe3d.gameEntity_setLightness(entityID, 1.0f);
						}
					}
				}
			}

			// Check if user made the active model inactive
			if (selectedModelID == "" && _activeModelID != "" && _fe3d.misc_isMouseInsideViewport() && !_gui->getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT))
				{
					_activeModelID = "";
					_rightWindow->setActiveScreen("main");
					string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}

			// Update model lightness blinking
			if (selectedModelID != _activeModelID)
			{
				_updateModelBlinking(selectedModelID, _selectedLightnessMultiplier);
			}
			_updateModelBlinking(_activeModelID, _activeLightnessMultiplier);

			// Update properties screen
			if (_activeModelID != "")
			{
				_rightWindow->setActiveScreen("modelProperties");

				// GUI management (pressed)
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					if (_rightWindow->getScreen("modelProperties")->getButton("translation")->isHovered()) // Translation button
					{
						_transformation = Transformation::TRANSLATION;

						// Update buttons hoverability
						_rightWindow->getScreen("modelProperties")->getButton("translation")->setHoverable(false);
						_rightWindow->getScreen("modelProperties")->getButton("rotation")->setHoverable(true);
						_rightWindow->getScreen("modelProperties")->getButton("scaling")->setHoverable(true);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("rotation")->isHovered()) // Rotation button
					{
						_transformation = Transformation::ROTATION;

						// Update buttons hoverability
						_rightWindow->getScreen("modelProperties")->getButton("translation")->setHoverable(true);
						_rightWindow->getScreen("modelProperties")->getButton("rotation")->setHoverable(false);
						_rightWindow->getScreen("modelProperties")->getButton("scaling")->setHoverable(true);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("scaling")->isHovered()) // Scaling button
					{
						_transformation = Transformation::SCALING;

						// Update buttons hoverability
						_rightWindow->getScreen("modelProperties")->getButton("translation")->setHoverable(true);
						_rightWindow->getScreen("modelProperties")->getButton("rotation")->setHoverable(true);
						_rightWindow->getScreen("modelProperties")->getButton("scaling")->setHoverable(false);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("freeze")->isHovered()) // Freeze button
					{
						_fe3d.gameEntity_setStaticToCamera(_activeModelID, true);
						_fe3d.aabbEntity_setResponsiveness(_activeModelID, false);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.gameEntity_delete(_activeModelID);
						_rightWindow->setActiveScreen("main");
						_activeModelID = "";
						string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
						_fe3d.textEntity_hide(textEntityID);
						return;
					}
				}

				vec3 position = _fe3d.gameEntity_getPosition(_activeModelID);
				vec3 rotation = _fe3d.gameEntity_getRotation(_activeModelID);
				vec3 size	  = _fe3d.gameEntity_getSize(_activeModelID);

				// Apply new model position / rotation / size
				if (_transformation == Transformation::TRANSLATION)
				{
					_handleValueChanging("modelProperties", "xPlus", "x", position.x, _valueChangingSpeed);
					_handleValueChanging("modelProperties", "xMinus", "x", position.x, -_valueChangingSpeed);
					_handleValueChanging("modelProperties", "yPlus", "y", position.y, _valueChangingSpeed);
					_handleValueChanging("modelProperties", "yMinus", "y", position.y, -_valueChangingSpeed);
					_handleValueChanging("modelProperties", "zPlus", "z", position.z, _valueChangingSpeed);
					_handleValueChanging("modelProperties", "zMinus", "z", position.z, -_valueChangingSpeed);
					_fe3d.gameEntity_setPosition(_activeModelID, position);
				}
				else if (_transformation == Transformation::ROTATION)
				{
					_handleValueChanging("modelProperties", "xPlus", "x", rotation.x, _valueChangingSpeed);
					_handleValueChanging("modelProperties", "xMinus", "x", rotation.x, -_valueChangingSpeed);
					_handleValueChanging("modelProperties", "yPlus", "y", rotation.y, _valueChangingSpeed);
					_handleValueChanging("modelProperties", "yMinus", "y", rotation.y, -_valueChangingSpeed);
					_handleValueChanging("modelProperties", "zPlus", "z", rotation.z, _valueChangingSpeed);
					_handleValueChanging("modelProperties", "zMinus", "z", rotation.z, -_valueChangingSpeed);
					rotation.x = std::fmodf(rotation.x, 360.0f);
					rotation.y = std::fmodf(rotation.y, 360.0f);
					rotation.z = std::fmodf(rotation.z, 360.0f);
					_fe3d.gameEntity_setRotation(_activeModelID, rotation);
				}
				else if (_transformation == Transformation::SCALING)
				{
					// Model size
					vec3 oldSize = size;
					float factor = 25.0f;
					_handleValueChanging("modelProperties", "xPlus", "x", size.x, _valueChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "xMinus", "x", size.x, -_valueChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "yPlus", "y", size.y, _valueChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "yMinus", "y", size.y, -_valueChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "zPlus", "z", size.z, _valueChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "zMinus", "z", size.z, -_valueChangingSpeed, factor, factor);
					_fe3d.gameEntity_setSize(_activeModelID, size);

					// AABB size
					float changeX = size.x / oldSize.x;
					float changeY = size.y / oldSize.y; 
					float changeZ = size.z / oldSize.z;
					_fe3d.aabbEntity_setSize(_activeModelID, _fe3d.aabbEntity_getSize(_activeModelID) * vec3(changeX, changeY, changeZ));
				}
			}
		}
		else
		{
			if (_rightWindow->getActiveScreen()->getID() != "main")
			{
				// Reset when user wants to place models again
				for (auto& entityID : _fe3d.gameEntity_getAllIDs())
				{
					_rightWindow->setActiveScreen("main");
					_fe3d.gameEntity_setLightness(entityID, 1.0f);
					_selectedLightnessMultiplier = 1;
					_activeModelID = "";
					selectedModelID = "";
				}
			}
		}
	}
}

void EntityPlacer::_updateBillboardEditing()
{
	if (_isLoaded)
	{

	}
}

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