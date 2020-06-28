#include "entity_placer.hpp"

void EntityPlacer::_updateModelEditing()
{
	static int lightnessMultiplier = 1;
	static string activeModelID = "";
	string selectedModelID = "";

	if (_isLoaded)
	{
		if (_currentModelName == "")
		{
			// Check if user selected model
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				if (_fe3d.collision_checkCursorInEntity(entityID))
				{
					// Select model if none active yet
					if (activeModelID == "")
					{
						selectedModelID = entityID;

						// Check if user clicked model
						if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
						{
							activeModelID = selectedModelID;

							// Activate properties screen
							_rightWindow->setActiveScreen("entityProperties");
							_rightWindow->getScreen("entityProperties")->getButton("translation")->setHoverable(false);
							_rightWindow->getScreen("entityProperties")->getButton("rotation")->setHoverable(true);
							_rightWindow->getScreen("entityProperties")->getButton("scaling")->setHoverable(true);

							// Update selected model text
							string textEntityID = _gui->getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
							_fe3d.textEntity_show(textEntityID);
							_fe3d.textEntity_setTextContent(textEntityID, "Selected model: " + activeModelID, 0.025f);

							// Filling writefields
							vec3 position = _fe3d.gameEntity_getPosition(activeModelID);
							_rightWindow->getScreen("entityProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(position.x)));
							_rightWindow->getScreen("entityProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(position.y)));
							_rightWindow->getScreen("entityProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(position.z)));
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
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					activeModelID = "";
				}
			}

			// Always set active model as selected
			if(activeModelID != "" && selectedModelID == "")
			{
				selectedModelID = activeModelID;
			}

			// Resetting lightness direciton if nothing selected
			if (selectedModelID == "")
			{
				lightnessMultiplier = 1;
			}

			// Update lightness direction
			if (selectedModelID != "")
			{
				// Check if lightness reached bounds
				if (_fe3d.gameEntity_getLightness(selectedModelID) >= 1.0f || _fe3d.gameEntity_getLightness(selectedModelID) <= 0.0f)
				{
					lightnessMultiplier *= -1;
				}

				// Change lightness
				float speed = (_blinkingSpeed * static_cast<float>(lightnessMultiplier));
				_fe3d.gameEntity_setLightness(selectedModelID, _fe3d.gameEntity_getLightness(selectedModelID) + speed);
			}

			// Update options screen
			if (activeModelID != "")
			{
				// GUI management
				if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
				{
					if (_rightWindow->getScreen("entityProperties")->getButton("translation")->isHovered()) // Translation button
					{
						_transformation = Transformation::TRANSLATION;

						// Filling writefields
						vec3 position = _fe3d.gameEntity_getPosition(activeModelID);
						_rightWindow->getScreen("entityProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(position.x)));
						_rightWindow->getScreen("entityProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(position.y)));
						_rightWindow->getScreen("entityProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(position.z)));

						// Update buttons hoverability
						_rightWindow->getScreen("entityProperties")->getButton("translation")->setHoverable(false);
						_rightWindow->getScreen("entityProperties")->getButton("rotation")->setHoverable(true);
						_rightWindow->getScreen("entityProperties")->getButton("scaling")->setHoverable(true);
					}
					else if (_rightWindow->getScreen("entityProperties")->getButton("rotation")->isHovered()) // Rotation button
					{
						_transformation = Transformation::ROTATION;

						// Filling writefields
						vec3 rotation = _fe3d.gameEntity_getRotation(activeModelID);
						_rightWindow->getScreen("entityProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(rotation.x)));
						_rightWindow->getScreen("entityProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(rotation.y)));
						_rightWindow->getScreen("entityProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(rotation.z)));

						// Update buttons hoverability
						_rightWindow->getScreen("entityProperties")->getButton("translation")->setHoverable(true);
						_rightWindow->getScreen("entityProperties")->getButton("rotation")->setHoverable(false);
						_rightWindow->getScreen("entityProperties")->getButton("scaling")->setHoverable(true);
					}
					else if (_rightWindow->getScreen("entityProperties")->getButton("scaling")->isHovered()) // Scaling button
					{
						_transformation = Transformation::SCALING;

						// Filling writefields
						vec3 size = _fe3d.gameEntity_getSize(activeModelID);
						_rightWindow->getScreen("entityProperties")->getWriteField("x")->setTextContent(std::to_string(static_cast<int>(size.x * 10.0f)));
						_rightWindow->getScreen("entityProperties")->getWriteField("y")->setTextContent(std::to_string(static_cast<int>(size.y * 10.0f)));
						_rightWindow->getScreen("entityProperties")->getWriteField("z")->setTextContent(std::to_string(static_cast<int>(size.z * 10.0f)));

						// Update buttons hoverability
						_rightWindow->getScreen("entityProperties")->getButton("translation")->setHoverable(true);
						_rightWindow->getScreen("entityProperties")->getButton("rotation")->setHoverable(true);
						_rightWindow->getScreen("entityProperties")->getButton("scaling")->setHoverable(false);
					}
				}

				// Current model position / rotation / size
				vec3 newValue;
				if (_transformation == Transformation::TRANSLATION)
				{
					newValue = _fe3d.gameEntity_getPosition(activeModelID);
				}
				else if (_transformation == Transformation::ROTATION)
				{
					newValue = _fe3d.gameEntity_getRotation(activeModelID);
				}
				else if (_transformation == Transformation::SCALING)
				{
					newValue = _fe3d.gameEntity_getSize(activeModelID);
				}

				// X
				if (_rightWindow->getScreen("entityProperties")->getWriteField("x")->confirmedInput())
				{
					if (_rightWindow->getScreen("entityProperties")->getWriteField("x")->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;
						newValue.x = float(stoi(_rightWindow->getScreen("entityProperties")->getWriteField("x")->getTextContent())) / divider;
					}
				}

				// Y
				if (_rightWindow->getScreen("entityProperties")->getWriteField("y")->confirmedInput())
				{
					if (_rightWindow->getScreen("entityProperties")->getWriteField("y")->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;
						newValue.y = float(stoi(_rightWindow->getScreen("entityProperties")->getWriteField("y")->getTextContent())) / divider;
					}
				}

				// Z
				if (_rightWindow->getScreen("entityProperties")->getWriteField("z")->confirmedInput())
				{
					if (_rightWindow->getScreen("entityProperties")->getWriteField("z")->getTextContent() != "")
					{
						float divider = (_transformation == Transformation::SCALING) ? 10.0f : 1.0f;
						newValue.z = float(stoi(_rightWindow->getScreen("entityProperties")->getWriteField("z")->getTextContent())) / divider;
					}
				}

				// Apply new model position / rotation / size
				if (_transformation == Transformation::TRANSLATION)
				{
					_fe3d.gameEntity_setPosition(activeModelID, newValue);
				}
				else if (_transformation == Transformation::ROTATION)
				{
					_fe3d.gameEntity_setRotation(activeModelID, newValue);
				}
				else if (_transformation == Transformation::SCALING)
				{
					_fe3d.gameEntity_setSize(activeModelID, newValue);
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
				lightnessMultiplier = 1;
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