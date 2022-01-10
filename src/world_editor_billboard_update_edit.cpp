#include "world_editor.hpp"

void WorldEditor::_updateBillboardEditing()
{
	auto rightWindow = _gui->getViewport("right")->getWindow("main");

	if(!_dontResetSelectedBillboard)
	{
		_selectedBillboardID = "";
	}
	else
	{
		_dontResetSelectedBillboard = false;
	}

	if(_currentTemplateModelID.empty() && _currentTemplateBillboardID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingReflection)
	{
		for(const auto& ID : _fe3d->billboard_getIDs())
		{
			if(ID[0] != '@')
			{
				auto hoveredAabbID = _fe3d->raycast_checkCursorInAny().first;
				bool hovered = (hoveredAabbID.size() >= ID.size()) && (hoveredAabbID.substr(0, ID.size()) == ID);

				if(hovered && _fe3d->misc_isCursorInsideViewport() &&
				   !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectBillboard(ID);

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedBillboardID != _activeBillboardID)
						{
							_activateBillboard(_selectedBillboardID);
						}
					}
				}
				else
				{
					if((ID != _selectedBillboardID) && (ID != _activeBillboardID))
					{
						_unselectBillboard(ID);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeBillboardID.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedBillboardID.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeBillboardID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedBillboardID != _activeBillboardID)
		{
			_updateBillboardHighlighting(_selectedBillboardID, _selectedBillboardHighlightDirection);
		}
		_updateBillboardHighlighting(_activeBillboardID, _activeBillboardHighlightDirection);

		if(!_activeBillboardID.empty())
		{
			auto screen = rightWindow->getScreen("billboardPropertiesMenu");

			rightWindow->setActiveScreen("billboardPropertiesMenu");

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
					_fe3d->billboard_setFrozen(_activeBillboardID, !_fe3d->billboard_isFrozen(_activeBillboardID));
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
				{
					_gui->getOverlay()->createChoiceForm("animationList", "Select Animation", fvec2(0.0f, 0.1f), _animation2dEditor->getAnimationIDs());
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->billboard_delete(_activeBillboardID);
					rightWindow->setActiveScreen("main");
					_activeBillboardID = "";
					return;
				}
			}

			auto lastAnimationID = _animation2dEditor->getStartedBillboardAnimationIDs(_activeBillboardID);
			auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("animationList");
			if(!selectedButtonID.empty() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(!lastAnimationID.empty())
				{
					_animation2dEditor->stopBillboardAnimation(lastAnimationID.back(), _activeBillboardID);
				}

				_animation2dEditor->startBillboardAnimation(selectedButtonID, _activeBillboardID, -1);

				_gui->getOverlay()->deleteChoiceForm("animationList");
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled("animationList"))
			{
				_gui->getOverlay()->deleteChoiceForm("animationList");
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->billboard_delete(_activeBillboardID);
				rightWindow->setActiveScreen("main");
				_activeBillboardID = "";
				return;
			}

			auto position = _fe3d->billboard_getPosition(_activeBillboardID);
			auto rotation = _fe3d->billboard_getRotation(_activeBillboardID);
			auto size = _fe3d->billboard_getSize(_activeBillboardID);

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
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / BILLBOARD_POSITION_DIVIDER));
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / BILLBOARD_POSITION_DIVIDER));
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / BILLBOARD_POSITION_DIVIDER));
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / BILLBOARD_POSITION_DIVIDER));
				_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / BILLBOARD_POSITION_DIVIDER));
				_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / BILLBOARD_POSITION_DIVIDER));
				_fe3d->billboard_setPosition(_activeBillboardID, position);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", rotation.x, BILLBOARD_ROTATION_SPEED);
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", rotation.x, -BILLBOARD_ROTATION_SPEED);
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", rotation.y, BILLBOARD_ROTATION_SPEED);
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", rotation.y, -BILLBOARD_ROTATION_SPEED);
				_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", rotation.z, BILLBOARD_ROTATION_SPEED);
				_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", rotation.z, -BILLBOARD_ROTATION_SPEED);
				_fe3d->billboard_setRotation(_activeBillboardID, rotation);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / BILLBOARD_SIZE_DIVIDER), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / BILLBOARD_SIZE_DIVIDER), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / BILLBOARD_SIZE_DIVIDER), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / BILLBOARD_SIZE_DIVIDER), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_fe3d->billboard_setSize(_activeBillboardID, size);
			}

			screen->getButton("freeze")->changeTextContent(_fe3d->billboard_isFrozen(_activeBillboardID) ? "Unfreeze" : "Freeze");
		}

		if(_selectedBillboardID.empty() && _activeBillboardID.empty())
		{
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("billboardID")->getEntityID(), false);
		}
	}
}