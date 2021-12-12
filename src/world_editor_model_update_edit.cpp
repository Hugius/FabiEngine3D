#include "world_editor.hpp"

void WorldEditor::_updateModelEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// User must not be placing anything
	if(_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		// Reset selected model from last frame
		if(!_dontResetSelectedModel)
		{
			_selectedModelID = "";
		}
		else
		{
			_dontResetSelectedModel = false;
		}

		// Check which entity is selected
		auto hoveredID = _fe3d.raycast_checkCursorInAny().first;

		// Check if user selected a model
		for(const auto& ID : _fe3d.model_getAllIDs())
		{
			// Must not be preview entity
			if(ID[0] != '@')
			{
				bool hovered = (hoveredID.size() >= ID.size()) && (hoveredID.substr(0, ID.size()) == ID);

				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if(hovered && _fe3d.misc_isCursorInsideViewport() &&
				   !_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered model
					_selectModel(ID);

					// Check if user clicked model
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same model is not clicked again
						if(_selectedModelID != _activeModelID)
						{
							_activateModel(_selectedModelID);
						}
					}
				}
				else
				{
					// Unselect if necessary
					if((ID != _selectedModelID) && (ID != _activeModelID))
					{
						_unselectModel(ID);
					}
				}
			}
		}

		// Check if RMB not down
		if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if model is active
				if(_activeModelID != "")
				{
					// Check if active model cancelled
					if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedModelID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeModelID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		// Update model highlighting
		if(_selectedModelID != _activeModelID)
		{
			_updateModelHighlighting(_selectedModelID, _selectedModelHighlightDirection);
		}
		_updateModelHighlighting(_activeModelID, _activeModelHighlightDirection);

		// Update properties screen
		if(_activeModelID != "")
		{
			// Temporary values
			auto screen = rightWindow->getScreen("modelPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("modelPropertiesMenu");

			// Button management
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(false);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(true);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(false);
					screen->getButton("size")->setHoverable(true);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(false);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
				{
					_fe3d.model_setFrozen(_activeModelID, !_fe3d.model_isFrozen(_activeModelID));
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
				{
					_gui.getGlobalScreen()->createChoiceForm("animationList", "Select Animation", fvec2(0.0f, 0.1f), _meshAnimationEditor.getAllAnimationIDs());
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.model_delete(_activeModelID);
					rightWindow->setActiveScreen("main");
					_activeModelID = "";
					return;
				}
			}

			// Check if an animation ID is clicked
			auto lastAnimationID = _meshAnimationEditor.getStartedAnimationIDs(_activeModelID);
			string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("animationList");
			if(selectedButtonID != "" && _fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Stop last playing animation
				if(!lastAnimationID.empty())
				{
					// Stop animation
					_meshAnimationEditor.stopAnimation(lastAnimationID.back(), _activeModelID);

					// Reset main transformation
					_fe3d.model_setBasePosition(_activeModelID, _initialModelPosition[_activeModelID]);
					_fe3d.model_setBaseRotationOrigin(_activeModelID, fvec3(0.0f));
					_fe3d.model_setBaseRotation(_activeModelID, _initialModelRotation[_activeModelID]);
					_fe3d.model_setBaseSize(_activeModelID, _initialModelSize[_activeModelID]);

					// Reset part transformations
					for(const auto& partID : _fe3d.model_getPartIDs(_activeModelID))
					{
						// Only named parts
						if(!partID.empty())
						{
							_fe3d.model_setPartPosition(_activeModelID, partID, fvec3(0.0f));
							_fe3d.model_setPartRotationOrigin(_activeModelID, partID, fvec3(0.0f));
							_fe3d.model_setPartRotation(_activeModelID, partID, fvec3(0.0f));
							_fe3d.model_setPartSize(_activeModelID, partID, fvec3(1.0f));
						}
					}
				}

				// Start chosen animation
				_meshAnimationEditor.startAnimation(selectedButtonID, _activeModelID, -1);

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
			}
			else if(_gui.getGlobalScreen()->isChoiceFormCancelled("animationList")) // Cancelled choosing
			{
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
			}

			// Alternative way of deleting
			if(_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.model_delete(_activeModelID);
				rightWindow->setActiveScreen("main");
				_activeModelID = "";
				return;
			}

			// Get current transformation
			auto position = _fe3d.model_getBasePosition(_activeModelID);
			auto rotation = _fe3d.model_getBaseRotation(_activeModelID);
			auto size = _fe3d.model_getBaseSize(_activeModelID);
			auto oldPosition = position;
			auto oldRotation = rotation;
			auto oldSize = size;

			// Handle position, rotation, size
			if(!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", rotation.x, (_editorSpeed / 25.0f));
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", rotation.x, -(_editorSpeed / 25.0f));
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", rotation.y, (_editorSpeed / 25.0f));
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", rotation.y, -(_editorSpeed / 25.0f));
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", rotation.z, (_editorSpeed / 25.0f));
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", rotation.z, -(_editorSpeed / 25.0f));
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", size.z, (_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", size.z, -(_editorSpeed / 100.0f), MODEL_SIZE_MULTIPLIER, 0.0f);
			}

			// Update transformations if changed
			if((position != oldPosition) || (rotation != oldRotation) || (size != oldSize))
			{
				// Check if animation is playing
				auto animationIDs = _meshAnimationEditor.getStartedAnimationIDs(_activeModelID);
				if(!animationIDs.empty())
				{
					// Stop animation
					_meshAnimationEditor.stopAnimation(animationIDs[0], _activeModelID);

					// Save new initial position
					if(position != oldPosition)
					{
						_initialModelPosition[_activeModelID] = position;
					}

					// Save new initial rotation
					if(rotation != oldRotation)
					{
						_initialModelRotation[_activeModelID] = rotation;
					}

					// Save new initial size
					if(size != oldSize)
					{
						_initialModelSize[_activeModelID] = size;
					}

					// Set new transformations
					_fe3d.model_setBasePosition(_activeModelID, _initialModelPosition[_activeModelID]);
					_fe3d.model_setBaseRotationOrigin(_activeModelID, fvec3(0.0f));
					_fe3d.model_setBaseRotation(_activeModelID, _initialModelRotation[_activeModelID]);
					_fe3d.model_setBaseSize(_activeModelID, _initialModelSize[_activeModelID]);

					// Reset part transformations
					for(const auto& partID : _fe3d.model_getPartIDs(_activeModelID))
					{
						// Only named parts
						if(!partID.empty())
						{
							_fe3d.model_setPartPosition(_activeModelID, partID, fvec3(0.0f));
							_fe3d.model_setPartRotationOrigin(_activeModelID, partID, fvec3(0.0f));
							_fe3d.model_setPartRotation(_activeModelID, partID, fvec3(0.0f));
							_fe3d.model_setPartSize(_activeModelID, partID, fvec3(1.0f));
						}
					}

					// Start animation again
					_meshAnimationEditor.startAnimation(animationIDs[0], _activeModelID, -1);
				}
				else // No animation playing
				{
					// Update position
					_initialModelPosition[_activeModelID] = position;
					_fe3d.model_setBasePosition(_activeModelID, position);

					// Update rotation
					_initialModelRotation[_activeModelID] = rotation;
					_fe3d.model_setBaseRotation(_activeModelID, rotation);

					// Update size
					_initialModelSize[_activeModelID] = size;
					_fe3d.model_setBaseSize(_activeModelID, size);
				}
			}

			// Update button text contents
			screen->getButton("freeze")->changeTextContent(_fe3d.model_isFrozen(_activeModelID) ? "Unfreeze" : "Freeze");
		}

		// Check if model is still selected or active
		if(_selectedModelID.empty() && _activeModelID.empty())
		{
			_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), false);
		}
	}
}