#include "world_editor.hpp"

void WorldEditor::_updateText3dEditing()
{
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	if(!_dontResetSelectedText3d)
	{
		_selectedTextId = "";
	}
	else
	{
		_dontResetSelectedText3d = false;
	}

	if(_currentTemplateModelId.empty() && _currentTemplateTextId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingReflection)
	{
		for(const auto& id : _fe3d->text3d_getIds())
		{
			if(id[0] != '@')
			{
				auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();
				bool isHovered = (hoveredAabbId.size() >= id.size()) && (hoveredAabbId.substr(0, id.size()) == id);

				if(isHovered && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					_selectText3d(id);

					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						if(_selectedTextId != _activeTextId)
						{
							_activateText3d(_selectedTextId);
						}
					}
				}
				else
				{
					if((id != _selectedTextId) && (id != _activeTextId))
					{
						_deselectText3d(id);
					}
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeTextId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedTextId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
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
				_fe3d->text3d_setFrozen(_activeTextId, !_fe3d->text3d_isFrozen(_activeTextId));
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
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
				_handleValueChanging("text3dPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_handleValueChanging("text3dPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / TEXT3D_POSITION_DIVIDER));
				_fe3d->text3d_setPosition(_activeTextId, position);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("text3dPropertiesMenu", "xPlus", "x", rotation.x, TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "xMinus", "x", rotation.x, -TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "yPlus", "y", rotation.y, TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "yMinus", "y", rotation.y, -TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "zPlus", "z", rotation.z, TEXT3D_ROTATION_SPEED);
				_handleValueChanging("text3dPropertiesMenu", "zMinus", "z", rotation.z, -TEXT3D_ROTATION_SPEED);
				_fe3d->text3d_setRotation(_activeTextId, rotation);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("text3dPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("text3dPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("text3dPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("text3dPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / TEXT3D_SIZE_DIVIDER), TEXT3D_SIZE_MULTIPLIER, 0.0f);
				_fe3d->text3d_setSize(_activeTextId, size);
			}

			screen->getButton("freeze")->changeTextContent(_fe3d->text3d_isFrozen(_activeTextId) ? "Unfreeze" : "Freeze");
		}
	}
}