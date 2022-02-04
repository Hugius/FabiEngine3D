#include "world_editor.hpp"

void WorldEditor::_updateQuad3dEditing()
{
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(!_dontResetSelectedQuad3d)
	{
		_selectedQuadId = "";
	}
	else
	{
		_dontResetSelectedQuad3d = false;
	}

	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingReflection)
	{
		for(const auto& id : _fe3d->quad3d_getIds())
		{
			if(id[0] != '@')
			{
				auto hoveredAabbId = _fe3d->raycast_checkCursorInAny().first;
				bool hovered = (hoveredAabbId.size() >= id.size()) && (hoveredAabbId.substr(0, id.size()) == id);

				if(hovered && _fe3d->misc_isCursorInsideViewport() &&
				   !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectQuad3d(id);

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedQuadId != _activeQuadId)
						{
							_activateQuad3d(_selectedQuadId);
						}
					}
				}
				else
				{
					if((id != _selectedQuadId) && (id != _activeQuadId))
					{
						_unselectQuad3d(id);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeQuadId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedQuadId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeQuadId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedQuadId.empty())
		{
			_updateQuad3dHighlighting(_activeQuadId, _activeQuad3dHighlightDirection);
		}
		else
		{
			_updateQuad3dHighlighting(_selectedQuadId, _selectedQuad3dHighlightDirection);
		}

		if(!_activeQuadId.empty())
		{
			auto screen = rightWindow->getScreen("quad3dPropertiesMenu");

			rightWindow->setActiveScreen("quad3dPropertiesMenu");

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
				_fe3d->quad3d_setFrozen(_activeQuadId, !_fe3d->quad3d_isFrozen(_activeQuadId));
			}
			else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
			{
				_gui->getOverlay()->createChoiceForm("animationList", "Select Animation", fvec2(0.0f, 0.1f), _animation2dEditor->getAnimationIds());
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->quad3d_delete(_activeQuadId);
				_loadedQuadIds.erase(_activeQuadId);
				_activeQuadId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto lastAnimationId = _animation2dEditor->getStartedQuad3dAnimationIds(_activeQuadId);
			auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("animationList");
			if(!selectedButtonId.empty() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(!lastAnimationId.empty())
				{
					_animation2dEditor->stopQuad3dAnimation(lastAnimationId.back(), _activeQuadId);
				}

				_animation2dEditor->startQuad3dAnimation(selectedButtonId, _activeQuadId, -1);

				_gui->getOverlay()->deleteChoiceForm("animationList");
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("animationList"))
			{
				_gui->getOverlay()->deleteChoiceForm("animationList");
			}

			auto position = _fe3d->quad3d_getPosition(_activeQuadId);
			auto rotation = _fe3d->quad3d_getRotation(_activeQuadId);
			auto size = _fe3d->quad3d_getSize(_activeQuadId);

			screen->getButton("xMinus")->setHoverable(true);
			screen->getButton("xPlus")->setHoverable(true);
			screen->getInputField("x")->setHoverable(true);
			screen->getButton("yMinus")->setHoverable(true);
			screen->getButton("yPlus")->setHoverable(true);
			screen->getInputField("y")->setHoverable(true);
			screen->getButton("zMinus")->setHoverable(true);
			screen->getButton("zPlus")->setHoverable(true);
			screen->getInputField("z")->setHoverable(true);

			if(!screen->getButton("size")->isHoverable())
			{
				screen->getButton("zMinus")->setHoverable(false);
				screen->getButton("zPlus")->setHoverable(false);
				screen->getInputField("z")->setHoverable(false);
			}

			if(!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("quad3dPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_fe3d->quad3d_setPosition(_activeQuadId, position);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("quad3dPropertiesMenu", "xPlus", "x", rotation.x, QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "xMinus", "x", rotation.x, -QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "yPlus", "y", rotation.y, QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "yMinus", "y", rotation.y, -QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "zPlus", "z", rotation.z, QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "zMinus", "z", rotation.z, -QUAD3D_ROTATION_SPEED);
				_fe3d->quad3d_setRotation(_activeQuadId, rotation);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("quad3dPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("quad3dPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("quad3dPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("quad3dPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_fe3d->quad3d_setSize(_activeQuadId, size);
			}

			screen->getButton("freeze")->changeTextContent(_fe3d->quad3d_isFrozen(_activeQuadId) ? "Unfreeze" : "Freeze");
		}

		if(_selectedQuadId.empty() && _activeQuadId.empty())
		{
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
		}
	}
}