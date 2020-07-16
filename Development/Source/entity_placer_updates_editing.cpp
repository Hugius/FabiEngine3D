#include "entity_placer.hpp"

void EntityPlacer::_updateModelEditing()
{
	static int selectedLightnessMultiplier = 1;
	static int activeLightnessMultiplier = 1;
	static string activeModelID = "";
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
							if (selectedModelID != activeModelID)
							{
								activeModelID = selectedModelID;
								_transformation = Transformation::TRANSLATION;

								// Activate properties screen
								_rightWindow->getScreen("modelProperties")->getButton("translation")->setHoverable(false);
								_rightWindow->getScreen("modelProperties")->getButton("rotation")->setHoverable(true);
								_rightWindow->getScreen("modelProperties")->getButton("scaling")->setHoverable(true);

								// Update selected model text
								string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
								_fe3d.textEntity_show(textEntityID);
								_fe3d.textEntity_setTextContent(textEntityID, "Selected: " + activeModelID, 0.025f);

								// Filling writefields
								vec3 position = _fe3d.gameEntity_getPosition(activeModelID);
								_rightWindow->getScreen("modelProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(position.x)));
								_rightWindow->getScreen("modelProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(position.y)));
								_rightWindow->getScreen("modelProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(position.z)));
							}
						}
					}
					else
					{
						// Don't reset if model is active
						if (entityID != activeModelID)
						{
							_fe3d.gameEntity_setLightness(entityID, 1.0f);
						}
					}
				}
			}

			// Check if user made the active model inactive
			if (selectedModelID == "" && activeModelID != "" && _fe3d.misc_isMouseInsideViewport() && !_gui->getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT))
				{
					activeModelID = "";
					_rightWindow->setActiveScreen("main");
					string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
					_fe3d.textEntity_hide(textEntityID);
				}
			}

			// Update model lightness blinking
			if (selectedModelID != activeModelID)
			{
				_updateModelBlinking(selectedModelID, selectedLightnessMultiplier);
			}
			_updateModelBlinking(activeModelID, activeLightnessMultiplier);

			// Update properties screen
			if (activeModelID != "")
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
						_fe3d.gameEntity_setStaticToCamera(activeModelID, true);
						_fe3d.aabbEntity_setResponsiveness(activeModelID, false);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.gameEntity_delete(activeModelID);
						_rightWindow->setActiveScreen("main");
						activeModelID = "";
						string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
						_fe3d.textEntity_hide(textEntityID);
						return;
					}
				}

				// Current model position / rotation / size
				vec3 oldValue;
				vec3 newValue;
				if (_transformation == Transformation::TRANSLATION)
				{
					oldValue = _fe3d.gameEntity_getPosition(activeModelID);
					newValue = oldValue;
				}
				else if (_transformation == Transformation::ROTATION)
				{
					oldValue = _fe3d.gameEntity_getRotation(activeModelID);
					newValue = oldValue;
				}
				else if (_transformation == Transformation::SCALING)
				{
					oldValue = _fe3d.gameEntity_getSize(activeModelID);
					newValue = oldValue;
				}

				// GUI management (held down)
				if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
				{
					if (_rightWindow->getScreen("modelProperties")->getButton("xPlus")->isHovered()) // Increasing X
					{
						newValue += vec3(_transformationSpeed, 0.0f, 0.0f);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("xMinus")->isHovered()) // Decreasing X
					{
						newValue -= vec3(_transformationSpeed, 0.0f, 0.0f);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("yPlus")->isHovered()) // Increasing Y
					{
						newValue += vec3(0.0f, _transformationSpeed, 0.0f);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("yMinus")->isHovered()) // Decreasing Y
					{
						newValue -= vec3(0.0f, _transformationSpeed, 0.0f);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("zPlus")->isHovered()) // Increasing Z
					{
						newValue += vec3(0.0f, 0.0f, _transformationSpeed);
					}
					else if (_rightWindow->getScreen("modelProperties")->getButton("zMinus")->isHovered()) // Decreasing Z
					{
						newValue -= vec3(0.0f, 0.0f, _transformationSpeed);
					}
				}

				// Setting X
				auto writefield = _rightWindow->getScreen("modelProperties")->getWriteField("x");
				if (writefield->confirmedInput())
				{
					if (writefield->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;

						// Cannot be empty
						if (writefield->getTextContent() == "-")
						{
							writefield->setTextContent(std::to_string(oldValue.x));
						}

						newValue.x = float(stoi(writefield->getTextContent())) / divider;
					}
				}

				// Setting Y
				writefield = _rightWindow->getScreen("modelProperties")->getWriteField("y");
				if (writefield->confirmedInput())
				{
					if (writefield->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;

						// Cannot be empty
						if (writefield->getTextContent() == "-")
						{
							writefield->setTextContent(std::to_string(oldValue.y));
						}

						newValue.y = float(stoi(writefield->getTextContent())) / divider;
					}
				}

				// Setting Z
				writefield = _rightWindow->getScreen("modelProperties")->getWriteField("z");
				if (writefield->confirmedInput())
				{
					if (writefield->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;

						// Cannot be empty
						if (writefield->getTextContent() == "-")
						{
							writefield->setTextContent(std::to_string(oldValue.z));
						}

						newValue.z = float(stoi(writefield->getTextContent())) / divider;
					}
				}

				// Apply new model position / rotation / size
				if (_transformation == Transformation::TRANSLATION)
				{
					_fe3d.gameEntity_setPosition(activeModelID, newValue);
				}
				else if (_transformation == Transformation::ROTATION)
				{
					newValue.x = std::fmodf(newValue.x, 360.0f);
					newValue.y = std::fmodf(newValue.y, 360.0f);
					newValue.z = std::fmodf(newValue.z, 360.0f);
					_fe3d.gameEntity_setRotation(activeModelID, newValue);
				}
				else if (_transformation == Transformation::SCALING)
				{
					_fe3d.gameEntity_setSize(activeModelID, newValue);
					float changeX = newValue.x / oldValue.x;
					float changeY = newValue.y / oldValue.y; 
					float changeZ = newValue.z / oldValue.z;
					_fe3d.aabbEntity_setSize(activeModelID, _fe3d.aabbEntity_getSize(activeModelID) * vec3(changeX, changeY, changeZ));
				}

				// Filling writefields - X
				if (!_rightWindow->getScreen("modelProperties")->getWriteField("x")->isActive())
				{
					// Filling writefields - position X
					if (_transformation == Transformation::TRANSLATION)
					{
						vec3 position = _fe3d.gameEntity_getPosition(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(position.x)));
					}

					// Filling writefields - rotation X
					if (_transformation == Transformation::ROTATION)
					{
						vec3 rotation = _fe3d.gameEntity_getRotation(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(rotation.x)));
					}

					// Filling writefields - scaling X
					if (_transformation == Transformation::SCALING)
					{
						vec3 size = _fe3d.gameEntity_getSize(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(size.x * 10.0f)));
					}
				}

				// Filling writefields - Y
				if (!_rightWindow->getScreen("modelProperties")->getWriteField("y")->isActive())
				{
					// Filling writefields - position
					if (_transformation == Transformation::TRANSLATION)
					{
						vec3 position = _fe3d.gameEntity_getPosition(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(position.y)));
					}

					// Filling writefields - rotation
					if (_transformation == Transformation::ROTATION)
					{
						vec3 rotation = _fe3d.gameEntity_getRotation(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(rotation.y)));
					}

					// Filling writefields - scaling
					if (_transformation == Transformation::SCALING)
					{
						vec3 size = _fe3d.gameEntity_getSize(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(size.y * 10.0f)));
					}
				}

				// Filling writefields - Z
				if (!_rightWindow->getScreen("modelProperties")->getWriteField("z")->isActive())
				{
					// Filling writefields - position
					if (_transformation == Transformation::TRANSLATION)
					{
						vec3 position = _fe3d.gameEntity_getPosition(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(position.z)));
					}

					// Filling writefields - rotation
					if (_transformation == Transformation::ROTATION)
					{
						vec3 rotation = _fe3d.gameEntity_getRotation(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(rotation.z)));
					}

					// Filling writefields - scaling
					if (_transformation == Transformation::SCALING)
					{
						vec3 size = _fe3d.gameEntity_getSize(activeModelID);
						_rightWindow->getScreen("modelProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(size.z * 10.0f)));
					}
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
					selectedLightnessMultiplier = 1;
					activeModelID = "";
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

				// Current model position
				vec3 newPosition = _fe3d.gameEntity_getPosition(ACTIVE_BULB_ID);
				float newIntensity = _fe3d.lightEntity_getIntensity(ACTIVE_LIGHT_ID);

				// GUI management (held down)
				if (_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_LEFT))
				{
					if (_rightWindow->getScreen("lightProperties")->getButton("intensityPlus")->isHovered()) // Increasing intensity
					{
						newIntensity += _transformationSpeed;
					}
					else if (_rightWindow->getScreen("lightProperties")->getButton("intensityMinus")->isHovered()) // Decreasing intensity
					{
						newIntensity -= _transformationSpeed;
					}
					else if (_rightWindow->getScreen("lightProperties")->getButton("xPlus")->isHovered()) // Increasing X
					{
						newPosition += vec3(_transformationSpeed, 0.0f, 0.0f);
					}
					else if (_rightWindow->getScreen("lightProperties")->getButton("xMinus")->isHovered()) // Decreasing X
					{
						newPosition -= vec3(_transformationSpeed, 0.0f, 0.0f);
					}
					else if (_rightWindow->getScreen("lightProperties")->getButton("yPlus")->isHovered()) // Increasing Y
					{
						newPosition += vec3(0.0f, _transformationSpeed, 0.0f);
					}
					else if (_rightWindow->getScreen("lightProperties")->getButton("yMinus")->isHovered()) // Decreasing Y
					{
						newPosition -= vec3(0.0f, _transformationSpeed, 0.0f);
					}
					else if (_rightWindow->getScreen("lightProperties")->getButton("zPlus")->isHovered()) // Increasing Z
					{
						newPosition += vec3(0.0f, 0.0f, _transformationSpeed);
					}
					else if (_rightWindow->getScreen("lightProperties")->getButton("zMinus")->isHovered()) // Decreasing Z
					{
						newPosition -= vec3(0.0f, 0.0f, _transformationSpeed);
					}
				}

				// Filling writefields - intensity
				if (!_rightWindow->getScreen("lightProperties")->getWriteField("intensity")->isActive())
				{
					float intensity = _fe3d.lightEntity_getIntensity(ACTIVE_LIGHT_ID);
					_rightWindow->getScreen("lightProperties")->getWriteField("intensity")->setTextContent(std::to_string(static_cast<int>(intensity)));
				}

				// Filling writefields - X
				if (!_rightWindow->getScreen("lightProperties")->getWriteField("x")->isActive())
				{
					vec3 position = _fe3d.gameEntity_getPosition(ACTIVE_BULB_ID);
					_rightWindow->getScreen("lightProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(position.x)));
				}

				// Filling writefields - Y
				if (!_rightWindow->getScreen("lightProperties")->getWriteField("y")->isActive())
				{
					vec3 position = _fe3d.gameEntity_getPosition(ACTIVE_BULB_ID);
					_rightWindow->getScreen("lightProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(position.y)));
				}

				// Filling writefields - Z
				if (!_rightWindow->getScreen("lightProperties")->getWriteField("z")->isActive())
				{
					vec3 position = _fe3d.gameEntity_getPosition(ACTIVE_BULB_ID);
					_rightWindow->getScreen("lightProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(position.z)));
				}

				// Applying new values
				_fe3d.gameEntity_setPosition(ACTIVE_BULB_ID, newPosition);
				_fe3d.lightEntity_setPosition(ACTIVE_LIGHT_ID, newPosition);
				_fe3d.lightEntity_setIntensity(ACTIVE_LIGHT_ID, newIntensity);
			}
		}
	}
}