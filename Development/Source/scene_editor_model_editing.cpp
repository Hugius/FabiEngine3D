#include "scene_editor.hpp"

void SceneEditor::_updateModelEditing()
{
	if (_isEditorLoaded)
	{
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
		if (_currentPreviewModelName == "" && _currentPreviewBillboardName == "" && !_isPlacingPointlight && _currentPreviewAudioName == "")
		{
			// Check which entity is selected
			auto hoveredID = _fe3d.collision_checkCursorInAny().first;

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
						// Don't reset if model is active or selected
						if (entityID != _activeModelID && entityID != _selectedModelID)
						{
							_fe3d.gameEntity_setLightness(entityID, _initialModelLightness[entityID]);
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
					rightWindow->setActiveScreen("sceneEditorControls");
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
				rightWindow->setActiveScreen("modelPropertiesMenu");

				// GUI management (pressed)
				if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if (rightWindow->getScreen("modelPropertiesMenu")->getButton("translation")->isHovered()) // Translation button
					{
						_transformation = TransformationType::TRANSLATION;

						// Update buttons hoverability
						rightWindow->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(false);
						rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
						rightWindow->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(true);
					}
					else if (rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->isHovered()) // Rotation button
					{
						_transformation = TransformationType::ROTATION;

						// Update buttons hoverability
						rightWindow->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(true);
						rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(false);
						rightWindow->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(true);
					}
					else if (rightWindow->getScreen("modelPropertiesMenu")->getButton("scaling")->isHovered()) // Scaling button
					{
						_transformation = TransformationType::SCALING;

						// Update buttons hoverability
						rightWindow->getScreen("modelPropertiesMenu")->getButton("translation")->setHoverable(true);
						rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
						rightWindow->getScreen("modelPropertiesMenu")->getButton("scaling")->setHoverable(false);
					}
					else if (rightWindow->getScreen("modelPropertiesMenu")->getButton("freeze")->isHovered()) // Freeze button
					{
						// Model
						_fe3d.gameEntity_setStaticToCamera(_activeModelID, !_fe3d.gameEntity_isStaticToCamera(_activeModelID));

						// AABB
						for (auto& aabbID : _fe3d.aabbEntity_getBoundIDs(_activeModelID, true, false))
						{
							_fe3d.aabbEntity_setRaycastResponsive(aabbID, !_fe3d.gameEntity_isStaticToCamera(_activeModelID));
							_fe3d.aabbEntity_setCollisionResponsive(aabbID, !_fe3d.gameEntity_isStaticToCamera(_activeModelID));
						}
					}
					else if (rightWindow->getScreen("modelPropertiesMenu")->getButton("delete")->isHovered()) // Delete button
					{
						_fe3d.gameEntity_delete(_activeModelID);
						rightWindow->setActiveScreen("sceneEditorControls");
						_activeModelID = "";
						return;
					}
					else if (rightWindow->getScreen("modelPropertiesMenu")->getButton("animation")->isHovered()) // Animation button
					{
						_gui.getGlobalScreen()->addChoiceForm("animations", "Select animation", Vec2(0.0f, 0.1f),
							_animationEditor.getLoadedAnimationIDs());
					}
				}

				// Check if an animation name is clicked
				auto lastAnimationID = _animationEditor.getPlayingAnimationNames(_activeModelID);
				string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("animations");
				if (selectedButtonID != "" && _fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					// Stop last playing animation
					if (!lastAnimationID.empty())
					{
						// Stop animation
						_animationEditor.stopAnimation(lastAnimationID.back(), _activeModelID);

						// Reset main transformation
						_fe3d.gameEntity_setPosition(_activeModelID, _initialModelPosition[_activeModelID]);
						_fe3d.gameEntity_setRotationOrigin(_activeModelID, Vec3(0.0f));
						_fe3d.gameEntity_setRotation(_activeModelID, _initialModelRotation[_activeModelID]);
						_fe3d.gameEntity_setSize(_activeModelID, _initialModelSize[_activeModelID]);

						// Reset part transformations
						for (auto& partName : _fe3d.gameEntity_getPartNames(_activeModelID))
						{
							// Only named parts
							if (!partName.empty())
							{
								_fe3d.gameEntity_setPosition(_activeModelID, Vec3(0.0f), partName);
								_fe3d.gameEntity_setRotationOrigin(_activeModelID, Vec3(0.0f), partName);
								_fe3d.gameEntity_setRotation(_activeModelID, Vec3(0.0f), partName);
								_fe3d.gameEntity_setSize(_activeModelID, Vec3(1.0f), partName);
							}
						}
					}

					// Start chosen animation
					_animationEditor.startAnimation(selectedButtonID, _activeModelID, -1);

					// Miscellaneous
					_gui.getGlobalScreen()->removeChoiceForm("animations");
				}
				else if (_gui.getGlobalScreen()->isChoiceFormCancelled("animations")) // Cancelled choosing
				{
					_gui.getGlobalScreen()->removeChoiceForm("animations");
				}

				// Update freeze button
				auto freezeID = rightWindow->getScreen("modelPropertiesMenu")->getButton("freeze")->getTextfield()->getEntityID();
				bool isFrozen = _fe3d.gameEntity_isStaticToCamera(_activeModelID);
				_fe3d.textEntity_setTextContent(freezeID, isFrozen ? "Unfreeze" : "Freeze");

				// Alternative way of deleting
				if (_fe3d.input_getKeyPressed(InputType::KEY_DELETE))
				{
					_fe3d.gameEntity_delete(_activeModelID);
					rightWindow->setActiveScreen("sceneEditorControls");
					_activeModelID = "";
					return;
				}

				// Get entity transformation
				Vec3 position = _fe3d.gameEntity_getPosition(_activeModelID);
				Vec3 rotation = _fe3d.gameEntity_getRotation(_activeModelID);
				Vec3 size = _fe3d.gameEntity_getSize(_activeModelID);
				Vec3 oldPosition = position;
				Vec3 oldRotation = rotation;
				Vec3 oldSize = size;

				// Apply new model position / rotation / size
				if (_transformation == TransformationType::TRANSLATION)
				{
					_handleValueChanging("modelPropertiesMenu", "xPlus", "x", position.x, _customEditorSpeed / 100.0f);
					_handleValueChanging("modelPropertiesMenu", "xMinus", "x", position.x, -_customEditorSpeed / 100.0f);
					_handleValueChanging("modelPropertiesMenu", "yPlus", "y", position.y, _customEditorSpeed / 100.0f);
					_handleValueChanging("modelPropertiesMenu", "yMinus", "y", position.y, -_customEditorSpeed / 100.0f);
					_handleValueChanging("modelPropertiesMenu", "zPlus", "z", position.z, _customEditorSpeed / 100.0f);
					_handleValueChanging("modelPropertiesMenu", "zMinus", "z", position.z, -_customEditorSpeed / 100.0f);
				}
				else if (_transformation == TransformationType::ROTATION)
				{
					_handleValueChanging("modelPropertiesMenu", "xPlus", "x", rotation.x, _customEditorSpeed / 50.0f);
					_handleValueChanging("modelPropertiesMenu", "xMinus", "x", rotation.x, -_customEditorSpeed / 50.0f);
					_handleValueChanging("modelPropertiesMenu", "yPlus", "y", rotation.y, _customEditorSpeed / 50.0f);
					_handleValueChanging("modelPropertiesMenu", "yMinus", "y", rotation.y, -_customEditorSpeed / 50.0f);
					_handleValueChanging("modelPropertiesMenu", "zPlus", "z", rotation.z, _customEditorSpeed / 50.0f);
					_handleValueChanging("modelPropertiesMenu", "zMinus", "z", rotation.z, -_customEditorSpeed / 50.0f);
				}
				else if (_transformation == TransformationType::SCALING)
				{
					const float factor = 100.0f;
					_handleValueChanging("modelPropertiesMenu", "xPlus", "x", size.x, _customEditorSpeed / 100.0f, factor);
					_handleValueChanging("modelPropertiesMenu", "xMinus", "x", size.x, -_customEditorSpeed / 100.0f, factor);
					_handleValueChanging("modelPropertiesMenu", "yPlus", "y", size.y, _customEditorSpeed / 100.0f, factor);
					_handleValueChanging("modelPropertiesMenu", "yMinus", "y", size.y, -_customEditorSpeed / 100.0f, factor);
					_handleValueChanging("modelPropertiesMenu", "zPlus", "z", size.z, _customEditorSpeed / 100.0f, factor);
					_handleValueChanging("modelPropertiesMenu", "zMinus", "z", size.z, -_customEditorSpeed / 100.0f, factor);
				}

				// Update transformations if changed
				if (position != oldPosition || rotation != oldRotation || size != oldSize)
				{
					// Check if animation is playing
					auto animationNames = _animationEditor.getPlayingAnimationNames(_activeModelID);
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
						_fe3d.gameEntity_setPosition(_activeModelID, _initialModelPosition[_activeModelID]);
						_fe3d.gameEntity_setRotationOrigin(_activeModelID, Vec3(0.0f));
						_fe3d.gameEntity_setRotation(_activeModelID, _initialModelRotation[_activeModelID]);
						_fe3d.gameEntity_setSize(_activeModelID, _initialModelSize[_activeModelID]);

						// Reset part transformations
						for (auto& partName : _fe3d.gameEntity_getPartNames(_activeModelID))
						{
							// Only named parts
							if (!partName.empty())
							{
								_fe3d.gameEntity_setPosition(_activeModelID, Vec3(0.0f), partName);
								_fe3d.gameEntity_setRotationOrigin(_activeModelID, Vec3(0.0f), partName);
								_fe3d.gameEntity_setRotation(_activeModelID, Vec3(0.0f), partName);
								_fe3d.gameEntity_setSize(_activeModelID, Vec3(1.0f), partName);
							}
						}

						// Start animation again
						_animationEditor.startAnimation(animationNames.front(), _activeModelID, -1);
					}
					else // No animation playing
					{
						// Update position
						_initialModelPosition[_activeModelID] = position;
						_fe3d.gameEntity_setPosition(_activeModelID, position);

						// Update rotation
						_initialModelRotation[_activeModelID] = rotation;
						_fe3d.gameEntity_setRotation(_activeModelID, rotation);

						// Update size
						_initialModelSize[_activeModelID] = size;
						_fe3d.gameEntity_setSize(_activeModelID, size);
					}
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
			if (rightWindow->getActiveScreen()->getID() != "main")
			{
				// Reset when user wants to place models again
				for (auto& entityID : _fe3d.gameEntity_getAllIDs())
				{
					// Check if not preview entity
					if (entityID[0] != '@')
					{
						rightWindow->setActiveScreen("sceneEditorControls");
						_fe3d.gameEntity_setLightness(entityID, _initialModelLightness[entityID]);
						_selectedModelLightnessMultiplier = 1;
						_activeModelID = "";
						_selectedModelID = "";
					}
				}
			}
		}
	}
}