#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateText3dEditing()
{
	if(_currentTemplateModelId.empty() &&
	   _currentTemplateQuad3dId.empty() &&
	   _currentTemplateText3dId.empty() &&
	   _currentTemplateAabbId.empty() &&
	   _currentTemplatePointlightId.empty() &&
	   _currentTemplateSpotlightId.empty() &&
	   _currentTemplateSound3dId.empty() &&
	   !_isPlacingCaptor)
	{
		const auto window = _gui->getLeftViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedText3d)
		{
			_selectedText3dId = "";
		}
		else
		{
			_dontResetSelectedText3d = false;
		}

		for(const auto & [placedText3dId, templateText3dId] : _loadedText3dIds)
		{
			const auto isHovered = (hoveredAabbId == placedText3dId);

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectText3d(placedText3dId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedText3dId != _activeText3dId)
					{
						_activateText3d(_selectedText3dId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
			}
			else
			{
				if((placedText3dId != _selectedText3dId) && (placedText3dId != _activeText3dId))
				{
					_deselectText3d(placedText3dId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeText3dId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedText3dId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						window->setActiveScreen("empty");

						_activeText3dId = "";
					}
				}
			}
		}

		if(!_activeText3dId.empty())
		{
			const auto screen = window->getScreen("text3dPropertiesMenu");

			window->setActiveScreen("text3dPropertiesMenu");

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
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("content")->isHovered())
			{
				_gui->getOverlay()->openValueForm("content", "Content", "", VALUE_FORM_POSITION, 10, true, true, true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
			{
				_fe3d->text3d_setFrozen(_activeText3dId, !_fe3d->text3d_isFrozen(_activeText3dId));
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->text3d_delete(_activeText3dId);

				window->setActiveScreen("empty");

				_loadedText3dIds.erase(_activeText3dId);

				_activeText3dId = "";

				return;
			}

			if((_gui->getOverlay()->getValueFormId() == "content") && _gui->getOverlay()->isValueFormConfirmed())
			{
				_fe3d->text3d_setContent(_activeText3dId, _gui->getOverlay()->getValueFormContent());
			}

			auto position = _fe3d->text3d_getPosition(_activeText3dId);
			auto rotation = _fe3d->text3d_getRotation(_activeText3dId);
			auto size = _fe3d->text3d_getSize(_activeText3dId);

			if(!screen->getButton("position")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / TEXT3D_POSITION_SPEED_DIVIDER));
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / TEXT3D_POSITION_SPEED_DIVIDER));
				_handleInputBox("text3dPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / TEXT3D_POSITION_SPEED_DIVIDER));
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", rotation.x, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", rotation.y, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
				_handleInputBox("text3dPropertiesMenu", "zMinus", "z", "zPlus", rotation.z, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", size.x, (_editorSpeed / TEXT3D_SIZE_SPEED_DIVIDER), TEXT3D_SIZE_FACTOR, 0.0f);
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", size.y, (_editorSpeed / TEXT3D_SIZE_SPEED_DIVIDER), TEXT3D_SIZE_FACTOR, 0.0f);
			}

			_fe3d->text3d_setPosition(_activeText3dId, position);
			_fe3d->text3d_setRotation(_activeText3dId, rotation);
			_fe3d->text3d_setSize(_activeText3dId, size);

			screen->getInputBox("z")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("zMinus")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("zPlus")->setHoverable(screen->getButton("size")->isHoverable());
			screen->getButton("freeze")->setTextContent(_fe3d->text3d_isFrozen(_activeText3dId) ? "Unfreeze" : "Freeze");
		}
	}
}