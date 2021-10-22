#include "scene_editor.hpp"

void SceneEditor::_updateModelEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

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
	if (_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingPointlight && !_isPlacingReflection)
	{
		// Check which entity is selected
		auto hoveredID = _fe3d.raycast_checkCursorInAny().first;

		// Check if user selected a model
		for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
		{
			// Must not be preview entity
			if (entityID[0] != '@')
			{
				bool hovered = (hoveredID.size() >= entityID.size()) && (hoveredID.substr(0, entityID.size()) == entityID);

				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if (hovered && _fe3d.misc_isCursorInsideViewport() &&
					!_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered model
					_selectModel(entityID);

					// Check if user clicked model
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same model is not clicked again
						if (_selectedModelID != _activeModelID)
						{
							_activateModel(_selectedModelID);
						}
					}
				}
				else
				{
					// Don't reset if model is active or selected
					if ((entityID != _activeModelID) && (entityID != _selectedModelID))
					{
						// Reset all parts
						for (const auto& partID : _fe3d.modelEntity_getPartIDs(entityID))
						{
							_fe3d.modelEntity_setColorInversion(entityID, partID, 0.0f);
						}
					}
				}
			}
		}

		// Check if RMB not down
		if (!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if (_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if model is active
				if (_activeModelID != "")
				{
					// Check if active model cancelled
					if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedModelID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeModelID = "";
						rightWindow->setActiveScreen("sceneEditorControls");
					}
				}
			}
		}

		// Update model blinking
		if (_selectedModelID != _activeModelID)
		{
			_updateModelBlinking(_selectedModelID, _selectedModelInversionDirection);
		}
		_updateModelBlinking(_activeModelID, _activeModelInversionDirection);

		// Update properties screen
		if (_activeModelID != "")
		{
			// Temporary values
			auto screen = rightWindow->getScreen("modelPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("modelPropertiesMenu");

			// Button management
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(false);
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
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
				{
					// Freeze model
					_fe3d.modelEntity_setStaticToCamera(_activeModelID, !_fe3d.modelEntity_isStaticToCamera(_activeModelID));

					// Set AABBs responsiveness
					for (const auto& aabbID : _fe3d.aabbEntity_getChildIDs(_activeModelID, AabbParentType::MODEL_ENTITY))
					{
						_fe3d.aabbEntity_setRaycastResponsive(aabbID, !_fe3d.modelEntity_isStaticToCamera(_activeModelID));
						_fe3d.aabbEntity_setCollisionResponsive(aabbID, !_fe3d.modelEntity_isStaticToCamera(_activeModelID));
					}
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
				{
					_gui.getGlobalScreen()->createChoiceForm("animationList", "Select Animation", Vec2(0.0f, 0.1f),
						_animationEditor.getAllAnimationIDs());
				}
				else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.modelEntity_delete(_activeModelID);
					rightWindow->setActiveScreen("sceneEditorControls");
					_activeModelID = "";
					return;
				}
			}

			// Check if an animation ID is clicked
			auto lastAnimationID = _animationEditor.getStartedAnimationIDs(_activeModelID);
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("animationList");
			if (selectedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Stop last playing animation
				if (!lastAnimationID.empty())
				{
					// Stop animation
					_animationEditor.stopAnimation(lastAnimationID.back(), _activeModelID);

					// Reset main transformation
					_fe3d.modelEntity_setBasePosition(_activeModelID, _initialModelPosition[_activeModelID]);
					_fe3d.modelEntity_setBaseRotationOrigin(_activeModelID, Vec3(0.0f));
					_fe3d.modelEntity_setBaseRotation(_activeModelID, _initialModelRotation[_activeModelID]);
					_fe3d.modelEntity_setBaseSize(_activeModelID, _initialModelSize[_activeModelID]);

					// Reset part transformations
					for (const auto& partID : _fe3d.modelEntity_getPartIDs(_activeModelID))
					{
						// Only named parts
						if (!partID.empty())
						{
							_fe3d.modelEntity_setPartPosition(_activeModelID, partID, Vec3(0.0f));
							_fe3d.modelEntity_setPartRotationOrigin(_activeModelID, partID, Vec3(0.0f));
							_fe3d.modelEntity_setPartRotation(_activeModelID, partID, Vec3(0.0f));
							_fe3d.modelEntity_setPartSize(_activeModelID, partID, Vec3(1.0f));
						}
					}
				}

				// Start chosen animation
				_animationEditor.startAnimation(selectedButtonID, _activeModelID, -1);

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("animationList")) // Cancelled choosing
			{
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
			}

			// Alternative way of deleting
			if (_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.modelEntity_delete(_activeModelID);
				rightWindow->setActiveScreen("sceneEditorControls");
				_activeModelID = "";
				return;
			}

			// Get current transformation
			auto position = _fe3d.modelEntity_getBasePosition(_activeModelID);
			auto rotation = _fe3d.modelEntity_getBaseRotation(_activeModelID);
			auto size = _fe3d.modelEntity_getBaseSize(_activeModelID);
			auto oldPosition = position;
			auto oldRotation = rotation;
			auto oldSize = size;

			// Handle position, rotation, size
			if (!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
			}
			else if (!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", rotation.x, (_editorSpeed / 50.0f));
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", rotation.x, -(_editorSpeed / 50.0f));
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", rotation.y, (_editorSpeed / 50.0f));
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", rotation.y, -(_editorSpeed / 50.0f));
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", rotation.z, (_editorSpeed / 50.0f));
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", rotation.z, -(_editorSpeed / 50.0f));
			}
			else if (!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", size.z, (_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", size.z, -(_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
			}

			// Update transformations if changed
			if (position != oldPosition || rotation != oldRotation || size != oldSize)
			{
				// Check if animation is playing
				auto animationNames = _animationEditor.getStartedAnimationIDs(_activeModelID);
				if (!animationNames.empty())
				{
					// Stop animation
					_animationEditor.stopAnimation(animationNames.front(), _activeModelID);

					// Save new initial position
					if (position != oldPosition)
					{
						_initialModelPosition[_activeModelID] = position;
					}

					// Save new initial rotation
					if (rotation != oldRotation)
					{
						_initialModelRotation[_activeModelID] = rotation;
					}

					// Save new initial size
					if (size != oldSize)
					{
						_initialModelSize[_activeModelID] = size;
					}

					// Set new transformations
					_fe3d.modelEntity_setBasePosition(_activeModelID, _initialModelPosition[_activeModelID]);
					_fe3d.modelEntity_setBaseRotationOrigin(_activeModelID, Vec3(0.0f));
					_fe3d.modelEntity_setBaseRotation(_activeModelID, _initialModelRotation[_activeModelID]);
					_fe3d.modelEntity_setBaseSize(_activeModelID, _initialModelSize[_activeModelID]);

					// Reset part transformations
					for (const auto& partID : _fe3d.modelEntity_getPartIDs(_activeModelID))
					{
						// Only named parts
						if (!partID.empty())
						{
							_fe3d.modelEntity_setPartPosition(_activeModelID, partID, Vec3(0.0f));
							_fe3d.modelEntity_setPartRotationOrigin(_activeModelID, partID, Vec3(0.0f));
							_fe3d.modelEntity_setPartRotation(_activeModelID, partID, Vec3(0.0f));
							_fe3d.modelEntity_setPartSize(_activeModelID, partID, Vec3(1.0f));
						}
					}

					// Start animation again
					_animationEditor.startAnimation(animationNames.front(), _activeModelID, -1);
				}
				else // No animation playing
				{
					// Update position
					_initialModelPosition[_activeModelID] = position;
					_fe3d.modelEntity_setBasePosition(_activeModelID, position);

					// Update rotation
					_initialModelRotation[_activeModelID] = rotation;
					_fe3d.modelEntity_setBaseRotation(_activeModelID, rotation);

					// Update size
					_initialModelSize[_activeModelID] = size;
					_fe3d.modelEntity_setBaseSize(_activeModelID, size);
				}
			}

			// Update button text contents
			screen->getButton("freeze")->changeTextContent(_fe3d.modelEntity_isStaticToCamera(_activeModelID) ? "Unfreeze" : "Freeze");
		}

		// Check if model is still selected or active
		if (_selectedModelID.empty() && _activeModelID.empty())
		{
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), false);
		}
	}
	else
	{
		if (rightWindow->getActiveScreen()->getID() != "main")
		{
			// Reset when user wants to place models again
			for (const auto& entityID : _fe3d.modelEntity_getAllIDs())
			{
				// Check if not preview entity
				if (entityID[0] != '@')
				{
					rightWindow->setActiveScreen("sceneEditorControls");
					_selectedModelInversionDirection = 1;
					_activeModelID = "";
					_selectedModelID = "";
				}
			}
		}
	}
}