#include "scene_editor.hpp"

void SceneEditor::_updateModelEditing()
{
	if (_isEditorLoaded)
	{
		// Reset selected model from last frame
		if (!_dontResetSelectedModel)
		{
			_selectedModelID = "";
		}
		else
		{
			_dontResetSelectedModel = false;
		}

		// User must not be in placement mode
		if (_currentPreviewModelName == "" && _currentPreviewBillboardName == "" && !_isPlacingPointlight && _currentPreviewAudioName == "")
		{
			// Check which entity is selected
			auto hoveredID = _fe3d.collision_checkCursorInAny();

			// Check if user selected a model
			for (auto& entityID : _fe3d.gameEntity_getAllIDs())
			{
				// Must not be preview entity
				if (entityID[0] != '@')
				{
					bool hovered = (hoveredID.size() >= entityID.size()) && (hoveredID.substr(0, entityID.size()) == entityID);

					// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
					if (hovered && _fe3d.misc_isCursorInsideViewport() &&
						!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
					{
						// Select hovered model
						_selectModel(entityID);

						// Check if user clicked model
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
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
							_fe3d.gameEntity_setLightness(entityID, _fe3d.gameEntity_getOriginalLightness(entityID));
						}
					}
				}
			}

			// Check if user made the active model inactive
			if (_selectedModelID == "" && _activeModelID != "" && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_activeModelID = "";
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
				}
			}

			// Update model lightness blinking
			if (_selectedModelID != _activeModelID)
			{
				_updateModelBlinking(_selectedModelID, _selectedModelLightnessMultiplier);
			}
			_updateModelBlinking(_activeModelID, _activeModelLightnessMultiplier);

			// Update properties screen
			if (_activeModelID != "")
			{
				_gui.getViewport("right")->getWindow("main")->setActiveScreen("modelPropertiesMenu");

				// GUI management (pressed)
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("translation")->isHovered()) // Translation button
					{
						_transformation = TransformationType::TRANSLATION;

						// Update buttons hoverability
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(false);
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(true);
					}
					else if (_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("rotation")->isHovered()) // Rotation button
					{
						_transformation = TransformationType::ROTATION;

						// Update buttons hoverability
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(true);
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(false);
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(true);
					}
					else if (_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("scaling")->isHovered()) // Scaling button
					{
						_transformation = TransformationType::SCALING;

						// Update buttons hoverability
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(true);
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
						_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(false);
					}
					else if (_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("freeze")->isHovered()) // Freeze button
					{
						// Model
						_fe3d.gameEntity_setStaticToCamera(_activeModelID, true);

						// AABB
						for (auto& aabbID : _fe3d.aabbEntity_getBoundIDs(_activeModelID, true, false))
						{
							_fe3d.aabbEntity_setResponsiveness(aabbID, false);
						}
					}
					else if (_gui.getViewport("right")->getWindow("main")->getScreen("modelPropertiesMenu")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.gameEntity_delete(_activeModelID);
						_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
						_activeModelID = "";
						return;
					}
				}

				// Alternative way of deleting
				if (_fe3d.input_getKeyPressed(InputType::KEY_DELETE))
				{
					_fe3d.gameEntity_delete(_activeModelID);
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
					_activeModelID = "";
					return;
				}

				// Get entity transformation
				Vec3 position = _fe3d.gameEntity_getPosition(_activeModelID);
				Vec3 rotation = _fe3d.gameEntity_getRotation(_activeModelID);
				Vec3 size	  = _fe3d.gameEntity_getSize(_activeModelID);

				// Apply new model position / rotation / size
				if (_transformation == TransformationType::TRANSLATION)
				{
					_handleValueChanging("modelPropertiesMenu", "xPlus", "x", position.x, _movementChangingSpeed);
					_handleValueChanging("modelPropertiesMenu", "xMinus", "x", position.x, -_movementChangingSpeed);
					_handleValueChanging("modelPropertiesMenu", "yPlus", "y", position.y, _movementChangingSpeed);
					_handleValueChanging("modelPropertiesMenu", "yMinus", "y", position.y, -_movementChangingSpeed);
					_handleValueChanging("modelPropertiesMenu", "zPlus", "z", position.z, _movementChangingSpeed);
					_handleValueChanging("modelPropertiesMenu", "zMinus", "z", position.z, -_movementChangingSpeed);
					_fe3d.gameEntity_setPosition(_activeModelID, position);
				}
				else if (_transformation == TransformationType::ROTATION)
				{
					_handleValueChanging("modelPropertiesMenu", "xPlus", "x", rotation.x, _movementChangingSpeed * 2.0f);
					_handleValueChanging("modelPropertiesMenu", "xMinus", "x", rotation.x, -_movementChangingSpeed * 2.0f);
					_handleValueChanging("modelPropertiesMenu", "yPlus", "y", rotation.y, _movementChangingSpeed * 2.0f);
					_handleValueChanging("modelPropertiesMenu", "yMinus", "y", rotation.y, -_movementChangingSpeed * 2.0f);
					_handleValueChanging("modelPropertiesMenu", "zPlus", "z", rotation.z, _movementChangingSpeed * 2.0f);
					_handleValueChanging("modelPropertiesMenu", "zMinus", "z", rotation.z, -_movementChangingSpeed * 2.0f);
					rotation.x = std::fmodf(rotation.x, 360.0f);
					rotation.y = std::fmodf(rotation.y, 360.0f);
					rotation.z = std::fmodf(rotation.z, 360.0f);
					_fe3d.gameEntity_setRotation(_activeModelID, rotation);
				}
				else if (_transformation == TransformationType::SCALING)
				{
					// Model size
					Vec3 oldSize = size;
					float factor = 25.0f;
					_handleValueChanging("modelPropertiesMenu", "xPlus", "x", size.x, _movementChangingSpeed, factor);
					_handleValueChanging("modelPropertiesMenu", "xMinus", "x", size.x, -_movementChangingSpeed, factor);
					_handleValueChanging("modelPropertiesMenu", "yPlus", "y", size.y, _movementChangingSpeed, factor);
					_handleValueChanging("modelPropertiesMenu", "yMinus", "y", size.y, -_movementChangingSpeed, factor);
					_handleValueChanging("modelPropertiesMenu", "zPlus", "z", size.z, _movementChangingSpeed, factor);
					_handleValueChanging("modelPropertiesMenu", "zMinus", "z", size.z, -_movementChangingSpeed, factor);
					_fe3d.gameEntity_setSize(_activeModelID, size);
				}
			}

			// Check if model is still selected or active
			string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelName")->getEntityID();
			if (_selectedModelID == "" && _activeModelID == "")
			{
				_fe3d.textEntity_hide(textEntityID);
			}
			else
			{
				if (_selectedBillboardID == "" && _activeBillboardID == "" &&
					_selectedLightBulbID == "" && _activeLightBulbID == "" &&
					_selectedSpeakerID == "" && _activeSpeakerID == "")
				{
					_fe3d.textEntity_show(textEntityID);
				}
			}
		}
		else
		{
			if (_gui.getViewport("right")->getWindow("main")->getActiveScreen()->getID() != "main")
			{
				// Reset when user wants to place models again
				for (auto& entityID : _fe3d.gameEntity_getAllIDs())
				{
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
					_fe3d.gameEntity_setLightness(entityID, _fe3d.gameEntity_getOriginalLightness(entityID));
					_selectedModelLightnessMultiplier = 1;
					_activeModelID = "";
					_selectedModelID = "";
				}
			}
		}
	}
}