#include "scene_editor.hpp"

void SceneEditor::_updateBillboardEditing()
{
	if (_isLoaded)
	{
		// Reset selected billboard from last frame
		if (!_dontResetSelectedBillboard)
		{
			_selectedBillboardID = "";
		}
		else
		{
			_dontResetSelectedBillboard = false;
		}

		// User must not be in placement mode
		if (_currentPreviewModelName == "" && _currentPreviewBillboardName == "" && !_isPlacingPointlight && _currentPreviewAudioName == "")
		{
			// Check if user selected a billboard
			for (auto& entityID : _fe3d.billboardEntity_getAllIDs())
			{
				// Must not be preview entity
				if (entityID[0] != '@')
				{
					auto hoveredAabbID = _fe3d.collision_checkCursorInAny();
					bool hovered = (hoveredAabbID.size() >= entityID.size()) && (hoveredAabbID.substr(0, entityID.size()) == entityID);

					// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
					if (hovered && _fe3d.misc_isCursorInsideViewport() &&
						!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
					{
						// Select hovered billboard
						_selectBillboard(entityID);

						// Check if user clicked billboard
						if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
						{
							// Check if same billboard is clicked again
							if (_selectedBillboardID != _activeBillboardID)
							{
								_activateBillboard(_selectedBillboardID);
							}
						}
					}
					else
					{
						// Don't reset if billboard is active
						if (entityID != _activeBillboardID && _selectedBillboardID == "")
						{
							_fe3d.billboardEntity_setLightness(entityID, _fe3d.billboardEntity_getOriginalLightness(entityID));
						}
					}
				}
			}

			// Check if user made the active billboard inactive
			if (_selectedBillboardID == "" && _activeBillboardID != "" && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// LMB pressed
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_activeBillboardID = "";
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
				}
			}

			// Update billboard lightness blinking
			if (_selectedBillboardID != _activeBillboardID)
			{
				_updateBillboardBlinking(_selectedBillboardID, _selectedBillboardLightnessMultiplier);
			}
			_updateBillboardBlinking(_activeBillboardID, _activeBillboardLightnessMultiplier);

			// Update properties screen
			if (_activeBillboardID != "")
			{
				_gui.getViewport("right")->getWindow("main")->setActiveScreen("billboardPropertiesMenu");

				// GUI management (pressed)
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("translation")->isHovered()) // Translation button
					{
						_transformation = TransformationType::TRANSLATION;

						// Update buttons hoverability
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("translation")->setHoverable(false);
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("rotation")->setHoverable(true);
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("scaling")->setHoverable(true);
					}
					else if (_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("rotation")->isHovered()) // Rotation button
					{
						_transformation = TransformationType::ROTATION;

						// Update buttons hoverability
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("translation")->setHoverable(true);
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("rotation")->setHoverable(false);
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("scaling")->setHoverable(true);
					}
					else if (_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("scaling")->isHovered()) // Scaling button
					{
						_transformation = TransformationType::SCALING;

						// Update buttons hoverability
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("translation")->setHoverable(true);
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("rotation")->setHoverable(true);
						_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("scaling")->setHoverable(false);
					}
					else if (_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.billboardEntity_delete(_activeBillboardID);
						_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
						_activeBillboardID = "";
						return;
					}
				}

				// Get entity transformation
				Vec3 position = _fe3d.billboardEntity_getPosition(_activeBillboardID);
				Vec3 rotation = _fe3d.billboardEntity_getRotation(_activeBillboardID);
				Vec2 size = _fe3d.billboardEntity_getSize(_activeBillboardID);
				
				// Enabling all axes by default
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("xMinus")->setHoverable(true);
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("xPlus")->setHoverable(true);
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("x")->setHoverable(true);
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("yMinus")->setHoverable(true);
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("yPlus")->setHoverable(true);
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("y")->setHoverable(true);
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("zMinus")->setHoverable(true);
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("zPlus")->setHoverable(true);
				_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("z")->setHoverable(true);

				// Disabling Z axis for scaling operations on a billboard
				if (_transformation == TransformationType::SCALING)
				{
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("zMinus")->setHoverable(false);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("zPlus")->setHoverable(false);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("z")->setHoverable(false);
				}

				// Apply new billboard position / rotation / size
				if (_transformation == TransformationType::TRANSLATION)
				{
					// Handle GUI input
					_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", position.x, _movementChangingSpeed);
					_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", position.x, -_movementChangingSpeed);
					_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", position.y, _movementChangingSpeed);
					_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", position.y, -_movementChangingSpeed);
					_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", position.z, _movementChangingSpeed);
					_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", position.z, -_movementChangingSpeed);
					_fe3d.billboardEntity_setPosition(_activeBillboardID, position);
				}
				else if (_transformation == TransformationType::ROTATION)
				{
					// Only 1 rotation direction
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("xMinus")->setHoverable(rotation.z == 0.0f && rotation.y == 0.0f);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("xPlus")->setHoverable(rotation.z == 0.0f && rotation.y == 0.0f);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("x")->setHoverable(rotation.z == 0.0f && rotation.y == 0.0f);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("yMinus")->setHoverable(rotation.x == 0.0f && rotation.z == 0.0f);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("yPlus")->setHoverable(rotation.x == 0.0f && rotation.z == 0.0f);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("y")->setHoverable(rotation.x == 0.0f && rotation.z == 0.0f);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("zMinus")->setHoverable(rotation.x == 0.0f && rotation.y == 0.0f);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("zPlus")->setHoverable(rotation.x == 0.0f && rotation.y == 0.0f);
					_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("z")->setHoverable(rotation.x == 0.0f && rotation.y == 0.0f);

					// Handle GUI input
					_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", rotation.x, _movementChangingSpeed * 2.0f);
					_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", rotation.x, -_movementChangingSpeed * 2.0f);
					_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", rotation.y, _movementChangingSpeed * 2.0f);
					_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", rotation.y, -_movementChangingSpeed * 2.0f);
					_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", rotation.z, _movementChangingSpeed * 2.0f);
					_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", rotation.z, -_movementChangingSpeed * 2.0f);
					rotation.x = std::fmodf(rotation.x, 360.0f);
					rotation.y = std::fmodf(rotation.y, 360.0f);
					rotation.z = std::fmodf(rotation.z, 360.0f);
					_fe3d.billboardEntity_setRotation(_activeBillboardID, rotation);
				}
				else if (_transformation == TransformationType::SCALING)
				{
					// Handle GUI input
					Vec2 oldSize = size;
					float factor = 25.0f;
					_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", size.x, _movementChangingSpeed, factor);
					_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", size.x, -_movementChangingSpeed, factor);
					_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", size.y, _movementChangingSpeed, factor);
					_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", size.y, -_movementChangingSpeed, factor);
					_fe3d.billboardEntity_setSize(_activeBillboardID, size);
				}
			}

			// Check if billboard is still selected or active
			string textEntityID = _gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID();
			if (_selectedBillboardID == "" && _activeBillboardID == "")
			{
				_fe3d.textEntity_hide(textEntityID);
			}
			else
			{
				if (_selectedModelID == "" && _activeModelID == "" && 
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
				// Reset when user wants to place billboards again
				for (auto& entityID : _fe3d.billboardEntity_getAllIDs())
				{
					_gui.getViewport("right")->getWindow("main")->setActiveScreen("sceneEditorControls");
					_fe3d.billboardEntity_setLightness(entityID, _fe3d.billboardEntity_getOriginalLightness(entityID));
					_selectedBillboardLightnessMultiplier = 1;
					_activeBillboardID = "";
					_selectedBillboardID = "";
				}
			}
		}
	}
}