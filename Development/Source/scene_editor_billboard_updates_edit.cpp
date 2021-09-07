#include "scene_editor.hpp"

void SceneEditor::_updateBillboardEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

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
	if (_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingLight)
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
						// Check if same billboard is not clicked again
						if (_selectedBillboardID != _activeBillboardID)
						{
							_activateBillboard(_selectedBillboardID);
						}
					}
				}
				else
				{
					// Don't reset if billboard is active or selected
					if ((entityID != _activeBillboardID) && (entityID != _selectedBillboardID))
					{
						_fe3d.billboardEntity_setInversion(entityID, 0.0f);
					}
				}
			}
		}

		// Check if user made the active billboard inactive
		if (_selectedBillboardID.empty() && _activeBillboardID != "" && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_activeBillboardID = "";
				rightWindow->setActiveScreen("sceneEditorControls");
			}
		}

		// Update billboard blinking
		if (_selectedBillboardID != _activeBillboardID)
		{
			_updateBillboardBlinking(_selectedBillboardID, _selectedBillboardInversionDirection);
		}
		_updateBillboardBlinking(_activeBillboardID, _activeBillboardInversionDirection);

		// Update properties screen
		if (_activeBillboardID != "")
		{
			// Temporary values
			auto screen = rightWindow->getScreen("billboardPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("billboardPropertiesMenu");

			// Button management
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(true);
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(false);
					screen->getButton("size")->setHoverable(true);
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(false);
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.billboardEntity_delete(_activeBillboardID);
					rightWindow->setActiveScreen("sceneEditorControls");
					_activeBillboardID = "";
					return;
				}
			}

			// Alternative way of deleting
			if (_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.billboardEntity_delete(_activeBillboardID);
				rightWindow->setActiveScreen("sceneEditorControls");
				_activeBillboardID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.billboardEntity_getPosition(_activeBillboardID);
			auto rotation = _fe3d.billboardEntity_getRotation(_activeBillboardID);
			auto size = _fe3d.billboardEntity_getSize(_activeBillboardID);

			// Enabling all axes by default
			screen->getButton("xMinus")->setHoverable(true);
			screen->getButton("xPlus")->setHoverable(true);
			screen->getWriteField("x")->setHoverable(true);
			screen->getButton("yMinus")->setHoverable(true);
			screen->getButton("yPlus")->setHoverable(true);
			screen->getWriteField("y")->setHoverable(true);
			screen->getButton("zMinus")->setHoverable(true);
			screen->getButton("zPlus")->setHoverable(true);
			screen->getWriteField("z")->setHoverable(true);

			// Disabling Z axis for scaling operations on a billboard
			if (!screen->getButton("size")->isHoverable())
			{
				screen->getButton("zMinus")->setHoverable(false);
				screen->getButton("zPlus")->setHoverable(false);
				screen->getWriteField("z")->setHoverable(false);
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
				_fe3d.billboardEntity_setPosition(_activeBillboardID, position);
			}
			else if (!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", rotation.x, (_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", rotation.x, -(_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", rotation.y, (_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", rotation.y, -(_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", rotation.z, (_editorSpeed / 50.0f));
				_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", rotation.z, -(_editorSpeed / 50.0f));
				_fe3d.billboardEntity_setRotation(_activeBillboardID, rotation);
			}
			else if (!screen->getButton("size")->isHoverable())
			{
				Vec2 oldSize = size;
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_fe3d.billboardEntity_setSize(_activeBillboardID, size);
			}
		}

		// Check if billboard is still selected or active
		if (_selectedBillboardID.empty() && _activeBillboardID.empty())
		{
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
		}
		else
		{
			if (_selectedModelID.empty() && _activeModelID.empty() &&
				_selectedLampID.empty() && _activeLampID.empty() &&
				_selectedSpeakerID.empty() && _activeSpeakerID.empty())
			{
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
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
					_activeBillboardID = "";
					_selectedBillboardID = "";
				}
			}
		}
	}
}