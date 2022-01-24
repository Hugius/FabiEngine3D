#include "world_editor.hpp"

void WorldEditor::_updateQuad3dEditing()
{
	auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(!_dontResetSelectedQuad3d)
	{
		_selectedQuadID = "";
	}
	else
	{
		_dontResetSelectedQuad3d = false;
	}

	if(_currentTemplateModelID.empty() && _currentTemplateQuadID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingReflection)
	{
		for(const auto& ID : _fe3d->quad3d_getIDs())
		{
			if(ID[0] != '@')
			{
				auto hoveredAabbID = _fe3d->raycast_checkCursorInAny().first;
				bool hovered = (hoveredAabbID.size() >= ID.size()) && (hoveredAabbID.substr(0, ID.size()) == ID);

				if(hovered && _fe3d->misc_isCursorInsideViewport() &&
				   !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectQuad3d(ID);

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedQuadID != _activeQuadID)
						{
							_activateQuad3d(_selectedQuadID);
						}
					}
				}
				else
				{
					if((ID != _selectedQuadID) && (ID != _activeQuadID))
					{
						_unselectQuad3d(ID);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeQuadID.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedQuadID.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeQuadID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedQuadID.empty())
		{
			_updateQuad3dHighlighting(_activeQuadID, _activeQuad3dHighlightDirection);
		}
		else
		{
			_updateQuad3dHighlighting(_selectedQuadID, _selectedQuad3dHighlightDirection);
		}

		if(!_activeQuadID.empty())
		{
			auto screen = rightWindow->getScreen("quad3dPropertiesMenu");

			rightWindow->setActiveScreen("quad3dPropertiesMenu");

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
					_fe3d->quad3d_setFrozen(_activeQuadID, !_fe3d->quad3d_isFrozen(_activeQuadID));
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
				{
					_gui->getOverlay()->createChoiceForm("animationList", "Select Animation", fvec2(0.0f, 0.1f), _animation2dEditor->getAnimationIDs());
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->quad3d_delete(_activeQuadID);
					_loadedQuadIDs.erase(_activeQuadID);
					_activeQuadID = "";
					rightWindow->setActiveScreen("main");
					return;
				}
			}

			auto lastAnimationID = _animation2dEditor->getStartedQuad3dAnimationIDs(_activeQuadID);
			auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("animationList");
			if(!selectedButtonID.empty() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(!lastAnimationID.empty())
				{
					_animation2dEditor->stopQuad3dAnimation(lastAnimationID.back(), _activeQuadID);
				}

				_animation2dEditor->startQuad3dAnimation(selectedButtonID, _activeQuadID, -1);

				_gui->getOverlay()->deleteChoiceForm("animationList");
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("animationList"))
			{
				_gui->getOverlay()->deleteChoiceForm("animationList");
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->quad3d_delete(_activeQuadID);
				_loadedQuadIDs.erase(_activeQuadID);
				_activeQuadID = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->quad3d_getPosition(_activeQuadID);
			auto rotation = _fe3d->quad3d_getRotation(_activeQuadID);
			auto size = _fe3d->quad3d_getSize(_activeQuadID);

			screen->getButton("xMinus")->setHoverable(true);
			screen->getButton("xPlus")->setHoverable(true);
			screen->getWriteField("x")->setHoverable(true);
			screen->getButton("yMinus")->setHoverable(true);
			screen->getButton("yPlus")->setHoverable(true);
			screen->getWriteField("y")->setHoverable(true);
			screen->getButton("zMinus")->setHoverable(true);
			screen->getButton("zPlus")->setHoverable(true);
			screen->getWriteField("z")->setHoverable(true);

			if(!screen->getButton("size")->isHoverable())
			{
				screen->getButton("zMinus")->setHoverable(false);
				screen->getButton("zPlus")->setHoverable(false);
				screen->getWriteField("z")->setHoverable(false);
			}

			if(!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("quad3dPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_handleValueChanging("quad3dPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / QUAD3D_POSITION_DIVIDER));
				_fe3d->quad3d_setPosition(_activeQuadID, position);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("quad3dPropertiesMenu", "xPlus", "x", rotation.x, QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "xMinus", "x", rotation.x, -QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "yPlus", "y", rotation.y, QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "yMinus", "y", rotation.y, -QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "zPlus", "z", rotation.z, QUAD3D_ROTATION_SPEED);
				_handleValueChanging("quad3dPropertiesMenu", "zMinus", "z", rotation.z, -QUAD3D_ROTATION_SPEED);
				_fe3d->quad3d_setRotation(_activeQuadID, rotation);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("quad3dPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("quad3dPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("quad3dPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("quad3dPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / QUAD3D_SIZE_DIVIDER), QUAD3D_SIZE_MULTIPLIER, 0.0f);
				_fe3d->quad3d_setSize(_activeQuadID, size);
			}

			screen->getButton("freeze")->changeTextContent(_fe3d->quad3d_isFrozen(_activeQuadID) ? "Unfreeze" : "Freeze");
		}

		if(_selectedQuadID.empty() && _activeQuadID.empty())
		{
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), false);
		}
	}
}