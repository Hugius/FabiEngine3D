#include "world_editor.hpp"

void WorldEditor::_updateText3dEditing()
{
	auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(!_dontResetSelectedText3d)
	{
		_selectedTextID = "";
	}
	else
	{
		_dontResetSelectedText3d = false;
	}

	if(_currentTemplateModelID.empty() && _currentTemplateTextID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingReflection)
	{
		for(const auto& ID : _fe3d->text3d_getIDs())
		{
			if(ID[0] != '@')
			{
				auto hoveredAabbID = _fe3d->raycast_checkCursorInAny().first;
				bool hovered = (hoveredAabbID.size() >= ID.size()) && (hoveredAabbID.substr(0, ID.size()) == ID);

				if(hovered && _fe3d->misc_isCursorInsideViewport() &&
				   !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectText3d(ID);

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedTextID != _activeTextID)
						{
							_activateText3d(_selectedTextID);
						}
					}
				}
				else
				{
					if((ID != _selectedTextID) && (ID != _activeTextID))
					{
						_unselectText3d(ID);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideViewport() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeTextID.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedTextID.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeTextID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedTextID != _activeTextID)
		{
			_updateText3dHighlighting(_selectedTextID, _selectedText3dHighlightDirection);
		}
		_updateText3dHighlighting(_activeTextID, _activeText3dHighlightDirection);

		if(!_activeTextID.empty())
		{
			auto screen = rightWindow->getScreen("text3dPropertiesMenu");

			rightWindow->setActiveScreen("text3dPropertiesMenu");

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
					_fe3d->text3d_setFrozen(_activeTextID, !_fe3d->text3d_isFrozen(_activeTextID));
				}
				else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d->text3d_delete(_activeTextID);
					_loadedTextIDs.erase(_activeTextID);
					_activeTextID = "";
					rightWindow->setActiveScreen("main");
					return;
				}
			}

			if(_fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d->text3d_delete(_activeTextID);
				_loadedTextIDs.erase(_activeTextID);
				_activeTextID = "";
				rightWindow->setActiveScreen("main");
				return;
			}

			auto position = _fe3d->text3d_getPosition(_activeTextID);
			auto rotation = _fe3d->text3d_getRotation(_activeTextID);
			auto size = _fe3d->text3d_getSize(_activeTextID);

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
				_handleValueChanging("text3dPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_fe3d->text3d_setPosition(_activeTextID, position);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("text3dPropertiesMenu", "xPlus", "x", rotation.x, TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "xMinus", "x", rotation.x, -TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "yPlus", "y", rotation.y, TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "yMinus", "y", rotation.y, -TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "zPlus", "z", rotation.z, TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "zMinus", "z", rotation.z, -TEXT3D_ROTATION_SPEED);
				_fe3d->text3d_setRotation(_activeTextID, rotation);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("text3dPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("text3dPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("text3dPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("text3dPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_fe3d->text3d_setSize(_activeTextID, size);
			}

			screen->getButton("freeze")->changeTextContent(_fe3d->text3d_isFrozen(_activeTextID) ? "Unfreeze" : "Freeze");
		}

		if(_selectedTextID.empty() && _activeTextID.empty())
		{
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), false);
		}
	}
}