#include "scene_editor.hpp"

void SceneEditor::_updateModelEditing()
{
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
						_selectedModelID = entityID;

						// Check if user clicked model
						if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
						{
							// Check if same model is clicked again
							if (_selectedModelID != _activeModelID)
							{
								_activateModel(_selectedModelID);
							}
						}
					}
					else
					{
						// Don't reset if model is active
						if (entityID != _activeModelID && _selectedModelID == "")
						{
							_fe3d.gameEntity_setLightness(entityID, 1.0f);
						}
					}
				}
			}

			// Check if user made the active model inactive
			if (_selectedModelID == "" && _activeModelID != "" && _fe3d.misc_isMouseInsideViewport() && !_gui->getGlobalScreen()->isFocused())
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
			if (_selectedModelID != _activeModelID)
			{
				_updateModelBlinking(_selectedModelID, _selectedLightnessMultiplier);
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

				// Get entity transformation
				vec3 position = _fe3d.gameEntity_getPosition(_activeModelID);
				vec3 rotation = _fe3d.gameEntity_getRotation(_activeModelID);
				vec3 size	  = _fe3d.gameEntity_getSize(_activeModelID);

				// Apply new model position / rotation / size
				if (_transformation == Transformation::TRANSLATION)
				{
					_handleValueChanging("modelProperties", "xPlus", "x", position.x, _movementChangingSpeed);
					_handleValueChanging("modelProperties", "xMinus", "x", position.x, -_movementChangingSpeed);
					_handleValueChanging("modelProperties", "yPlus", "y", position.y, _movementChangingSpeed);
					_handleValueChanging("modelProperties", "yMinus", "y", position.y, -_movementChangingSpeed);
					_handleValueChanging("modelProperties", "zPlus", "z", position.z, _movementChangingSpeed);
					_handleValueChanging("modelProperties", "zMinus", "z", position.z, -_movementChangingSpeed);
					_fe3d.gameEntity_setPosition(_activeModelID, position);
				}
				else if (_transformation == Transformation::ROTATION)
				{
					_handleValueChanging("modelProperties", "xPlus", "x", rotation.x, _movementChangingSpeed);
					_handleValueChanging("modelProperties", "xMinus", "x", rotation.x, -_movementChangingSpeed);
					_handleValueChanging("modelProperties", "yPlus", "y", rotation.y, _movementChangingSpeed);
					_handleValueChanging("modelProperties", "yMinus", "y", rotation.y, -_movementChangingSpeed);
					_handleValueChanging("modelProperties", "zPlus", "z", rotation.z, _movementChangingSpeed);
					_handleValueChanging("modelProperties", "zMinus", "z", rotation.z, -_movementChangingSpeed);
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
					_handleValueChanging("modelProperties", "xPlus", "x", size.x, _movementChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "xMinus", "x", size.x, -_movementChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "yPlus", "y", size.y, _movementChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "yMinus", "y", size.y, -_movementChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "zPlus", "z", size.z, _movementChangingSpeed, factor, factor);
					_handleValueChanging("modelProperties", "zMinus", "z", size.z, -_movementChangingSpeed, factor, factor);
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
					_selectedModelID = "";
				}
			}
		}

		_selectedModelID = "";
	}
}