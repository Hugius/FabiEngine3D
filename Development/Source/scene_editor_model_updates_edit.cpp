#include "scene_editor.hpp"

#define SELECTED_MODEL_ID _selectedModelID
#define ACTIVE_MODEL_ID _activeModelID

void SceneEditor::_updateModelEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected model from last frame
	if (!_dontResetSelectedModel)
	{
		SELECTED_MODEL_ID = "";
	}
	else
	{
		_dontResetSelectedModel = false;
	}

	// User must not be in placement mode
	if (_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && !_isPlacingLight && _currentPreviewSoundID.empty())
	{
		// Check which entity is selected
		auto hoveredID = _fe3d.collision_checkCursorInAny().first;

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
						// Check if same model is clicked again
						if (SELECTED_MODEL_ID != ACTIVE_MODEL_ID)
						{
							_activateModel(SELECTED_MODEL_ID);
						}
					}
				}
				else
				{
					// Don't reset inversion if model is active or selected
					if ((entityID != ACTIVE_MODEL_ID) && (entityID != SELECTED_MODEL_ID))
					{
						_fe3d.modelEntity_setInversion(entityID, 0.0f);
					}
				}
			}
		}

		// Check if user made the active model inactive
		if ((SELECTED_MODEL_ID.empty()) && (ACTIVE_MODEL_ID != "") && _fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
		{
			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				ACTIVE_MODEL_ID = "";
				rightWindow->setActiveScreen("sceneEditorControls");
			}
		}

		// Update model blinking
		if (SELECTED_MODEL_ID != ACTIVE_MODEL_ID)
		{
			_updateModelBlinking(SELECTED_MODEL_ID, _selectedModelInversionDirection);
		}
		_updateModelBlinking(ACTIVE_MODEL_ID, _activeModelInversionDirection);

		// Update properties screen
		if (ACTIVE_MODEL_ID != "")
		{
			// Temporary values
			auto screen = rightWindow->getScreen("modelPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("modelPropertiesMenu");

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("position")->isHovered()) // Position button
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(false);
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
				else if (screen->getButton("freeze")->isHovered()) // Freeze button
				{
					// Model
					_fe3d.modelEntity_setStaticToCamera(ACTIVE_MODEL_ID, !_fe3d.modelEntity_isStaticToCamera(ACTIVE_MODEL_ID));

					// AABB
					for (const auto& aabbID : _fe3d.aabbEntity_getBoundIDs(ACTIVE_MODEL_ID, true, false))
					{
						_fe3d.aabbEntity_setRaycastResponsive(aabbID, !_fe3d.modelEntity_isStaticToCamera(ACTIVE_MODEL_ID));
						_fe3d.aabbEntity_setCollisionResponsive(aabbID, !_fe3d.modelEntity_isStaticToCamera(ACTIVE_MODEL_ID));
					}
				}
				else if (screen->getButton("animation")->isHovered()) // Animation button
				{
					_gui.getGlobalScreen()->createChoiceForm("animationList", "Choose Animation", Vec2(0.0f, 0.1f),
						_animationEditor.getAllAnimationIDs());
				}
				else if (screen->getButton("delete")->isHovered()) // Delete button
				{
					_fe3d.modelEntity_delete(ACTIVE_MODEL_ID);
					rightWindow->setActiveScreen("sceneEditorControls");
					ACTIVE_MODEL_ID = "";
					return;
				}
			}

			// Check if an animation ID is clicked
			auto lastAnimationID = _animationEditor.getStartedAnimationIDs(ACTIVE_MODEL_ID);
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("animationList");
			if (selectedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Stop last playing animation
				if (!lastAnimationID.empty())
				{
					// Stop animation
					_animationEditor.stopAnimation(lastAnimationID.back(), ACTIVE_MODEL_ID);

					// Reset main transformation
					_fe3d.modelEntity_setPosition(ACTIVE_MODEL_ID, _initialModelPosition[ACTIVE_MODEL_ID]);
					_fe3d.modelEntity_setRotationOrigin(ACTIVE_MODEL_ID, Vec3(0.0f));
					_fe3d.modelEntity_setRotation(ACTIVE_MODEL_ID, _initialModelRotation[ACTIVE_MODEL_ID]);
					_fe3d.modelEntity_setSize(ACTIVE_MODEL_ID, _initialModelSize[ACTIVE_MODEL_ID]);

					// Reset part transformations
					for (const auto& partID : _fe3d.modelEntity_getPartIDs(ACTIVE_MODEL_ID))
					{
						// Only named parts
						if (!partID.empty())
						{
							_fe3d.modelEntity_setPosition(ACTIVE_MODEL_ID, Vec3(0.0f), partID);
							_fe3d.modelEntity_setRotationOrigin(ACTIVE_MODEL_ID, Vec3(0.0f), partID);
							_fe3d.modelEntity_setRotation(ACTIVE_MODEL_ID, Vec3(0.0f), partID);
							_fe3d.modelEntity_setSize(ACTIVE_MODEL_ID, Vec3(1.0f), partID);
						}
					}
				}

				// Start chosen animation
				_animationEditor.startAnimation(selectedButtonID, ACTIVE_MODEL_ID, -1);

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("animationList")) // Cancelled choosing
			{
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
			}

			// Button text contents
			bool isFrozen = _fe3d.modelEntity_isStaticToCamera(ACTIVE_MODEL_ID);
			screen->getButton("freeze")->changeTextContent(isFrozen ? "Unfreeze" : "Freeze");

			// Alternative way of deleting
			if (_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.modelEntity_delete(ACTIVE_MODEL_ID);
				rightWindow->setActiveScreen("sceneEditorControls");
				ACTIVE_MODEL_ID = "";
				return;
			}

			// Get entity transformation
			Vec3 position = _fe3d.modelEntity_getPosition(ACTIVE_MODEL_ID);
			Vec3 rotation = _fe3d.modelEntity_getRotation(ACTIVE_MODEL_ID);
			Vec3 size = _fe3d.modelEntity_getSize(ACTIVE_MODEL_ID);
			Vec3 oldPosition = position;
			Vec3 oldRotation = rotation;
			Vec3 oldSize = size;

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
				auto animationNames = _animationEditor.getStartedAnimationIDs(ACTIVE_MODEL_ID);
				if (!animationNames.empty())
				{
					// Stop animation
					_animationEditor.stopAnimation(animationNames.front(), ACTIVE_MODEL_ID);

					// Save new initial position
					if (position != oldPosition)
					{
						_initialModelPosition[ACTIVE_MODEL_ID] = position;
					}

					// Save new initial rotation
					if (rotation != oldRotation)
					{
						_initialModelRotation[ACTIVE_MODEL_ID] = rotation;
					}

					// Save new initial size
					if (size != oldSize)
					{
						_initialModelSize[ACTIVE_MODEL_ID] = size;
					}

					// Set new transformations
					_fe3d.modelEntity_setPosition(ACTIVE_MODEL_ID, _initialModelPosition[ACTIVE_MODEL_ID]);
					_fe3d.modelEntity_setRotationOrigin(ACTIVE_MODEL_ID, Vec3(0.0f));
					_fe3d.modelEntity_setRotation(ACTIVE_MODEL_ID, _initialModelRotation[ACTIVE_MODEL_ID]);
					_fe3d.modelEntity_setSize(ACTIVE_MODEL_ID, _initialModelSize[ACTIVE_MODEL_ID]);

					// Reset part transformations
					for (const auto& partID : _fe3d.modelEntity_getPartIDs(ACTIVE_MODEL_ID))
					{
						// Only named parts
						if (!partID.empty())
						{
							_fe3d.modelEntity_setPosition(ACTIVE_MODEL_ID, Vec3(0.0f), partID);
							_fe3d.modelEntity_setRotationOrigin(ACTIVE_MODEL_ID, Vec3(0.0f), partID);
							_fe3d.modelEntity_setRotation(ACTIVE_MODEL_ID, Vec3(0.0f), partID);
							_fe3d.modelEntity_setSize(ACTIVE_MODEL_ID, Vec3(1.0f), partID);
						}
					}

					// Start animation again
					_animationEditor.startAnimation(animationNames.front(), ACTIVE_MODEL_ID, -1);
				}
				else // No animation playing
				{
					// Update position
					_initialModelPosition[ACTIVE_MODEL_ID] = position;
					_fe3d.modelEntity_setPosition(ACTIVE_MODEL_ID, position);

					// Update rotation
					_initialModelRotation[ACTIVE_MODEL_ID] = rotation;
					_fe3d.modelEntity_setRotation(ACTIVE_MODEL_ID, rotation);

					// Update size
					_initialModelSize[ACTIVE_MODEL_ID] = size;
					_fe3d.modelEntity_setSize(ACTIVE_MODEL_ID, size);
				}
			}
		}

		// Check if model is still selected or active
		auto textEntityID = _gui.getGlobalScreen()->getTextfield("modelID")->getEntityID();
		if (SELECTED_MODEL_ID.empty() && ACTIVE_MODEL_ID.empty())
		{
			_fe3d.textEntity_setVisible(textEntityID, false);
		}
		else
		{
			if (_selectedBillboardID.empty() && _activeBillboardID.empty() &&
				_selectedLampID.empty() && _activeLampID.empty() &&
				_selectedSpeakerID.empty() && _activeSpeakerID.empty())
			{
				_fe3d.textEntity_setVisible(textEntityID, true);
			}
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
					ACTIVE_MODEL_ID = "";
					SELECTED_MODEL_ID = "";
				}
			}
		}
	}
}