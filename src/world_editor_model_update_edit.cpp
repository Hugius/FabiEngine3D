#include "world_editor.hpp"

void WorldEditor::_updateModelEditing()
{
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	if(_currentTemplateModelID.empty() && _currentTemplateBillboardID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedModel)
		{
			_selectedModelID = "";
		}
		else
		{
			_dontResetSelectedModel = false;
		}

		auto hoveredID = _fe3d->raycast_checkCursorInAny().first;

		for(const auto& ID : _fe3d->model_getIDs())
		{
			if(ID[0] != '@')
			{
				bool hovered = (hoveredID.size() >= ID.size()) && (hoveredID.substr(0, ID.size()) == ID);

				if(hovered && _fe3d->misc_isCursorInsideViewport() &&
				   !_gui.getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectModel(ID);

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedModelID != _activeModelID)
						{
							_activateModel(_selectedModelID);
						}
					}
				}
				else
				{
					if((ID != _selectedModelID) && (ID != _activeModelID))
					{
						_unselectModel(ID);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui.getOverlay()->isFocused())
			{
				if(!_activeModelID.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedModelID.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeModelID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedModelID != _activeModelID)
		{
			_updateModelHighlighting(_selectedModelID, _selectedModelHighlightDirection);
		}
		_updateModelHighlighting(_activeModelID, _activeModelHighlightDirection);

		if(!_activeModelID.empty())
		{
			auto screen = rightWindow->getScreen("modelPropertiesMenu");

			rightWindow->setActiveScreen("modelPropertiesMenu");

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					screen->getButton("position")->setHoverable(false);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(true);
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(false);
					screen->getButton("size")->setHoverable(true);
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
				{
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(false);
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
				{
					_fe3d->model_setFrozen(_activeModelID, !_fe3d->model_isFrozen(_activeModelID));
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
				{
					_gui.getOverlay()->createChoiceForm("animationList", "Select Animation", fvec2(0.0f, 0.1f), _animation3dEditor.getAnimationIDs());
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->model_delete(_activeModelID);
					rightWindow->setActiveScreen("main");
					_activeModelID = "";
					return;
				}
			}

			auto lastAnimationID = _animation3dEditor.getStartedModelAnimationIDs(_activeModelID);
			auto selectedButtonID = _gui.getOverlay()->checkChoiceForm("animationList");
			if(!selectedButtonID.empty() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(!lastAnimationID.empty())
				{
					_animation3dEditor.stopModelAnimation(lastAnimationID.back(), _activeModelID);

					_fe3d->model_setBasePosition(_activeModelID, _initialModelPosition[_activeModelID]);
					_fe3d->model_setBaseRotationOrigin(_activeModelID, fvec3(0.0f));
					_fe3d->model_setBaseRotation(_activeModelID, _initialModelRotation[_activeModelID]);
					_fe3d->model_setBaseSize(_activeModelID, _initialModelSize[_activeModelID]);

					for(const auto& partID : _fe3d->model_getPartIDs(_activeModelID))
					{
						if(!partID.empty())
						{
							_fe3d->model_setPartPosition(_activeModelID, partID, fvec3(0.0f));
							_fe3d->model_setPartRotationOrigin(_activeModelID, partID, fvec3(0.0f));
							_fe3d->model_setPartRotation(_activeModelID, partID, fvec3(0.0f));
							_fe3d->model_setPartSize(_activeModelID, partID, fvec3(1.0f));
						}
					}
				}

				_animation3dEditor.startModelAnimation(selectedButtonID, _activeModelID, -1);

				_gui.getOverlay()->deleteChoiceForm("animationList");
			}
			else if(_gui.getOverlay()->isChoiceFormCancelled("animationList"))
			{
				_gui.getOverlay()->deleteChoiceForm("animationList");
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeModelID);
				rightWindow->setActiveScreen("main");
				_activeModelID = "";
				return;
			}

			auto position = _fe3d->model_getBasePosition(_activeModelID);
			auto rotation = _fe3d->model_getBaseRotation(_activeModelID);
			auto size = _fe3d->model_getBaseSize(_activeModelID);
			auto oldPosition = position;
			auto oldRotation = rotation;
			auto oldSize = size;

			if(!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / MODEL_POSITION_DIVIDER));
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", rotation.x, MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", rotation.x, -MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", rotation.y, MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", rotation.y, -MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", rotation.z, MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", rotation.z, -MODEL_ROTATION_SPEED);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", size.z, (_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", size.z, -(_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
			}

			if((position != oldPosition) || (rotation != oldRotation) || (size != oldSize))
			{
				auto animationIDs = _animation3dEditor.getStartedModelAnimationIDs(_activeModelID);
				if(!animationIDs.empty())
				{
					_animation3dEditor.stopModelAnimation(animationIDs[0], _activeModelID);

					if(position != oldPosition)
					{
						_initialModelPosition[_activeModelID] = position;
					}

					if(rotation != oldRotation)
					{
						_initialModelRotation[_activeModelID] = rotation;
					}

					if(size != oldSize)
					{
						_initialModelSize[_activeModelID] = size;
					}

					_fe3d->model_setBasePosition(_activeModelID, _initialModelPosition[_activeModelID]);
					_fe3d->model_setBaseRotationOrigin(_activeModelID, fvec3(0.0f));
					_fe3d->model_setBaseRotation(_activeModelID, _initialModelRotation[_activeModelID]);
					_fe3d->model_setBaseSize(_activeModelID, _initialModelSize[_activeModelID]);

					for(const auto& partID : _fe3d->model_getPartIDs(_activeModelID))
					{
						if(!partID.empty())
						{
							_fe3d->model_setPartPosition(_activeModelID, partID, fvec3(0.0f));
							_fe3d->model_setPartRotationOrigin(_activeModelID, partID, fvec3(0.0f));
							_fe3d->model_setPartRotation(_activeModelID, partID, fvec3(0.0f));
							_fe3d->model_setPartSize(_activeModelID, partID, fvec3(1.0f));
						}
					}

					_animation3dEditor.startModelAnimation(animationIDs[0], _activeModelID, -1);
				}
				else
				{
					_initialModelPosition[_activeModelID] = position;
					_fe3d->model_setBasePosition(_activeModelID, position);

					_initialModelRotation[_activeModelID] = rotation;
					_fe3d->model_setBaseRotation(_activeModelID, rotation);

					_initialModelSize[_activeModelID] = size;
					_fe3d->model_setBaseSize(_activeModelID, size);
				}
			}

			screen->getButton("freeze")->changeTextContent(_fe3d->model_isFrozen(_activeModelID) ? "Unfreeze" : "Freeze");
		}

		if(_selectedModelID.empty() && _activeModelID.empty())
		{
			_fe3d->text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), false);
		}
	}
}