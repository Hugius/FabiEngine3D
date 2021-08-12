#include "scene_editor.hpp"

#define SELECTED_BILLBOARD_ID _selectedBillboardID
#define ACTIVE_BILLBOARD_ID _activeBillboardID

void SceneEditor::_updateBillboardEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected billboard from last frame
	if (!_dontResetSelectedBillboard)
	{
		SELECTED_BILLBOARD_ID = "";
	}
	else
	{
		_dontResetSelectedBillboard = false;
	}

	// User must not be in placement mode
	if (_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && !_isPlacingLight && _currentPreviewSoundID.empty())
	{
		// Check if user selected a billboard
		for (const auto& entityID : _fe3d.billboardEntity_getAllIDs())
		{
			// Must not be preview entity
			if (entityID[0] != '@')
			{
				// Check which entity is selected
				auto hoveredAabbID = _fe3d.collision_checkCursorInAny().first;
				bool hovered = (hoveredAabbID.size() >= entityID.size()) && (hoveredAabbID.substr(0, entityID.size()) == entityID);

				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if (hovered && _fe3d.misc_isCursorInsideViewport() &&
					!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered billboard
					_selectBillboard(entityID);

					// Check if user clicked billboard
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same billboard is clicked again
						if (SELECTED_BILLBOARD_ID != ACTIVE_BILLBOARD_ID)
						{
							_activateBillboard(SELECTED_BILLBOARD_ID);
						}
					}
				}
				else
				{
					// Don't reset inversion if billboard is active or selected
					if (entityID != ACTIVE_BILLBOARD_ID && entityID != SELECTED_BILLBOARD_ID)
					{
						_fe3d.billboardEntity_setInversion(entityID, 0.0f);
					}
				}
			}
		}

		// Check if user made the active billboard inactive
		if (SELECTED_BILLBOARD_ID.empty() && ACTIVE_BILLBOARD_ID != "" && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				ACTIVE_BILLBOARD_ID = "";
				rightWindow->setActiveScreen("sceneEditorControls");
			}
		}

		// Update billboard blinking
		if (SELECTED_BILLBOARD_ID != ACTIVE_BILLBOARD_ID)
		{
			_updateBillboardBlinking(SELECTED_BILLBOARD_ID, _selectedBillboardInversionDirection);
		}
		_updateBillboardBlinking(ACTIVE_BILLBOARD_ID, _activeBillboardInversionDirection);

		// Update properties screen
		if (ACTIVE_BILLBOARD_ID != "")
		{
			// Temporary values
			auto screen = rightWindow->getScreen("billboardPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("billboardPropertiesMenu");

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("position")->isHovered()) // Position button
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(true);
				}
				else if (screen->getButton("rotation")->isHovered()) // Rotation button
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(false);
					screen->getButton("size")->setHoverable(true);
				}
				else if (screen->getButton("size")->isHovered()) // Size button
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(false);
				}
				else if (screen->getButton("delete")->isHovered()) // Delete button
				{
					_fe3d.billboardEntity_delete(ACTIVE_BILLBOARD_ID);
					rightWindow->setActiveScreen("sceneEditorControls");
					ACTIVE_BILLBOARD_ID = "";
					return;
				}
			}

			// Get entity transformation
			Vec3 position = _fe3d.billboardEntity_getPosition(ACTIVE_BILLBOARD_ID);
			Vec3 rotation = _fe3d.billboardEntity_getRotation(ACTIVE_BILLBOARD_ID);
			Vec2 size = _fe3d.billboardEntity_getSize(ACTIVE_BILLBOARD_ID);

			// Enabling all axes by default
			screen->getButton("xMinus")->setHoverable(true);
			screen->getButton("xPlus")->setHoverable(true);
			screen->getWritefield("x")->setHoverable(true);
			screen->getButton("yMinus")->setHoverable(true);
			screen->getButton("yPlus")->setHoverable(true);
			screen->getWritefield("y")->setHoverable(true);
			screen->getButton("zMinus")->setHoverable(true);
			screen->getButton("zPlus")->setHoverable(true);
			screen->getWritefield("z")->setHoverable(true);

			// Disabling Z axis for scaling operations on a billboard
			if (!screen->getButton("size")->isHoverable())
			{
				screen->getButton("zMinus")->setHoverable(false);
				screen->getButton("zPlus")->setHoverable(false);
				screen->getWritefield("z")->setHoverable(false);
			}

			// Apply position, rotationm, size
			if (!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
				_fe3d.billboardEntity_setPosition(ACTIVE_BILLBOARD_ID, position);
			}
			else if (!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", rotation.x, (_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", rotation.x, -(_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", rotation.y, (_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", rotation.y, -(_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", rotation.z, (_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", rotation.z, -(_editorSpeed / 50.0f));
				_fe3d.billboardEntity_setRotation(ACTIVE_BILLBOARD_ID, rotation);
			}
			else if (!screen->getButton("size")->isHoverable())
			{
				Vec2 oldSize = size;
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_fe3d.billboardEntity_setSize(ACTIVE_BILLBOARD_ID, size);
			}
		}

		// Check if billboard is still selected or active
		if (SELECTED_BILLBOARD_ID.empty() && ACTIVE_BILLBOARD_ID.empty())
		{
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("billboardID")->getEntityID(), false);
		}
		else
		{
			if (_selectedModelID.empty() && _activeModelID.empty() &&
				_selectedLampID.empty() && _activeLampID.empty() &&
				_selectedSpeakerID.empty() && _activeSpeakerID.empty())
			{
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("billboardID")->getEntityID(), true);
			}
		}
	}
	else
	{
		if (rightWindow->getActiveScreen()->getID() != "main")
		{
			// Reset when user wants to place billboards again
			for (const auto& entityID : _fe3d.billboardEntity_getAllIDs())
			{
				// Check if not preview entity
				if (entityID[0] != '@')
				{
					rightWindow->setActiveScreen("sceneEditorControls");
					_selectedBillboardInversionDirection = 1;
					ACTIVE_BILLBOARD_ID = "";
					SELECTED_BILLBOARD_ID = "";
				}
			}
		}
	}
}