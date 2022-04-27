#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateText3dEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateTextId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingCaptor)
	{
		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedText3d)
		{
			_selectedTextId = "";
		}
		else
		{
			_dontResetSelectedText3d = false;
		}

		for(const auto & [textId, templateId] : _loadedTextIds)
		{
			const auto isHovered = (hoveredAabbId == textId);

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectText(textId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedTextId != _activeTextId)
					{
						_activateText(_selectedTextId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((textId != _selectedTextId) && (textId != _activeTextId))
				{
					_deselectText(textId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeTextId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedTextId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						_activeTextId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedTextId.empty())
		{
			_updateText3dHighlighting(_activeTextId, _activeText3dHighlightDirection);
		}
		else
		{
			_updateText3dHighlighting(_selectedTextId, _selectedText3dHighlightDirection);
		}

		if(!_activeTextId.empty())
		{
			auto screen = rightWindow->getScreen("text3dPropertiesMenu");

			rightWindow->setActiveScreen("text3dPropertiesMenu");

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(false);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(false);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
			{
				_fe3d->text3d_setFrozen(_activeTextId, !_fe3d->text3d_isFrozen(_activeTextId));
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->text3d_delete(_activeTextId);
				_loadedTextIds.erase(_activeTextId);
				_activeTextId = "";
				rightWindow->setActiveScreen("main");

				return;
			}

			auto position = _fe3d->text3d_getPosition(_activeTextId);
			auto rotation = _fe3d->text3d_getRotation(_activeTextId);
			auto size = _fe3d->text3d_getSize(_activeTextId);

			if(!screen->getButton("position")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleInputBox("text3dPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", rotation.x, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", rotation.y, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
				_handleInputBox("text3dPropertiesMenu", "zMinus", "z", "zPlus", rotation.z, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", size.x, (_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", size.y, (_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
			}

			_fe3d->text3d_setPosition(_activeTextId, position);
			_fe3d->text3d_setRotation(_activeTextId, rotation);
			_fe3d->text3d_setSize(_activeTextId, size);

			screen->getInputBox("x")->setHoverable(true);
			screen->getInputBox("y")->setHoverable(true);
			screen->getInputBox("z")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("xMinus")->setHoverable(true);
			screen->getButton("yMinus")->setHoverable(true);
			screen->getButton("zMinus")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("xPlus")->setHoverable(true);
			screen->getButton("yPlus")->setHoverable(true);
			screen->getButton("zPlus")->setHoverable(screen->getButton("size")->isHoverable());

			screen->getButton("freeze")->setTextContent(_fe3d->text3d_isFrozen(_activeTextId) ? "Unfreeze" : "Freeze");
		}
	}
}