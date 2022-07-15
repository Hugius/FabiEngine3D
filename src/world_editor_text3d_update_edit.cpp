#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateText3dEditing()
{
	if(_currentEditorModelId.empty() &&
	   _currentEditorQuad3dId.empty() &&
	   _currentEditorText3dId.empty() &&
	   _currentEditorAabbId.empty() &&
	   _currentEditorPointlightId.empty() &&
	   _currentEditorSpotlightId.empty() &&
	   _currentEditorCaptorId.empty() &&
	   _currentEditorSound3dId.empty())
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

		for(const auto & text3dId : _loadedText3dIds)
		{
			const auto hasParent = (!hoveredAabbId.empty() && _fe3d->aabb_hasParent(hoveredAabbId) && (_fe3d->aabb_getParentType(hoveredAabbId) == AabbParentType::TEXT3D));
			const auto isHovered = (hasParent && (_fe3d->aabb_getParentId(hoveredAabbId) == text3dId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectText3d(text3dId);

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
				if((text3dId != _selectedText3dId) && (text3dId != _activeText3dId))
				{
					_deselectText3d(text3dId);
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
				screen->getButton("position")->setHoverable(false, true);
				screen->getButton("rotation")->setHoverable(true, true);
				screen->getButton("size")->setHoverable(true, true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
			{
				screen->getButton("position")->setHoverable(true, true);
				screen->getButton("rotation")->setHoverable(false, true);
				screen->getButton("size")->setHoverable(true, true);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
			{
				screen->getButton("position")->setHoverable(true, true);
				screen->getButton("rotation")->setHoverable(true, true);
				screen->getButton("size")->setHoverable(false, true);
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_duplicator->deleteCopiedText3d(_activeText3dId);

				window->setActiveScreen("empty");

				_loadedText3dIds.erase(remove(_loadedText3dIds.begin(), _loadedText3dIds.end(), _activeText3dId), _loadedText3dIds.end());

				_activeText3dId = "";

				return;
			}

			auto position = _fe3d->text3d_getPosition(_activeText3dId);
			auto rotation = _fe3d->text3d_getRotation(_activeText3dId);
			auto size = _fe3d->text3d_getSize(_activeText3dId);

			if(!screen->getButton("position")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / TEXT3D_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / TEXT3D_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
				_handleInputBox("text3dPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / TEXT3D_POSITION_SPEED_DIVIDER), 1.0f, -FLT_MAX, FLT_MAX);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", rotation.x, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", rotation.y, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
				_handleInputBox("text3dPropertiesMenu", "zMinus", "z", "zPlus", rotation.z, TEXT3D_ROTATION_SPEED, 1.0f, 0.0f, 359.0f);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleInputBox("text3dPropertiesMenu", "xMinus", "x", "xPlus", size.x, (_editorSpeed / TEXT3D_SIZE_SPEED_DIVIDER), TEXT3D_SIZE_FACTOR, 0.0f, FLT_MAX);
				_handleInputBox("text3dPropertiesMenu", "yMinus", "y", "yPlus", size.y, (_editorSpeed / TEXT3D_SIZE_SPEED_DIVIDER), TEXT3D_SIZE_FACTOR, 0.0f, FLT_MAX);
			}

			_fe3d->text3d_setPosition(_activeText3dId, position);
			_fe3d->text3d_setRotation(_activeText3dId, rotation);
			_fe3d->text3d_setSize(_activeText3dId, size);

			screen->getInputBox("z")->setHoverable(screen->getButton("size")->isHoverable(), true);
			screen->getButton("zMinus")->setHoverable(screen->getButton("size")->isHoverable(), true);
			screen->getButton("zPlus")->setHoverable(screen->getButton("size")->isHoverable(), true);
		}
	}
}