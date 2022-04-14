#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateQuad3dEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingReflection)
	{
		if(!_dontResetSelectedQuad3d)
		{
			_selectedQuadId = "";
		}
		else
		{
			_dontResetSelectedQuad3d = false;
		}

		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		for(const auto & [quadId, templateId] : _loadedQuadIds)
		{
			const auto isHovered = (hoveredAabbId == quadId);

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
			{
				_selectQuad(quadId);

				if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
				{
					if(_selectedQuadId != _activeQuadId)
					{
						_activateQuad(_selectedQuadId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((quadId != _selectedQuadId) && (quadId != _activeQuadId))
				{
					_deselectQuad(quadId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeQuadId.empty())
				{
					if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && _selectedQuadId.empty()) || _fe3d->input_isMouseHeld(ButtonType::BUTTON_MIDDLE))
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
			auto currentAnimationIds = _fe3d->quad3d_getAnimationIds(_activeQuadId);

			rightWindow->setActiveScreen("quad3dPropertiesMenu");

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(false);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(false);
			}
			else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
			{
				_fe3d->quad3d_setFrozen(_activeQuadId, !_fe3d->quad3d_isFrozen(_activeQuadId));
			}
			else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("animation")->isHovered())
			{
				if(currentAnimationIds.empty())
				{
					auto ids = _animation2dEditor->getLoadedAnimationIds();
					for(auto & id : ids)
					{
						id = id.substr(1);
					}

					_gui->getOverlay()->openChoiceForm("selectAnimation", "Select Animation", fvec2(0.0f, 0.1f), ids);
				}
				else
				{
					_fe3d->quad3d_stopAnimation(_activeQuadId, currentAnimationIds[0]);

					_fe3d->quad3d_setUvMultiplier(_activeQuadId, fvec2(1.0f));
					_fe3d->quad3d_setUvOffset(_activeQuadId, fvec2(0.0f));
				}
			}
			else if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyType::KEY_DELETE))
			{
				if(!currentAnimationIds.empty())
				{
					_fe3d->quad3d_stopAnimation(_activeQuadId, currentAnimationIds[0]);
				}

				_fe3d->quad3d_delete(_activeQuadId);
				_loadedQuadIds.erase(_activeQuadId);
				_activeQuadId = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			if((_gui->getOverlay()->getChoiceFormId() == "selectAnimation") && _gui->getOverlay()->isChoiceFormConfirmed())
			{
				const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

				if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
				{
					if(!currentAnimationIds.empty())
					{
						_fe3d->quad3d_stopAnimation(_activeQuadId, currentAnimationIds[0]);
					}

					_fe3d->quad3d_startAnimation(_activeQuadId, ("@" + selectedOptionId), -1);
				}
			}

			auto position = _fe3d->quad3d_getPosition(_activeQuadId);
			auto rotation = _fe3d->quad3d_getRotation(_activeQuadId);
			auto size = _fe3d->quad3d_getSize(_activeQuadId);

			if(!screen->getButton("position")->isHoverable())
			{
				_handleInputBox("quad3dPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleInputBox("quad3dPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleInputBox("quad3dPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleInputBox("quad3dPropertiesMenu", "xMinus", "x", "xPlus", rotation.x, QUAD3D_ROTATION_SPEED, 1.0f, 0.0f, 360.0f);
				_handleInputBox("quad3dPropertiesMenu", "yMinus", "y", "yPlus", rotation.y, QUAD3D_ROTATION_SPEED, 1.0f, 0.0f, 360.0f);
				_handleInputBox("quad3dPropertiesMenu", "zMinus", "z", "zPlus", rotation.z, QUAD3D_ROTATION_SPEED, 1.0f, 0.0f, 360.0f);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleInputBox("quad3dPropertiesMenu", "xMinus", "x", "xPlus", size.x, (_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_handleInputBox("quad3dPropertiesMenu", "yMinus", "y", "yPlus", size.y, (_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
			}

			_fe3d->quad3d_setPosition(_activeQuadId, position);
			_fe3d->quad3d_setRotation(_activeQuadId, rotation);
			_fe3d->quad3d_setSize(_activeQuadId, size);

			screen->getInputBox("x")->setHoverable(true);
			screen->getInputBox("y")->setHoverable(true);
			screen->getInputBox("z")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("xMinus")->setHoverable(true);
			screen->getButton("yMinus")->setHoverable(true);
			screen->getButton("zMinus")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("xPlus")->setHoverable(true);
			screen->getButton("yPlus")->setHoverable(true);
			screen->getButton("zPlus")->setHoverable(screen->getButton("size")->isHoverable());

			screen->getButton("animation")->setTextContent(currentAnimationIds.empty() ? "Start Animation" : "Stop Animation");
			screen->getButton("freeze")->setTextContent(_fe3d->quad3d_isFrozen(_activeQuadId) ? "Unfreeze" : "Freeze");
		}
	}
}