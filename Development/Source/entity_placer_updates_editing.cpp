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
		if (_currentModelName == "")
		{
			// Check if user selected model
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				if (_fe3d.collision_checkCursorInEntity(entityID))
				{
					selectedModelID = entityID;

					// Check if user clicked model
					if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT))
					{
						// Check if same model is clicked again
						if (selectedModelID != activeModelID)
						{
							activeModelID = selectedModelID;
							_transformation = Transformation::TRANSLATION;

							// Activate properties screen
							_rightWindow->setActiveScreen("modelProperties");
							_rightWindow->getScreen("modelProperties")->getButton("translation")->setHoverable(false);
							_rightWindow->getScreen("modelProperties")->getButton("rotation")->setHoverable(true);
							_rightWindow->getScreen("modelProperties")->getButton("scaling")->setHoverable(true);

							// Update selected model text
							string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
							_fe3d.textEntity_show(textEntityID);
							_fe3d.textEntity_setTextContent(textEntityID, "Selected model: " + activeModelID, 0.025f);

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

			// Check if user made the active model inactive
			if (selectedModelID == "" && _fe3d.misc_isMouseInsideViewport() && !_gui->getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(Input::MOUSE_BUTTON_RIGHT))
				{
					activeModelID = "";
				}
			}

			// Resetting lightness direciton if nothing selected
			if (selectedModelID == "")
			{
				selectedLightnessMultiplier = 1;
			}

			// Resetting lightness direciton if nothing active
			if (activeModelID == "")
			{
				activeLightnessMultiplier = 1;
			}

			// Update selected model lightness
			if (selectedModelID != "")
			{
				// Check if lightness reached bounds
				if (_fe3d.gameEntity_getLightness(selectedModelID) >= 1.0f || _fe3d.gameEntity_getLightness(selectedModelID) <= 0.0f)
				{
					selectedLightnessMultiplier *= -1;
				}
				
				// Set lightness
				float speed = (_blinkingSpeed * static_cast<float>(selectedLightnessMultiplier));
				_fe3d.gameEntity_setLightness(selectedModelID, _fe3d.gameEntity_getLightness(selectedModelID) + speed);
			}

			// Update active model lightness
			if (activeModelID != "")
			{
				// Check if lightness reached bounds
				if (_fe3d.gameEntity_getLightness(activeModelID) >= 1.0f || _fe3d.gameEntity_getLightness(activeModelID) <= 0.0f)
				{
					activeLightnessMultiplier *= -1;
				}

				// Set lightness
				float speed = (_blinkingSpeed * static_cast<float>(activeLightnessMultiplier));
				_fe3d.gameEntity_setLightness(activeModelID, _fe3d.gameEntity_getLightness(activeModelID) + speed);
			}

			// Update options screen
			if (activeModelID != "")
			{
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
				if (_rightWindow->getScreen("modelProperties")->getWriteField("x")->confirmedInput())
				{
					if (_rightWindow->getScreen("modelProperties")->getWriteField("x")->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;
						newValue.x = float(stoi(_rightWindow->getScreen("modelProperties")->getWriteField("x")->getTextContent())) / divider;
					}
				}

				// Setting Y
				if (_rightWindow->getScreen("modelProperties")->getWriteField("y")->confirmedInput())
				{
					if (_rightWindow->getScreen("modelProperties")->getWriteField("y")->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;
						newValue.y = float(stoi(_rightWindow->getScreen("modelProperties")->getWriteField("y")->getTextContent())) / divider;
					}
				}

				// Setting Z
				if (_rightWindow->getScreen("modelProperties")->getWriteField("z")->confirmedInput())
				{
					if (_rightWindow->getScreen("modelProperties")->getWriteField("z")->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;
						newValue.z = float(stoi(_rightWindow->getScreen("modelProperties")->getWriteField("z")->getTextContent())) / divider;
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

				// Filling writefields - position
				if (_transformation == Transformation::TRANSLATION)
				{
					vec3 position = _fe3d.gameEntity_getPosition(activeModelID);
					_rightWindow->getScreen("modelProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(position.x)));
					_rightWindow->getScreen("modelProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(position.y)));
					_rightWindow->getScreen("modelProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(position.z)));
				}

				// Filling writefields - rotation
				if (_transformation == Transformation::ROTATION)
				{
					vec3 rotation = _fe3d.gameEntity_getRotation(activeModelID);
					_rightWindow->getScreen("modelProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(rotation.x)));
					_rightWindow->getScreen("modelProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(rotation.y)));
					_rightWindow->getScreen("modelProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(rotation.z)));
				}

				// Filling writefields - scaling
				if (_transformation == Transformation::SCALING)
				{
					vec3 size = _fe3d.gameEntity_getSize(activeModelID);
					_rightWindow->getScreen("modelProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(size.x * 10.0f)));
					_rightWindow->getScreen("modelProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(size.y * 10.0f)));
					_rightWindow->getScreen("modelProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(size.z * 10.0f)));
				}
			}
			else
			{
				// Dectivate properties screen
				_rightWindow->setActiveScreen("main");
			}
		}
		else
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

void EntityPlacer::_updateBillboardEditing()
{
	if (_isLoaded)
	{

	}
}

void EntityPlacer::_updateLightEditing()
{
	if (_isLoaded)
	{

	}
}