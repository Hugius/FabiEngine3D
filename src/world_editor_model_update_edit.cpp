#include "world_editor.hpp"

void WorldEditor::_updateModelEditing()
{
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedModel)
		{
			_selectedModelId = "";
		}
		else
		{
			_dontResetSelectedModel = false;
		}

		auto hoveredId = _fe3d->raycast_getClosestAabbId();

		for(const auto& id : _fe3d->model_getIds())
		{
			if(id[0] != '@')
			{
				bool isHovered = (hoveredId.size() >= id.size()) && (hoveredId.substr(0, id.size()) == id);

				if(isHovered && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectModel(id);

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedModelId != _activeModelId)
						{
							_activateModel(_selectedModelId);
						}
					}
				}
				else
				{
					if((id != _selectedModelId) && (id != _activeModelId))
					{
						_unselectModel(id);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeModelId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedModelId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeModelId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedModelId.empty())
		{
			_updateModelHighlighting(_activeModelId, _activeModelHighlightDirection);
		}
		else
		{
			_updateModelHighlighting(_selectedModelId, _selectedModelHighlightDirection);
		}

		if(!_activeModelId.empty())
		{
			auto screen = rightWindow->getScreen("modelPropertiesMenu");

			rightWindow->setActiveScreen("modelPropertiesMenu");

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
				_fe3d->model_setFrozen(_activeModelId, !_fe3d->model_isFrozen(_activeModelId));
			}
			else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
			{
				_gui->getOverlay()->createChoiceForm("animationList", "Select Animation", fvec2(0.0f, 0.1f), _animation3dEditor->getAnimationIds());
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->model_delete(_activeModelId);
				_loadedModelIds.erase(_activeModelId);
				rightWindow->setActiveScreen("main");
				_activeModelId = "";
				return;
			}

			auto lastAnimationId = _animation3dEditor->getStartedModelAnimationIds(_activeModelId);
			auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("animationList");
			if(!selectedButtonId.empty())
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if(!lastAnimationId.empty())
					{
						_animation3dEditor->stopModelAnimation(lastAnimationId.back(), _activeModelId);

						_fe3d->model_setBasePosition(_activeModelId, _initialModelPosition.at(_activeModelId));
						_fe3d->model_setBaseRotationOrigin(_activeModelId, fvec3(0.0f));
						_fe3d->model_setBaseRotation(_activeModelId, _initialModelRotation.at(_activeModelId));
						_fe3d->model_setBaseSize(_activeModelId, _initialModelSize.at(_activeModelId));

						for(const auto& partId : _fe3d->model_getPartIds(_activeModelId))
						{
							if(!partId.empty())
							{
								_fe3d->model_setPartPosition(_activeModelId, partId, fvec3(0.0f));
								_fe3d->model_setPartRotationOrigin(_activeModelId, partId, fvec3(0.0f));
								_fe3d->model_setPartRotation(_activeModelId, partId, fvec3(0.0f));
								_fe3d->model_setPartSize(_activeModelId, partId, fvec3(1.0f));
							}
						}
					}

					_animation3dEditor->startModelAnimation(selectedButtonId, _activeModelId, -1);

					_gui->getOverlay()->deleteChoiceForm("animationList");
				}
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("animationList"))
			{
				_gui->getOverlay()->deleteChoiceForm("animationList");
			}

			auto position = _fe3d->model_getBasePosition(_activeModelId);
			auto rotation = _fe3d->model_getBaseRotation(_activeModelId);
			auto size = _fe3d->model_getBaseSize(_activeModelId);
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
				auto animationIds = _animation3dEditor->getStartedModelAnimationIds(_activeModelId);
				if(!animationIds.empty())
				{
					_animation3dEditor->stopModelAnimation(animationIds[0], _activeModelId);

					if(position != oldPosition)
					{
						_initialModelPosition.at(_activeModelId) = position;
					}

					if(rotation != oldRotation)
					{
						_initialModelRotation.at(_activeModelId) = rotation;
					}

					if(size != oldSize)
					{
						_initialModelSize.at(_activeModelId) = size;
					}

					_fe3d->model_setBasePosition(_activeModelId, _initialModelPosition.at(_activeModelId));
					_fe3d->model_setBaseRotationOrigin(_activeModelId, fvec3(0.0f));
					_fe3d->model_setBaseRotation(_activeModelId, _initialModelRotation.at(_activeModelId));
					_fe3d->model_setBaseSize(_activeModelId, _initialModelSize.at(_activeModelId));

					for(const auto& partId : _fe3d->model_getPartIds(_activeModelId))
					{
						if(!partId.empty())
						{
							_fe3d->model_setPartPosition(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartRotationOrigin(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartRotation(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartSize(_activeModelId, partId, fvec3(1.0f));
						}
					}

					_animation3dEditor->startModelAnimation(animationIds[0], _activeModelId, -1);
				}
				else
				{
					_initialModelPosition.at(_activeModelId) = position;
					_fe3d->model_setBasePosition(_activeModelId, position);

					_initialModelRotation.at(_activeModelId) = rotation;
					_fe3d->model_setBaseRotation(_activeModelId, rotation);

					_initialModelSize.at(_activeModelId) = size;
					_fe3d->model_setBaseSize(_activeModelId, size);
				}
			}

			screen->getButton("freeze")->changeTextContent(_fe3d->model_isFrozen(_activeModelId) ? "Unfreeze" : "Freeze");
		}

		if(_selectedModelId.empty() && _activeModelId.empty())
		{
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), false);
		}
	}
}